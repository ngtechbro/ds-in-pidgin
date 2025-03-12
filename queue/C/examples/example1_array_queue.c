/**
* example1_array_queue.c 
*
* Example use case for array queue in C.
*
* WTD: We go just build simple task scheduler wey go accept task, and time(in seconds) wey e go take to run the task.
* When we process the task, e go run all tasks(in this case; na just sleep for the time we expect the system to run the task),
* but in real world, e go actually dey run any kind logic to do anything.
*
* Author: NULL
* Date: 12/03/2025
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct Task {
  char *name;
  int seconds;
} Task;

typedef struct ArrQueue{
  Task *data;
  int size;
  int capacity;
} ArrQueue;


/**
  * This function na to initialize the queue.
  *
  * @param ArrQueue *queue Pointer to the queue.
  */
void initQueue(ArrQueue *queue) {
  queue->data = (Task *) malloc(sizeof(Task));
  if(queue->data == NULL) {
    printf("Memory allocation no gree work.\n");
    return;
  }

  queue->capacity = 1;
  queue->size = 0;
}


/**
  * This function na to add task to our queue.
  *
  * @param ArrQueue *queue Pointer to the queue we wan add the task.
  * @param Task *task Pointer to the task we wan add.
  */
void addTask(ArrQueue *queue, Task *task) {
  if(queue->size >= queue->capacity) {
    queue->capacity *= 2;
    queue->data = (Task *) realloc(queue->data, queue->capacity * sizeof(Task));
    if(queue->data == NULL) {
      printf("Memory reallocation no gree work\n");
      return;
    }
  }

  queue->data[queue->size].name = (char *) malloc((strlen(task->name) + 1) * sizeof(char));
  strcpy(queue->data[queue->size].name, task->name);
  
  queue->data[queue->size].seconds = task->seconds;

  queue->size ++;
}


/**
  * This function na to process the top task wey dey our queue.
  * we go pop the top komot because we no want the task there again once e finish process.
  *
  * @param ArrQueue *queue Pointer to the queue
  */
void processTopTask(ArrQueue *queue) {
  if(queue->size == 0) {
    printf("This queue dey empty\n");
    return;
  }

  if(queue->size == 1) {
    queue->size = 0;
    return;
  }

  for(int i = 1; i < queue->size; i++) {
    queue->data[i - 1] = queue->data[i];
  }

  queue->size --;
}


int main() {
  ArrQueue queue;

  initQueue(&queue);

  while(1) {
    printf("\n");
    printf("*******************************************************************************\n");
    printf("*             Tuale Boss!! See available options wey dey:                     *\n");
    printf("*******************************************************************************\n");
    printf("* 1. Enter new Task\n");
    printf("* 2. Run scheduler.\n");
    printf("* 0. Exit.\n");
    printf("*******************************************************************************\n");
    printf("* Available Task: %d\n", queue.size);
    printf("*******************************************************************************\n");

    printf("\nEnter your option: \n");

    int option;
    scanf("%d", &option);

    getchar();

    switch (option) {
      case 0:
        printf("Exiting program...\n");
        return 0;
      case 1:
        // get task name
        printf("\nEnter new task name(<100): ");
        char taskName[100]; 
        fgets(taskName, sizeof(taskName), stdin);
        taskName[strcspn(taskName, "\n")] = '\0';

        // get time(in seconds) wey e go take to process
        int newTaskTime;
        printf("\nEnter time(in seconds) e go take to process: ");
        scanf("%d", &newTaskTime);

        Task newTask = {taskName, newTaskTime};

        addTask(&queue, &newTask);
        printf("\n Task don dey added successfully!\n");

        break;
      case 2:
        printf("** STARTING SCHEDULER... **\n");
        if(queue.size == 0) {
          printf("No task dey to process\n");
          break;
        }

        printf("processing task...\n");
        while(queue.size != 0) {
          Task task = queue.data[0];
          printf("TASK NAME: %s\n", task.name);
          printf("PROCESSING TIME: %dsecs\n", task.seconds);

          sleep(task.seconds);
          processTopTask(&queue);

          if(queue.size > 0) {
            printf("\ncurrent process complete, we dey move to the next task.\n");
          }
        }

        printf("\n\n** All tasks don finish process, stopping scheduler... **\n\n");
        break;
      default:
        printf("\n\nThe option wey you enter no dey make sense boss.\n\n");
        break;
    }
  }

  free(queue.data);

  return 0;
}
