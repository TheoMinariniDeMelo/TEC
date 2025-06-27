#include <asm-generic/errno-base.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "./terminal.h"
#include "./terminal_config.h"

#include "sys/ioctl.h"

extern editorConfig E;

void clearRefreshScreen(){
	write(STDOUT_FILENO, "\x1b[2J", 4);
	write(STDOUT_FILENO, "\x1b[H", 3);
	editorDrawRows();
}
void editorDrawRows(){
	for(int i = 0; i < E.numrow; i++){
		write(STDOUT_FILENO, "~", 1);
		if(i < E.numrow -1) write(STDOUT_FILENO, "\r\n", 2);
	}
}

int getWindowSize(/*int *row, int *col*/){
	struct winsize ws;
	if( 1|| ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0){
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

char readkeypress(){
	char c;
	int nread;
	while((nread = read(STDIN_FILENO, &c, 1)) <= 0){
		if(nread == -1 && errno != EAGAIN) die("error in read stdin");
	}
	return c;
}
