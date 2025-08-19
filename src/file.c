#include <stdio.h>
#include "terminal.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern editorConfig E;

void editorOpen(char* filename){
    if(!strlen(filename)){
        E.filename = "";
        return;
    };
    E.filename = strdup(filename);
    E.num_rows = 0;

    FILE *fd = fopen(filename, "r");

    if(!fd) die("Não foi possível abrir o arquivo");
    E.num_rows = 0;
    char* line = NULL;
    size_t n = 0;
    ssize_t read_bytes = 0;
    while((read_bytes = getline(&line, &n, fd)) != -1){
        while (read_bytes > 0 && (line[read_bytes - 1] == '\n' ||
            line[read_bytes - 1] == '\r'))
            read_bytes--;
        editorAppendRow(line, read_bytes);
    }
    fclose(fd);
    return;
}
