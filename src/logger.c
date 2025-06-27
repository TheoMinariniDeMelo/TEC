#include "./logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

messages msgs;
loggerConfig lgconfig;

char* getDateTime(){
	time_t current_time = time(NULL);	
	struct tm *localtimeinfo = localtime(&current_time);
	return asctime(localtimeinfo);
}


void messageAppend(char* msg, messageType type){
	long new_size = msgs.size + strlen(msg);

	msgs.contents = realloc(msgs.contents, new_size);
	msgs.sizeb = new_size;
	msgs.size++;

	if(msgs.contents == NULL) die("message bus error");

	msgs.contents[msgs.size - 1].content = msg;
	msgs.contents[msgs.size - 1].type = type;
}

void loggerWriteInformation(char *info){
	FILE* file = lgconfig.file_log;

	asprintf(&info, "[%s] INFO: %s", getDateTime(), info);

	if(fwrite(info, sizeof(char), strlen(info), file) == -1) {
		messageAppend("Couldn't possible save log", ERROR);
		messageAppend(info, INFO);
	};

}

void configLogger(char* log_dir){
	char* path;

	time_t current_timestamp = time(NULL);

	lgconfig.log_dir = log_dir == NULL ? "./logs" : log_dir;

	asprintf(&path, "%s/%ld.log", lgconfig.log_dir, (long) current_timestamp);

	FILE* file = fopen(path, "a+");
	if(file == NULL){
		char* msg;
		asprintf(&msg, "[%s] Error: %s", getDateTime(), "Create File of logs fail");
		messageAppend(msg, ERROR);
		lgconfig.logInMessages = 1;
	}else{
		lgconfig.file_log = file;
	}
}

