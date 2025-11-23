#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "todolist.h"

void mainMenu(void) {
    Task* activeList = NULL;
    StackNode* completedStack = NULL;
    Queue priorityQueue = {NULL, NULL};
    Task retrievedTask; 
    int choice;
    int taskId;
    char taskTitle[100];
    int taskPriority; 

    while (1) {
        printf("\n===== MENU =====");
        printf("\n1. Add Task");
        printf("\n2. Display Tasks");
        printf("\n3. Mark Task as Complete");
        printf("\n4. Undo Task Completion");
        printf("\n5. Exit");
        printf("\n================");

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
            printf("Enter Task ID of completed task: ");
            scanf("%d", &taskId);
            Task* taskToMove = findTask(activeList, taskId);
            if (taskToMove != NULL) {
                push(&completedStack, *taskToMove);
                activeList = removeTask(activeList, taskId);
                printf("Task marked as complete.\n");
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
                return;
            }
            break;

            case 5:
            printf("Exiting program...");
            freeTaskList(activeList);
            freeStack(completedStack);
            freeQueue(&priorityQueue);
            return;

            // default:
            // printf("Invalid choice! Please try again.\n");
        };
    }
}

int main() {
    mainMenu();
    return 0;
}