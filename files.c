#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
// open global/local file to read/write
FILE *openFile(const char mode[], bool isGlobal) {
	const char *directory;
	const char *filePath;

	if (isGlobal) {
		directory = getenv("HOME");
		filePath = "/.local/share/ToDo.txt";
	} else {
		directory = getcwd(NULL, PATH_MAX);
		filePath = "/ToDo.txt";
	}

	char *fullPath = malloc(strlen(directory) + strlen(filePath) + 1);
	strcpy(fullPath, directory);
	strcat(fullPath, filePath);
	FILE *file = fopen(fullPath, mode);
	free(fullPath);
	return file;
}