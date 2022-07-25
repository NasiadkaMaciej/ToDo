#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void usage()
{
    printf("\033[31mWrong usage, get help using: \033[0m\n");
    printf("todo --help\n");
    exit(1);
}
void help()
{   
    printf(" No arguments,\n");
    printf(" -l              List global tasks\n");
    printf(" -lc             List tasks in current directory\n");
    printf("Example: todo -l\n\n");

    printf(" -c              Create global task\n");
    printf(" -cc             Create task in current directory\n");
    printf("Example: todo -cc \"Buy apples\"\n\n");

    printf(" -r              Remove global task\n");
    printf(" -rc             Remove task in current directory\n");
    printf("Get ID using: todo -l or todo -lc\n");
    printf("Example: todo -r 7\n\n");
    printf(" -h, --help      Display help and exit\n");
    exit(0);
}

