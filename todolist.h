#ifndef TODOLIST_H
#define TODOLIST_H

typedef enum { LOW, MEDIUM, HIGH } Priority;

typedef struct Task {
    int id;
    char title[100];
    Priority priority;
    struct Task* next;
} Task;

// Linked List APIs
Task* addTask(Task* head, int id, const char* title, Priority priority);
void displayTasks(Task* head);
Task* removeTask(Task* head, int id);
Task* findTask(Task* head, int id);
void freeTaskList(Task* head);
void sortTasksById(Task** head);

// Stack APIs (for completed tasks)
typedef struct StackNode {
    Task task;
    struct StackNode* next;
} StackNode;

void push(StackNode** top, Task task);
int pop(StackNode** top, Task* outTask);
void freeStack(StackNode* top);
void displayCompletedTasks(StackNode* top);

// Queue APIs (for priority/urgent tasks)
typedef struct QueueNode {
    Task task;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

void enqueue(Queue* q, Task task);
int dequeue(Queue* q, Task* outTask);
void freeQueue(Queue* q);
void displayPrioTasks(Queue* q);
int getNextTaskId();

// Interface function(s)
void mainMenu(const char *username);

#endif

