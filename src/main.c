#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "./terminal_config.c"
int main(int argc, char** argv){
	if(argc != 2){
		printf("Enter with a filename:");
		exit(1);
	}
	
	char* filename = argv[1];

	enableRawMode();
	
	char c;
	while(1){
		/*
		 * errno: variavel que seu valor é alterado por syscalls e algumas bibliotecas quando
		 * algo inesperado ocorre, diferente do retorno padrão como em malloc ou read/write,
		 * ele descreve comportamentos, como descritor de arquivo em estado ruim ou 
		 * recurso não disponível (EAGAIN), todos os valores são inteiros positivos
		 * */
		if(read(STDIN_FILENO, &c, 1) != -1 && errno != EAGAIN){

		};

		if(c == 'q') exit(0);
		printf("%d\r\n",c);
	}
}
