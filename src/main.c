#include <unistd.h>
#include <signal.h>
#include "./terminal_config.h"
#include "./process_keys.c"
#include "./file.h"

volatile int resize_terminal = 0;

void initEditor(){
    E.cx = 0;
    E.cy = 0;
    E.rx = 0;
    E.rowoff = 0;
    E.coloff = 0;
    E.num_rows = 0;
    if(getWindowSize() == -1){
        die("Fatal Error: get window size");
    }
}
void __handler_sig_winch(int sig){
    if(getWindowSize() != 0) die("Fatal Error: handler sig winch");
    E.numrow--;
    clearRefreshScreen();
}
void __handler_sig_int(int sig){
    disableRawMode();
    exit(0);
}
int main(int argc, char** argv){
    char* filename = "";
    if(argc == 2){
        filename = argv[1];
    }
    signal(SIGWINCH, __handler_sig_winch);
    signal(SIGINT, __handler_sig_int);

    enableRawMode();
    initEditor();
    write(STDOUT_FILENO,"\033[3J", 3);
    editorOpen(filename);
    E.num_rows -= 1;
    E.numrow--;
    while(1){
        clearRefreshScreen();
        editorProcessKeyPress();	
    }
}
