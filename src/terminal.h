#include "./data.h"

typedef enum{
	ARROW_UP = 1000,
	ARROW_DOWN = 1001,
	ARROW_LEFT = 1002,
	ARROW_RIGHT = 1003
} ARROW;


void die(char *msg);

void clearRefreshScreen();

int getWindowSize(/*int *row, int *col*/);

int getCursorPosition(int *row, int *col);

int readkeypress();

void editorDrawRows(abuf *ab);

