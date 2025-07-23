#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./data.h"

#define TEC_TAB_STOP 8

editorConfig E;

void abAppend(abuf *ab, char* str, size_t size){
	char *new_content = realloc(ab->content, ab->size + size);
	if(new_content == NULL) return; 	

	memcpy(&new_content[ab->size], str, size);
	ab->content = new_content;
	ab->size += size;
}
int abAppendRow(abuf *ab, erow *row){
	char *new_content = realloc(ab->content, ab->size + row->size);

	if(new_content == NULL) return -1; 	

	memcpy(&new_content[ab->size], row->content, row->size);
	ab->content = new_content;
	ab->size += row->size;
	return 0;
}
void editorAppendRow(char* line, size_t size){
	E.rows = realloc(E.rows, (E.num_rows + 1) * sizeof(erow));
	E.rows[E.num_rows].content = malloc((size + 1)* sizeof(char));
	memcpy(E.rows[E.num_rows].content, line, size);
	E.rows[E.num_rows].content[size] = '\0';
	E.rows[E.num_rows].size = size;

    E.rows[E.num_rows].render_content = NULL;
    E.rows[E.num_rows].rsize = 0;

	E.num_rows++;
}
void editorUpdateRow(erow* row){
    int tabs;
    for(int i = 0; i < row->size; i++){
        if(row->content[i] == '\t'){
            tabs++;
        }
    }
    row->rsize = row->size + tabs * (TEC_TAB_STOP - 1);
    row->render_content = malloc(row->rsize);

    for(int i = 0; i < row-> size; i++){
        if()
    }
}
void abFree(abuf *ab){
	free(ab->content);
}
