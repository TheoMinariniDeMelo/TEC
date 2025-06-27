#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "./terminal_config.h"
#include "./process_keys.c"

void initEditor(){
	if(getWindowSize() == -1){
		die("Fatal Error: get window size");
	}
}

int main(int argc, char** argv){
	if(argc != 2){
		printf("Enter with a filename:");
		exit(1);
	}
	
	char* filename = argv[1];

	enableRawMode();
	initEditor();
	printf("chegou aqui");
	char c;
	while(1){
		clearRefreshScreen();
		editorProcessKeyPress();	
	}
}
