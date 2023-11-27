#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100

typedef struct {
    char description[100];
    int isCompleted;
} Task;

void addTask(Task **taskList, int *taskCount, const char *description)
{
    if (*taskCount < MAX_TASKS)
    {
        Task newTask;
        strcpy(newTask.description, description);
        newTask.isCompleted = 0;

        (*taskList)[*taskCount] = newTask;
        (*taskCount)++;
        printf("Task added successfully!\n");
    }
    else
    {
        printf("Task list is full. Cannot add more tasks.\n");
    }
}

void markTaskCompleted(Task *taskList, int taskCount, int taskId)
{
    if (taskId >= 0 && taskId < taskCount)
    {
        taskList[taskId].isCompleted = 1;
        printf("Task %d marked as completed!\n", taskId);
    }
    else
    {
        printf("Invalid task ID. Please enter a valid task ID.\n");

        // Clear the input buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }
}

void displayTasks(Task *taskList, int taskCount)
{
    if (taskCount > 0)
    {
        printf("Task List:\n");
        for (int i = 0; i < taskCount; i++)
        {
            printf("[%d] %s - %s\n", i, taskList[i].isCompleted ? "[Completed]" : "[Pending]", taskList[i].description);
        }
    }
    else
    {
        printf("Task list is empty.\n");
    }
}

int main()
{
    Task *taskList = (Task *)malloc(MAX_TASKS * sizeof(Task));
    int taskCount = 0;
    int choice;
    char description[100];
    int taskId;

    do
    {
        printf("\nTask Manager Menu:\n");
        printf("1. Add Task\n");
        printf("2. Mark Task as Completed\n");
        printf("3. Display Tasks\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf(" %d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter task description: ");
                scanf(" %[^\n]s", description);
                addTask(&taskList, &taskCount, description);
                break;

            case 2:
                printf("Enter task ID to mark as completed: ");
                if (scanf(" %d", &taskId) != 1)
                {
                    printf("Invalid input. Please enter a valid task ID.\n");

                    // Clear the input buffer
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF)
                        ;
                }
                else
                {
                    markTaskCompleted(taskList, taskCount, taskId);
                }
                break;

            case 3:
                displayTasks(taskList, taskCount);
                break;

            case 4:
                printf("Exiting Task Manager.\n");
                break;

            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
                break;
        }

    } while (choice != 4);

    // Free the memory before exiting
    free(taskList);

    return 0;
}