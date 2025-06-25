#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "./logger.h"
static struct termios orgi_termios;

typedef struct {
	char* content;

} erow;

typedef struct {
	char* filename;
	int raw_mode;
	int numrow;
	erow *rows;
} editorConfig;

editorConfig editorC;

/*
 * ECHO: printa o caracter inserido 
 * ICANON: é possível ler a entrada do buffer apenas quando apertar ENTER 
 * ISIG: envio dos sinais SIGINT (Ctrl+Z) e SIGTSTP (Ctrl+Z)
 * IXON: Habilita o desativamento da propagação (Ctrl+S) e recebimento dos dados (Ctrl+Q)
 * OPOST: toda vez que um \n for printado, o \r (carry)
 * IEXTEN: Habilita o envio de dados literais (Ctrl+Y) - ex: (Ctrl+Y) + (Ctrl+C) => 3, ao invés de enviar um sinal
 * */
void disableRawMode(){
	if(editorC.raw_mode){
		if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &orgi_termios) == -1) die("tcsetattr");
		editorC.raw_mode = 0;
	}
}
void enableRawMode(){
	if(!isatty(STDIN_FILENO)){
		die("Fatal Error: the STDIN is not a tty");
	}
	if(tcgetattr(STDIN_FILENO, &orgi_termios) == -1) die ("tcgetattr");
	struct termios raw = orgi_termios;
	atexit(disableRawMode);
	raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN); 
	raw.c_iflag &= ~(BRKINT | IXON);
	raw.c_cc[VMIN] = 0; // quantidade mínima de bytes para a syscall read retornar o valor
	raw.c_cc[VTIME] = 1; // 1 mili segundos de delay para retorno do read
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
