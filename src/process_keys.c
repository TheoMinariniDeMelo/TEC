#include "./terminal.h"
#include <stdlib.h>
#include <unistd.h>

#define CTRL_KEY(x) x && 0x1f
#define PRINTABLE_KEY(x) x && 01111111

extern editorConfig E;

void editorCursorPosition(int c){
	switch(c){
		case ARROW_UP:
			if(E.cy != 0) E.cy -= 1;
			break;
		case ARROW_DOWN:
			if(E.cy != E.numrow - 1) E.cy += 1;
			break;
		case ARROW_LEFT:
			if(E.cx != 0) E.cx -= 1;
			break;
		case ARROW_RIGHT:
			if(E.cx != E.numcol - 6) E.cx += 1;
			break;
	}
}

void editorProcessKeyPress(){
	int c = readkeypress();
	switch (c) {
		case '\x03':
			write(STDOUT_FILENO, "\x1b[2J", 4);
			write(STDOUT_FILENO, "\x1b[H", 3);
			exit(0);
			break;
		case HOME_KEY:
			E.cx = 0;
			break;
		case END_KEY:
			break;
		case PAGE_UP:
		case PAGE_DOWN:
			{
				int times = E.numrow;
				int arrow = c == PAGE_UP ? ARROW_UP : ARROW_DOWN; 
				while(times--){
					editorCursorPosition(arrow);
				}
				break;
			}
		case ARROW_UP:
		case ARROW_DOWN:
		case ARROW_LEFT:
		case ARROW_RIGHT:
			editorCursorPosition(c);
	}
}
