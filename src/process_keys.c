#include "./terminal.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define CTRL_KEY(x) x && 0x1f
#define PRINTABLE_KEY(x) x && 01111111

extern editorConfig E;

void editorCursorPosition(int c){
	switch(c){
		case ARROW_UP:
			if(E.cy == 0) break;
			E.cy -= 1;
		case ARROW_DOWN:
			if(E.cy == E.numrow - 1) break;
			E.cy += 1;
		case ARROW_LEFT:
			if(E.cx == 0) break;
			E.cx -= 1;
		case ARROW_RIGHT:
			if(E.cx == E.numcol - 1) break;
			E.cx += 1;

	}
}

void editorProcessKeyPress(){
	int c = readkeypress();
	switch (c) {
		case CTRL_KEY('q'):
			exit(0);
			break;
		case ARROW_UP:
		case ARROW_DOWN:
		case ARROW_LEFT:
		case ARROW_RIGHT:
			editorCursorPosition(c);
		//default:
		//	printf("%c\n", c);
	}
}
