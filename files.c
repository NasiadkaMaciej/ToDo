#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <limits.h>
// open global/local file to read/write
FILE *openFile(char mode[], bool isGlobal)
{
	char *directory;
	char *filePath;

	if (isGlobal)
	{
		directory = getenv("HOME");
		filePath = "/.local/share/ToDo.txt";
	}
	else
	{
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