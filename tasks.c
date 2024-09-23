#include <stdlib.h>

#include "todo.h"

void create(char *task[], int words, bool isGlobal) {
	FILE *file = openFile("a", isGlobal); // Append to file

	for (int i = 2; i < words; i++)
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
		int lineNumber = 1;
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

void del(const int task, bool isGlobal) {
	unsigned int numberOfTasks = 1;

	FILE *file = openFile("r", isGlobal);
	fseek(file, 0, SEEK_END);
	unsigned long fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);
	rewind(file);

	char *buffer = (char *)malloc(fileSize + 1);
	unsigned int i = 0;
	bool isFound = false;

	char c;
	while ((c = getc(file)) != EOF)
		if (numberOfTasks != task)
			buffer[i++] = c;
		else
			isFound = true;
	if (c == '\n')
		numberOfTasks++;

	buffer[i] = '\0';

	if (isFound) {
		freopen(NULL, "w", file);
		fputs(buffer, file);
	} else {
		printf("\033[31mNo task of id %i was found\033[0m\n", task);
		free(buffer);
		fclose(file);
		exit(EXIT_FAILURE);
	}
	free(buffer);
	fclose(file);
}

int compare(const void *a, const void *b) { return (*(int *)b - *(int *)a); }

void delMulti(char *tasks[], int numberOfTasks, bool isGlobal) {
	int tasksToDelete[numberOfTasks];
	for (int i = 0; i < numberOfTasks; i++)
		tasksToDelete[i] = atoi(tasks[i]);

	for (int i = 0; i < numberOfTasks; i++) {
		for (int j = i + 1; j < numberOfTasks; j++) {
			if (tasksToDelete[i] == tasksToDelete[j]) {
				printf("\033[31mDuplicate task number %i\033[0m\n", tasksToDelete[i]);
				exit(EXIT_FAILURE);
			}
		}
	}

	qsort(tasksToDelete, numberOfTasks, sizeof(int), compare);

	for (int i = 0; i < numberOfTasks; i++)
		del(tasksToDelete[i], isGlobal);
}
