#include <stdlib.h>

#include "todo.h"

void create(const char *task[], uint words, bool isGlobal) {
	FILE *file = openFile("a", isGlobal); // Append to file

	for (uint i = 2; i < words; i++)
		fprintf(file, "%s ", task[i]);

	fprintf(file, "\n");
	fclose(file);
	exit(EXIT_SUCCESS);
}

void list(bool isGlobal) {
	FILE *file = openFile("r", isGlobal);
	char *line = NULL;
	size_t len = 0;

	if (file == NULL)
		return;
	printf(isGlobal ? "\033[32mGlobal tasks: \033[0m\n" : "\033[32mLocal tasks: \033[0m\n");
	if ((getline(&line, &len, file)) == -1)
		printf("Empty!\n");
	else {
		uint lineNumber = 1;
		printf("%d: %s", lineNumber, line);
		lineNumber++;
		while ((getline(&line, &len, file)) != -1) {
			printf("%d: %s", lineNumber, line);
			lineNumber++;
		}
	}

	free(line);
	fclose(file);
}

void del(const uint task, bool isGlobal) {
	uint numberOfTasks = 1;

	FILE *file = openFile("r", isGlobal);
	fseek(file, 0, SEEK_END);
	unsigned long long fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);
	rewind(file);

	char *buffer = (char *)malloc(fileSize + 1);
	uint i = 0;
	bool isFound = false;

	char c;
	while ((c = getc(file)) != EOF) {
		if (numberOfTasks != task)
			buffer[i++] = c;
		else
			isFound = true;
		if (c == '\n')
			numberOfTasks++;
	}

	buffer[i] = '\0';

	if (isFound) {
		freopen(NULL, "w", file);
		fputs(buffer, file);
	} else {
		printf("\033[31mNo task of id %u was found\033[0m\n", task);
		free(buffer);
		fclose(file);
		exit(EXIT_FAILURE);
	}
	free(buffer);
	fclose(file);
}

int compare(const void *a, const void *b) { return (*(uint *)b - *(uint *)a); }

void delMulti(const char *tasks[], uint numberOfTasks, bool isGlobal) {
	uint tasksToDelete[numberOfTasks];
	for (uint i = 0; i < numberOfTasks; i++)
		tasksToDelete[i] = atoi(tasks[i]);

	for (uint i = 0; i < numberOfTasks; i++) {
		for (uint j = i + 1; j < numberOfTasks; j++) {
			if (tasksToDelete[i] == tasksToDelete[j]) {
				printf("\033[31mDuplicate task number %u\033[0m\n", tasksToDelete[i]);
				exit(EXIT_FAILURE);
			}
		}
	}

	if (numberOfTasks > 0)
		qsort(tasksToDelete, numberOfTasks, sizeof(uint), compare);

	for (uint i = 0; i < numberOfTasks; i++)
		del(tasksToDelete[i], isGlobal);
}
