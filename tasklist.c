#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "todolist.h"

// Adds a new task to the linked list
Task* addTask(Task* head, const char* title, Priority priority) {
    Task* newTask = (Task*)malloc(sizeof(Task));
    static int id_counter = 1;
    if (!newTask) {
        printf("Memory allocation failed.\n");
        return head;
    }
    newTask->id = id_counter++;
    strncpy(newTask->title, title, sizeof(newTask->title) - 1);
    newTask->title[sizeof(newTask->title) - 1] = '\0';
    newTask->priority = priority;
    newTask->next = head;
    return newTask;
}

// Display all tasks with their priorities
void displayTasks(Task* head) {
    Task* temp = head;
    printf("\nActive Tasks:\n");
    printf("ID\tPriority\tTitle\n");
    while (temp) {
        printf("%d\t%s\t\t%s\n", temp->id,
               temp->priority == HIGH ? "High" :
               temp->priority == MEDIUM ? "Medium" : "Low",
               temp->title);
        temp = temp->next;
    }
}

// Remove task by ID and return head of the list
Task* removeTask(Task* head, int id) {
    Task *temp = head, *prev = NULL;
    while (temp && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (!temp) return head;
    if (prev) prev->next = temp->next;
    else head = temp->next;
    free(temp);
    return head;
}

// Search task by ID
Task* findTask(Task* head, int id) {
    while (head) {
        if (head->id == id)
            return head;
        head = head->next;
    }
    return NULL;
}

// Free all tasks in the list
void freeTaskList(Task* head) {
    while (head) {
        Task* temp = head;
        head = head->next;
        free(temp);
    }
}

// Bubble sort hell yeah
void sortTasksByPriority(Task** head) {
    int swapped;
    Task *ptr1;
    Task *lptr = NULL;

    if (!(*head)) return;
    do {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr) {
            if (ptr1->priority < ptr1->next->priority) { // Descending order
                int temp_id = ptr1->id;
                char temp_title[100];
                strcpy(temp_title, ptr1->title);
                Priority temp_priority = ptr1->priority;

                ptr1->id = ptr1->next->id;
                strcpy(ptr1->title, ptr1->next->title);
                ptr1->priority = ptr1->next->priority;

                ptr1->next->id = temp_id;
                strcpy(ptr1->next->title, temp_title);
                ptr1->next->priority = temp_priority;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Stack functions for completed tasks
void push(StackNode** top, Task task) {
    StackNode* node = (StackNode*)malloc(sizeof(StackNode));
    if (!node) return;
    node->task = task;
    node->next = *top;
    *top = node;
}

int pop(StackNode** top, Task* outTask) {
    if (!(*top)) return 0;
    StackNode* temp = *top;
    *outTask = temp->task;
    *top = temp->next;
    free(temp);
    return 1;
}

void freeStack(StackNode* top) {
    while (top) {
        StackNode* temp = top;
        top = top->next;
        free(temp);
    }
}

// Basic Queue (pd sha sa high-priority tasks ^_^ pagod na ko baby di ko na kaya)
void enqueue(Queue* q, Task task) {
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    if (!node) return;
    node->task = task;
    node->next = NULL;
    if (!q->rear) {
        q->front = q->rear = node;
    } else {
        q->rear->next = node;
        q->rear = node;
    }
}

int dequeue(Queue* q, Task* outTask) {
    if (!q->front) return 0;
    QueueNode* temp = q->front;
    *outTask = temp->task;
    q->front = temp->next;
    if (!q->front)
        q->rear = NULL;
    free(temp);
    return 1;
}

void freeQueue(Queue* q) {
    QueueNode* temp;
    while (q->front) {
        temp = q->front;
        q->front = q->front->next;
        free(temp);
    }
    q->rear = NULL;
}
// ang masasabi ko lang ayyyy TITE im done im out BYEEEE

void displayCompletedTasks(StackNode* top) {
    StackNode* temp = top;
    char* priorityString;

    while (temp != NULL) {
        switch (temp->task.priority) {
            case 0: priorityString = "LOW";
            break;
            case 1: priorityString = "MEDIUM";
            break;
            case 2: priorityString = "HIGH";
            break;
            default: priorityString = "UNDEFINED";
            break;
    }
        printf("Completed Tasks:\n");
        printf("ID\tPriority\tTitle\n");
        printf("%d\t%s\t\t%s\n", 
            temp->task.id, priorityString, temp->task.title);
        temp = temp->next;

    };
}