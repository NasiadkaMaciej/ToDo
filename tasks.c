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
	bool printNum = true;
	int i = 1;
	if (file == NULL)
		exit(EXIT_FAILURE);
	printf(isGlobal ? "\033[32mGlobal tasks: \033[0m\n" : "\033[32mLocal tasks: \033[0m\n");
	do {
		char c = fgetc(file);
		if (c == EOF) {
			if (i == 1)
				printf("Empty!\n");
			break;
		}
		if (printNum) {
			printf("%i: ", i);
			printNum = false;
			i++;
		}
		if (c == '\n')
			printNum = true;
		printf("%c", c);
	} while (true);
	fclose(file);
}

void del(int task, bool isGlobal) {
	unsigned long numberOfTasks = 1;

	FILE *file = openFile("r", isGlobal);
	fseek(file, 0, SEEK_END);
	int fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	char buffer[fileSize];
	unsigned int i = 0;
	bool isFound = false;

	do {
		char c = getc(file);
		if (c == EOF) {
			buffer[i] = '\0';
			break;
		}
		if (numberOfTasks != task) {
			buffer[i] = c;
			i++;
		} else if (!isFound)
			isFound = true;

		if (c == '\n')
			numberOfTasks++;
	} while (true);

	if (isFound) {
		freopen(NULL, "w", file);
		for (i = 0;; i++) {
			if (buffer[i] == '\0')
				break;
			fputc(buffer[i], file);
		}
	} else {
		printf("\033[31mNo task of id %i was found\033[0m\n", task);
		exit(EXIT_FAILURE);
	}
	fclose(file);
}

int compare(const void *a, const void *b) { return (*(int *)b - *(int *)a); }

void delMulti(char *tasks[], int numberOfTasks, bool isGlobal) {
	int tasksToDelete[numberOfTasks];
	for (int i = 0; i < numberOfTasks; i++)
		tasksToDelete[i] = atoi(tasks[i]);

	bool duplicates = false;
	for (int i = 0; i < numberOfTasks; i++) {
		for (int j = i+1; j < numberOfTasks; j++) {
			if (tasksToDelete[i] == tasksToDelete[j]) {
				printf("\033[31mDuplicate task number %i\033[0m\n", tasksToDelete[i]);
				exit(EXIT_FAILURE);
			}
		}
	}

	qsort(tasksToDelete, numberOfTasks, sizeof(int), compare);

	for (int i = 0; i < numberOfTasks; i++) {
		del(tasksToDelete[i], isGlobal);
	}
}
