#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// open global/local file to read/write
FILE *openFile(char mode[], bool isGlobal)
{
	char *dir = getenv("HOME");				   // First half
	char *filePath = "/.local/share/ToDo.txt"; // Second halfs

	if (!isGlobal)
	{
		dir = getenv("PWD");
		filePath = "/ToDo.txt";
	}

	char *fullPath = strcat(dir, filePath);

	FILE *file = fopen(fullPath, mode);
	if (file == NULL)
	{
		fprintf(stderr, "Can't access: %s \n", fullPath);
		exit(1);
	}
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
		exit(1);
	}
	return file;
}