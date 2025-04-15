typedef unsigned int uint;

#include "todo.h"
#include <stdlib.h>
#include <string.h>

int main(const int argv, const char *argc[]) {

	// -l  - List global tasks
	// -lc  - List tasks in current directory

	// -c  - Create global task
	// -cc - Create task in current directory

	// -r  - Remove global tasks
	// -rc - Remove tasks in current directory

	// -h  - Help

	if (argv == 1) {
		list(global);
		list(local);
	} else if (argv == 2) {
		if (!strcmp(argc[1], "-l")) {
			list(global);
			list(local);
		} else if (!strcmp(argc[1], "-lc"))
			list(local);
		else if (!strcmp(argc[1], "-h") || !strcmp(argc[1], "--help"))
			help();
		else
			usage();
	} else if (argv > 2) {
		if (!strcmp(argc[1], "-c"))
			create(argc, argv, global);
		else if (!strcmp(argc[1], "-cc"))
			create(argc, argv, local);
		else if (!strcmp(argc[1], "-r")) // +2, -2 to not pass program and option
			delMulti(argc + 2, argv - 2, global);
		else if (!strcmp(argc[1], "-rc"))
			delMulti(argc + 2, argv - 2, local);
		else
			usage();
	}
	exit(EXIT_SUCCESS);
}
