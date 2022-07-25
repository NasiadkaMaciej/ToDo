#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "todo.h"

int main(int argv, char *argc[])
{
    // -l  - List global tasks
    // -lc  - List tasks in current directory

    // -c  - Create global task
    // -cc - Create task in current directory

    // -r  - Remove global task
    // -rc - Remove task in current directory

    // -h  - Help

    if (argv == 1)
        list();
    else if (argv == 2)
    {
        if (!strcmp(argc[1], "-l"))
            list();
        else if (!strcmp(argc[1], "-lc"))
            showList(global);
        else if (!strcmp(argc[1], "-h") || !strcmp(argc[1], "--help"))
            help();
        else
            usage();
    }
    else if (argv == 3)
    {
        if (!strcmp(argc[1], "-c"))
            // if there is program name, -c and task
            // figure out how to pass everything after 2 parameter
            create(argc[2], global);
        else if (!strcmp(argc[1], "-cc"))
            // if there is program name, -c and task
            // figure out how to pass everything after 2 parameter
            // Save location do db
            create(argc[2], local);
        else if (!strcmp(argc[1], "-r"))
            del(argc[2], global);
        else if (!strcmp(argc[1], "-rc"))
            del(argc[2], local);
        else
            usage();
    }
    else if(argv>3){
        usage();
    }
    return 0;
}
