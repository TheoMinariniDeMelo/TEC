#include "./terminal.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define CTRL_KEY(x) x && 0x1f
#define PRINTABLE_KEY(x) x && 01111111

void editorProcessKeyPress(){
	char c = readkeypress();
	switch (c) {
		case CTRL_KEY('q'):
			exit(0);
			break;
		default:
			printf("%c\n", c);
	}
}
