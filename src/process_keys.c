#include "./terminal.h"
#include "./terminal_config.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define CTRL_KEY(x) x & 0x1f
#define PRINTABLE_KEY(x) x & 0b01111111
#define IS_UPPPERCASE(x) (x & (x | 0b01000000)) == x  
extern editorConfig E;

void editorCursorPosition(int c){
    erow *row = (E.cy >= E.num_rows) ? NULL : &E.rows[E.cy];
    erow *next_row = (E.cy + 1 >= E.num_rows) ? NULL : &E.rows[E.cy + 1];

    switch(c){
        case ARROW_UP:
            if(E.cy != 0){
                E.cy--;
            }
            break;
        case ARROW_DOWN:
            if(E.cy < E.num_rows){
                E.cy++;
            }
            break;
        case ARROW_LEFT:
            if(E.cx > 0){
                E.cx--;
            }else if(E.cy != 0){
                editorCursorPosition(ARROW_UP);	
                E.cx = E.rows[E.cy].size;
            }
            break;
        case ARROW_RIGHT:
            if(row && E.cx < (*row).size)
            {
                E.cx++;
            }else if(row && next_row) {
                editorCursorPosition(ARROW_DOWN);
                E.cx = 0;
            }
            break;
    }
    row = (E.cy >= E.num_rows) ? NULL : &E.rows[E.cy];
    int rowlen = row ? row->size : 0;
    if (E.cx > rowlen) {
        E.cx = rowlen;
    }
}

void editorProcessKeyPress(){
    int c = readkeypress();
    switch (c) {
        case '\x03':
            write(STDOUT_FILENO, "\x1b[2J", 4);
            write(STDOUT_FILENO, "\x1b[H", 3);
            disableRawMode();
            exit(0);
            break;
        case HOME_KEY:
            E.cx = 0;
            break;
        case END_KEY:
            E.cx = E.rows[E.cy].size;
            break;
        case PAGE_UP:
        case PAGE_DOWN:
            {
                int times = E.numrow;
                int arrow = c == PAGE_UP ? ARROW_UP : ARROW_DOWN; 
                while(times--){
                    editorCursorPosition(arrow);
                }
                break;
            }
        case CTRL_KEY('w'):
            for(int i = E.cx + 1; i < E.rows[E.cy].size; i++){
                char c = E.rows[E.cy].content[i]; 
                if(c == ' '  || c == '(' || c == ')'){
                    E.cx = ++i;
                    break;
                }
            }

        case ARROW_UP:
        case ARROW_DOWN:
        case ARROW_LEFT:
        case ARROW_RIGHT:
            editorCursorPosition(c);
            break;
        case ESC:
            break;
        case 0x7f: { // backspace
            erow *row = &E.rows[E.cy];
            char *new_content = malloc(row->size - 1);
            if(E.cx == 0) {
                editorCursorPosition(ARROW_LEFT);
                break;
            }
            memmove(new_content, row->content, E.cx - 1);
            memmove(new_content + E.cx, row->content + E.cx + 1, row->size - E.cx);
            free(row->content);
            row->content = new_content;
            row->size -= 1;
            editorUpdateRow(row);
            editorCursorPosition(ARROW_LEFT);
            break;
        }
        default:{
            erow *row = &E.rows[E.cy];
            row->content = realloc(row->content, row->size + 1);
            memmove(row->content + E.cx + 1, row->content + E.cx, row->size - E.cx);
            row->content[E.cx] = c;
            row->size++;
            editorUpdateRow(row);
            editorCursorPosition(ARROW_RIGHT);
        }
    }
}
