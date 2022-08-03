#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "todo.h"

void create(char *task[], int words, bool isGlobal)
{
    FILE *file = openFile("a", isGlobal); // Append to file

    for (int i = 2; i < words; i++)
    {
        fprintf(file, "%s", task[i]); // Write word to file
        fprintf(file, "%s", " ");     // Write space to file
    }
    fprintf(file, "\n");
    fclose(file);
    exit(EXIT_SUCCESS);
}

void list()
{
    FILE *file;

    file = openFile("r", global);
    if (file != NULL)
    {
        printf("\033[32mGlobal tasks: \033[0m\n");
        showList(global);
        fclose(file);
    }

    file = openFile("r", local);
    if (file != NULL)
    {
        printf("\033[32mLocal tasks: \033[0m\n");
        showList(local);
        fclose(file);
    }
    exit(EXIT_SUCCESS);
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
        if (c == EOF && i == 1)
        {
            printf("Empty!\n");
            break;
        }
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
    fclose(file);
}

void del(int task, bool isGlobal)
{
    unsigned long numberOfTasks = 1;

    FILE *file = openFile("r", isGlobal);
    fseek(file, 0, SEEK_END);
    int fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char buffer[fileSize];

    unsigned int i = 0;
    bool isFound = false;

    do
    {
        char c = getc(file);
        if (c == EOF)
        {
            buffer[i] = '\0';
            break;
        }
        if (numberOfTasks != task)
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
    else
    {
        printf("\033[31mNo task of id %i was found\033[0m\n", task);
        exit(EXIT_FAILURE);
    }
}