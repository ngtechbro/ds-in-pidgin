/**
 * array_queue.c 
 *
 * Implementation of queue using array in C.
 *
 * Wetin be queue?
 * Queue na a type of linear data structure wey dey follow the "First in First out" (FIFO) principle.
 * Queue dey operate just like normal line wey you know. Yes! that bank type of line wey dey vex person.
 * Wetin this mean na say data go dey arranged in the queue in a linear order,
 * the first data/content wey you put inside must be the first to komot if you dey do any remove operation from that queue.
 * JUST KNOW SAY THE LOGIC BEHIND QUEUE NA SAY THE DATA WEY FIRST ENTER, NA WETIN GO FIRST KOMOT IF YOU WAN DO ANY REMOVING.
 * You fit implement queue with arrays or linked list provided say you follow the logic.
 * Queue just dey like stack, but stack dey follow the LIFO principle while queue dey follow the FIFO principle.
 *
 * Operations:
 * - Push(to add data): O(1)
 * - Pop(to komot data): O(n)
 * - Peek(to get the top data): O(1)
 *
 * Author: NULL
 * Date: 12/03/2025
 **/

#include <stdio.h>
#include <stdlib.h>

typedef struct ArrayQueue {
  int *data;
  int size;
  int capacity;
} ArrayQueue;


/**
  * This function na to initialize the queue.
  *
  * @param ArrayQueue *queue The pointer to the queue.
  */
void initQueue(ArrayQueue *queue) {
  queue->data = (int *) malloc(sizeof(int));
  if(queue->data == NULL) {
    printf("memory allocation no gree work\n");
    return;
  }

  queue->capacity = 1;
  queue->size = 0;
}


/**
  * This function na to push data to the end of the queue.
  * PS: i gatz use pointers whine you small for here lol.
  *
  * @param ArrayQueue *queue The pointer to the queue.
  * @param int data The data we plan push.
  */
void push(ArrayQueue *queue, int data) {
  int *queueSize = &(queue->size);
  int *queueCapacity = &(queue->capacity);
  int **queueData = &(queue->data);

  if (*queueSize >= *queueCapacity) {
    *queueCapacity += 2;
    *queueData = (int *) realloc(*queueData, (*queueCapacity) * sizeof(int));
    
    if (*queueData == NULL) {
      printf("Memory reallocation failed\n");
      return;
    }
  }

  (*queueData)[*queueSize] = data;
  (*queueSize)++;

  return;
}


/**
  * This function na to pop data komot from the queue.
  *
  * @param ArrayQueue *queue The pointer to the queue.
  */
int pop(ArrayQueue *queue) {
  if(queue->size == 0) {
    printf("The queue dey empty\n");
    return -1;
  }

  if(queue->size == 1) {
    queue->size = 0;
    return queue->data[0];
  }

  int poppedData = queue->data[0];
  for(int i = 1; i < queue->size; i ++) {
    queue->data[i - 1] = queue->data[i];
  }

  queue->size --;

  return poppedData;
}


/**
  * This function na to access the data wey dey for the top of the queue.
  *
  * @param ArrayQueue *queue The pointer to the queue.
  */
int peek(ArrayQueue *queue) {
  if(queue->size == 0) {
    printf("The queue dey empty\n");
    return -1;
  }

  return queue->data[0];
}


int main() {
  ArrayQueue queue;

  initQueue(&queue);

  push(&queue, 0);
  push(&queue, 1);
  push(&queue, 2);
  push(&queue, 3);
  push(&queue, 4);

  pop(&queue);

  for(int i = 0; i < queue.size; i ++) {
    printf("%d\n", queue.data[i]);
  }
  printf("Data wey dey top of the queue: %d\n", peek(&queue));

  free(queue.data);
  return 0;
}
