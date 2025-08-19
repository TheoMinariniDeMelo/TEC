#include <stddef.h>
#include <termios.h>

#define TEC_TAB_STOP 8
#define ABUF_INIT {NULL, 0}

typedef struct {
    int rsize;
    char* render_content;
	char* content;
    size_t size;
} erow;

typedef struct {
	int cx, cy, rx;
	struct termios orgi_termios;	
	char* filename;
	int raw_mode;
	int numrow; // número de linhas do terminal
	int numcol;
	int rowoff;
	int coloff;
	erow *rows;
	size_t num_rows; // número de linhas do arquivo
} editorConfig;

typedef struct {
	char* content;
	size_t size;
} abuf;

void abAppend(abuf *ab, char* str, size_t size);

int abAppendRow(abuf *ab, erow *row);

void editorAppendRow(char* line, size_t size);

void editorUpdateRow(erow* row);

void abFree(abuf *ab);
