#include <stddef.h>
#include <termios.h>

#define ABUF_INIT {NULL, 0}

typedef struct {
	char* content;
} erow;

typedef struct {
	int cx, cy;
	struct termios orgi_termios;	
	char* filename;
	int raw_mode;
	int numrow;
	int numcol;
	erow *rows;
} editorConfig;

typedef struct {
	char* content;
	size_t size;
} abuf;

void abAppend(abuf *ab, char* str, size_t size);

void abFree(abuf *ab);
