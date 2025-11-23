#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "todolist.h"
#include <windows.h>

void center_text(const char *text, int console_width, const char *username) {
    int text_length = snprintf(NULL, 0, text, username);
    int padding = (console_width - text_length)/2;

    if (padding < 0) {
        padding = 0;
    } 
    printf("%*s", padding, "");
    printf(text, username);
    printf("\n");
}

void center_line(const char *text, int console_width) {
    int text_length = strlen(text);
    int padding = (console_width - text_length) / 2;

    if (padding < 0) {
        padding = 0;
    }
    printf("%*s%s\n", padding, "", text);

}

void mainMenu(const char *username) {
    Task* activeList = NULL;
    StackNode* completedStack = NULL;
    Queue priorityQueue = {NULL, NULL};
    Task retrievedTask; 
    int choice;
    int taskId;
    char taskTitle[100];
    int taskPriority; 
    const int console_width = 20;

    while (1) {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        WORD saved_attributes;

        // Saving current attributes
        GetConsoleScreenBufferInfo(h, &consoleInfo);
        saved_attributes = consoleInfo.wAttributes;

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
        center_text("\n========== %s's TO-DO LIST ==========", console_width, username);

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
        printf("[1] Add Task");
        printf("\n[2] Display Tasks");
        printf("\n[3] Mark Task as Complete");
        printf("\n[4] Undo Task Completion");
        printf("\n[5] Exit\n");

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
        center_line("=========================================", console_width);

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        printf("\nEnter your choice: ");
        int result = scanf("%d", &choice);
        if (result != 1 || choice < 1 || choice > 5) {
            if (result !=1) {
                printf("Invalid input. Please enter a number.\n");
                while (getchar() != '\n');
            } else {
                    printf("Invalid input. Please enter input within range.\n");
                    while (getchar() != '\n');
            }
            choice =0;
        } else {
            while (getchar() != '\n');
        }
        switch (choice) {
            case 1:
            printf("Enter task: ");
            fgets(taskTitle, 100, stdin);
            taskTitle[strcspn(taskTitle, "\n")] = '\0';
            printf("Priority level [0, 1, 2]: ");
            int result = scanf("%d", &taskPriority);
            while (getchar() != '\n');
            if (result != 1 || taskPriority < 0 || taskPriority > 2) {
                printf("Invalid input. Please enter a number within range.\n");
            } else {
                activeList = addTask(activeList, taskTitle, (Priority)taskPriority);
                printf("Task added successfully.\n");
            }
            break;

            case 2:
            displayTasks(activeList);
            break;

            case 3:
            displayTasks(activeList);
            printf("\nEnter Task ID of completed task: ");
            scanf("%d", &taskId);
            Task* taskToMove = findTask(activeList, taskId);
            if (taskToMove != NULL) {
                push(&completedStack, *taskToMove);
                activeList = removeTask(activeList, taskId);
                printf("Task marked as complete.\n");
                displayCompletedTasks(completedStack);
            } else {
                printf("Task ID not found.");
            }
            break;

            case 4: 
            printf("\nCompleted Tasks:\n");
            displayCompletedTasks(completedStack);
            if (pop(&completedStack, &retrievedTask)) {
                printf("Undoing recently completed task...\n");
                activeList = addTask(activeList, retrievedTask.title, (Priority)retrievedTask.priority);
                printf("Undid completion for task: %s\n", retrievedTask.title);   
            } else {
                printf("No completed tasks yet.\n");
            }
            break;

            case 5:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf("Exiting program...");
            SetConsoleTextAttribute(h, saved_attributes);
            freeTaskList(activeList);
            freeStack(completedStack);
            freeQueue(&priorityQueue);
            return;

            default:
            break;        
        };
    }
}

int main() {
    char username[50];
    printf("Input user name: ");
    scanf("%s", username);
    mainMenu(username);
    return 0;
}