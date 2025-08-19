#include "./data.h"

typedef enum{
	ARROW_UP = 1000,
	ARROW_DOWN,
	ARROW_LEFT,
	ARROW_RIGHT,
	PAGE_UP,
	PAGE_DOWN,
	HOME_KEY,
	END_KEY,
	DEL_KEY
} editorKey;


void die(char *msg);

void editorScroll();

void clearRefreshScreen();

int getWindowSize();

int getCursorPosition(int *row, int *col);

int readkeypress();

void editorDrawRows(abuf *ab);

