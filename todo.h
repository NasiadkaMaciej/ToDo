#include <stdio.h>
#include <stdbool.h>

#define global true
#define local false

// files.c
FILE *openFile(char mode[], bool isGlobal);

// tasks.c
void create(char* task[], int words, bool isGlobal);
void list(bool isGlobal);
void delMulti(char* tasks[], int number, bool isGlobal);


// tools.c
void help();
void usage();