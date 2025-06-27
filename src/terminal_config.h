#include <termios.h>
typedef struct {
	char* content;
} erow;

typedef struct {
	struct termios orgi_termios;	
	char* filename;
	int raw_mode;
	int numrow;
	int numcol;
	erow *rows;
} editorConfig;

void disableRawMode();

void enableRawMode();
