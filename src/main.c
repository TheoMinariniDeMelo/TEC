#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "./terminal_config.h"
#include "./process_keys.c"

volatile int resize_terminal = 0;

void initEditor(){
	if(getWindowSize() == -1){
		die("Fatal Error: get window size");
	}
}
void __handler_sig_winch(int sig){
	if(getWindowSize() != 0) die("Fatal Error: handler sig winch");
}

int main(int argc, char** argv){
	if(argc != 2){
		printf("Enter with a filename:");
		exit(1);
	}
	
	char* filename = argv[1];
	signal(SIGWINCH, __handler_sig_winch);
	enableRawMode();
	initEditor();
	printf("chegou aqui");
	char c;
	while(1){
		clearRefreshScreen();
		editorProcessKeyPress();	
	}
}
