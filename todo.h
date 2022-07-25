#include <stdio.h>
#include <stdbool.h>

#define global true
#define local false

// files.c
FILE *openFile(char mode[], bool isGlobal);
FILE *openDB(char mode[]);

// tasks.c
bool create(char task[], bool isGlobal);
void list();
void showList(bool isPublic);
void del(char task[], bool isGlobal);

// tools.c
void help();
void usage();