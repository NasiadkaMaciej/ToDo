#include <stdlib.h>
#include <string.h>
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
            showList(local);
        else if (!strcmp(argc[1], "-h") || !strcmp(argc[1], "--help"))
            help();
        else
            usage();
    }
    else if (argv > 2)
    {
        if (!strcmp(argc[1], "-c"))
            create(argc, argv, global);
        else if (!strcmp(argc[1], "-cc"))
            create(argc, argv, local);
        else if (!strcmp(argc[1], "-r"))
            del(atoi(argc[2]), global);
        else if (!strcmp(argc[1], "-rc"))
            del(atoi(argc[2]), local);
        else
            usage();
    }
    exit(EXIT_SUCCESS);
}
