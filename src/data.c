#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./data.h"

void abAppend(abuf *ab, char* str, size_t size){
	char *new_content = realloc(ab->content, ab->size + size);
	if(new_content == NULL) return; 	
	
	memcpy(&new_content[ab->size], str, size);
	ab->content = new_content;
	ab->size += size;
}

void abFree(abuf *ab){
	free(ab->content);
}
