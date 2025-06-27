#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "./logger.h"
#include "./terminal_config.h" 

extern editorConfig E;


void disableRawMode(){
	if(E.raw_mode){
		if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orgi_termios) == -1) die("tcsetattr");
		E.raw_mode = 0;
	}
}
/*
 * ECHO: printa o caracter inserido 
 * ICANON: é possível ler a entrada do buffer apenas quando apertar ENTER 
 * ISIG: envio dos sinais SIGINT (Ctrl+Z) e SIGTSTP (Ctrl+Z)
 * IXON: Habilita o desativamento da propagação (Ctrl+S) e recebimento dos dados (Ctrl+Q)
 * OPOST: toda vez que um \n for printado, o \r (carry)
 * IEXTEN: Habilita o envio de dados literais (Ctrl+Y) - ex: (Ctrl+Y) + (Ctrl+C) => 3, ao invés de enviar um sinal
 * */
void enableRawMode(){
	if(!isatty(STDIN_FILENO)){
		die("Fatal Error: the STDIN is not a tty");
	}
	if(tcgetattr(STDIN_FILENO, &E.orgi_termios) == -1) die ("tcgetattr");
	struct termios raw = E.orgi_termios;
	atexit(disableRawMode);
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw.c_cc[VMIN] = 0; // quantidade mínima de bytes para a syscall read retornar o valor
	raw.c_cc[VTIME] = 1; // 1 mili segundos de delay para retorno do read
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
	}
