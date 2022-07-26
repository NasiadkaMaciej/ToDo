#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

// open global/local file to read/write
FILE *openFile(char mode[], bool isGlobal)
{
	char *directory = "";
	char *filePath = "";

	if (isGlobal)
	{
		directory = getenv("HOME");
		filePath = "/.local/share/ToDo.txt";
	}
	else
	{
		directory = getcwd(NULL, 200);
		filePath = "/ToDo.txt";
	}

	char *fullPath = malloc(strlen(directory) + strlen(filePath) + 1);
	strcpy(fullPath, directory);
	strcat(fullPath, filePath);
	FILE *file = fopen(fullPath, mode);
	return file;
}

// open file containing all locations of ToDo.txt files
FILE *openDB(char mode[])
{
	char *fullPath = strcat(getenv("HOME"), "/.local/share/db.txt");
	FILE *file = fopen(fullPath, mode);
	if (file == NULL)
	{
		fprintf(stderr, "Can't access: %s \n", fullPath);
		exit(EXIT_FAILURE);
	}
	return file;
}