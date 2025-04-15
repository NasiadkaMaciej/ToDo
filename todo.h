#include <stdbool.h>
#include <stdio.h>

#define global true
#define local false

// files.c
FILE *openFile(const char mode[], bool isGlobal);

// tasks.c
void create(const char *task[], uint words, bool isGlobal);
void list(bool isGlobal);
void delMulti(const char *tasks[], uint numberOfTasks, bool isGlobal);

// tools.c
void help();
void usage();