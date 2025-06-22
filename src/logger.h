#include <stdio.h>
typedef enum {
	ERROR = 1,
	INFO = 2
} messageType; 

typedef struct{
	char* log_dir;
	int logInMessages;
	FILE* file_log;
} loggerConfig;

typedef struct{
	char* content;
	messageType type;	
} message;

typedef struct {
	message* contents;
	long sizeb; // bytes
	size_t size;

} messages;


void messageAppend(char* msg, messageType type);

/*
 * Write a line into stderr and exit the program
 * */
void die(char* msg);

/*
 * Get current timestamp and convert it in a date time
 * */
char* getDateTime();

/*
 * Write a line into a logger file
 * */
void loggerWriteInformation(char* info);

/*
 * Config log variables
 * */
void configLogger(char* dir_log);
