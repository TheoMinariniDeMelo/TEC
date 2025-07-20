#include <asm-generic/errno-base.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "./terminal.h"
#include <sys/ioctl.h>
#include <string.h>

#define TEC_VERSION "0.0.1"

extern editorConfig E;

void clearRefreshScreen(){
	abuf ab = ABUF_INIT;	
	abAppend(&ab, "\x1b[6 q", 5);
	abAppend(&ab, "\x1b[?25l", 6);
	abAppend(&ab, "\x1b[2J", 4);
	abAppend(&ab, "\x1b[H", 3);
	editorDrawRows(&ab);

	char buf[32];
	snprintf(buf, sizeof(buf), "\x1b[%d;%dH", E.cy + 1, E.cx + 6);
	abAppend(&ab, buf, strlen(buf));
	abAppend(&ab, "\x1b[?25h", 6);

	write(STDOUT_FILENO, ab.content, ab.size);
	abFree(&ab);
}

void editorDrawRows(abuf *ab){
	E.numrow = 20;
	for(int i = 0, j = 1; i < E.numrow; i++, j++){
		char side[32];	
		ssize_t len = snprintf(
			side, sizeof(side), "\x1b[2m%c%c%c%d \x1b[0m", 
	   		j>=1000 ? '\0' : ' ', 
			j>=100 ? '\0' : ' ', 
			j>=10 ? '\0' : ' ', 
			j 
		);	

		if(i >= E.num_rows){
			if(i == E.numrow / 3 && E.num_rows != 0){
				char welcome[32];
				char welcomelen = snprintf(welcome, sizeof(welcome), "TEC %sv", TEC_VERSION);
				int padding = (E.numcol - welcomelen)/2;
				while(--padding) abAppend(ab, " ", 1);
				abAppend(ab, welcome, strlen(welcome));
			}
		}
		else{
			abAppend(ab, side, len);
			abAppendRow(ab, &E.rows[i]);
		}
		abAppend(ab, "\x1b[K", 3);
		if(i < E.numrow -1) abAppend(ab, "\r\n", 2);
	}
}	

int getWindowSize(){
	struct winsize ws;
	if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0){
		if(write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12 ) != 12) return -1;
		return getCursorPosition(&E.numrow, &E.numcol);
	}else {
		E.numrow = ws.ws_row;
		E.numcol = ws.ws_col;
	}
	return 0;
}
int getCursorPosition(int *row, int *col){
	char buf[32];
	if(write(STDOUT_FILENO, "\x1b[6n", 4) != 4) return -1;
	unsigned int i = 0;
	int n;
	while(i < sizeof(buf) - 1){
		if((n = read(STDIN_FILENO, &buf[i], 1)) != 1) break;
		if(buf[i] == 'R') break;
		i++;
	}
	buf[i] = '\0';
	if(buf[0] != '\x1b' || buf[1] != '[') return -1;
	if(sscanf(&buf[2], "%d;%d", row, col) != 2) return -1;
	return 0;
}
void die(char *msg){
	write(STDOUT_FILENO, "\x1b[2J", 4);
	write(STDOUT_FILENO, "\x1b[H", 3);

	perror(msg);
	exit(1);
}

int readkeypress(){
	char c;
	int nread;
	while((nread = read(STDIN_FILENO, &c, 1)) <= 0){
		if(nread == -1 && errno != EAGAIN) die("error in read stdin");
	}
	if(c == '\x1b'){
		char seq[3];
		if(read(STDIN_FILENO, &seq[0], 1) != 1) return '\x1b';
		if(read(STDIN_FILENO, &seq[1], 1) != 1) return '\x1b';
		if(seq[0] == '['){
			if(seq[1] >= '0' && seq[1] <= '9'){
				if(read(STDIN_FILENO, &seq[2], 1) != 1) return '\x1b';
				if(seq[2] == '~'){
					switch(seq[1]){
						case '3': return DEL_KEY;
						case '5': return PAGE_UP;
						case '6': return PAGE_DOWN;
					}
				}
			}
			switch(seq[1]){
				case 'A': return ARROW_UP; 
				case 'B': return ARROW_DOWN;
				case 'C': return ARROW_RIGHT;
				case 'D': return ARROW_LEFT;
				case 'H': return HOME_KEY;
			}
		}
	}
	return c;
}
