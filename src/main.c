#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "./terminal_config.c"
int main(int argc, char** argv){
	if(argc != 2){
		perror("Enter with a filename");
		exit(1);
	}
	char* filename = argv[1];
	enableRawMode();
	char c;
	while(read(STDIN_FILENO, &c, 1) != -1){
		printf("%d\r\n",c);
	}
	
}
