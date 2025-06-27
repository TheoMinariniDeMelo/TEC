#include "./data.h"

void die(char *msg);

void clearRefreshScreen();

int getWindowSize(/*int *row, int *col*/);

int getCursorPosition(int *row, int *col);

char readkeypress();

void editorDrawRows(abuf *ab);

