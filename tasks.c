#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "todo.h"

bool create(char task[], bool isGlobal)
{
    FILE *file = openFile("a", isGlobal); // Append to file

    // Scan file, if task already exist

    do
    {
        static unsigned int i = 0;
        if (task[i] == '\0')
            break;
        if (task[i] == '\n')
        {
            fprintf(stderr, "Task can't contain new line characters\n");
            exit(1);
        }
        i++;
    } while (true);

    fprintf(file, "%s\n", task); // Write to file

    fclose(file);
    return true;
}
void list()
{
    printf("\033[32mGlobal tasks: \033[0m\n");
    showList(global);
    printf("\033[32mLocal tasks: \033[0m\n");
    showList(local);
}

void showList(bool isPublic)
{
    FILE *file;
    if (isPublic)
        file = openFile("r", global);
    else
        file = openFile("r", local);

    int i = 1;
    bool printNum = true;
    do
    {
        char c = fgetc(file);
        if (c == EOF)
            break;
        if (printNum)
        {
            printf("%i: ", i);
            printNum = false;
            i++;
        }
        if (c == '\n')
            printNum = true;
        printf("%c", c);
    } while (true);
}

// Normally delete from all, but with parameter delete only selected
void del(char task[], bool isGlobal)
{
    unsigned long taskNum = atoi(task);
    unsigned long numberOfTasks = 1;
    // char *taskName = task;

    FILE *file = openFile("r", isGlobal);

    // Put file to buffer to make checking much faster
    fseek(file, 0, SEEK_END);
    int fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *buffer;
    buffer = malloc(fileSize);

    unsigned int i = 0;
    bool isFound = false;

    do
    { // move from higher to here
        char c = getc(file);
        if (c == EOF)
        {
            buffer[i] = '\0';
            break;
        }
        if (numberOfTasks != taskNum)
        {
            buffer[i] = c;
            i++;
        }
        else if (!isFound)
            isFound = true;

        if (c == '\n')
            numberOfTasks++;
    } while (true);

    if (isFound)
    {
        freopen(NULL, "w", file);

        for (i = 0;; i++)
        {
            if (buffer[i] == '\0')
                break;
            fputc(buffer[i], file);
        }
    }
}