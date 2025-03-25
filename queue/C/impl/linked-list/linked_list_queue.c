/**
 * linked_list_queue.c 
 *
 * Implementation of queue using linked list in C.
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
 * - Push(to add data): O(n) - If you use doubly linked list, na constant time complexity O(1)
 * - Pop(to komot data): O(1)
 * - Peek(to get the top data): O(1)
 *
 * Author: NULL
 * Date: 12/03/2025
 **/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
  int data;
  struct Node *next;
} Node;

typedef struct LinkedListQueue {
  Node *top;
  int size;
} LinkedListQueue;


/**
  * This function na to initialize the queue.
  *
  * @param LinkedListQueue *queue The pointer to the linked list queue.
  */
void initQueue(LinkedListQueue *queue) { 
  queue->top = NULL;
  queue->size = 0;
}


/**
  * This function na to push to the queue.
  *
  * @param LinkedListQueue *queue The pointer to the queue.
  * @param int data The data we plan to push to the queue.
  */
void push(LinkedListQueue *queue, int data) {
  Node *node = (Node *) malloc(sizeof(Node));
  if(node == NULL) {
    printf("Memory allocation no gree work\n");
    return;
  }

  node->data = data;

  if(queue->size == 0) {
    queue->top = node;
  }
  else {
    Node *tail;
    Node *currNode = queue->top;
    while(currNode->next != NULL) {
      currNode = currNode->next;
    }
    tail = currNode;
    tail->next = node;
  }

  node->next = NULL;
  queue->size ++;
}


/**
  * This function na to pop data komot from the queue.
  * Remember say just like line for bank, the first/oldest entered data an im go first komot.
  *
  * @param LinkedListQueue *queue The pointer to the queue.
  *
  * @return int The popped data.
  */
int pop(LinkedListQueue *queue) {
  if(queue->size == 0) {
    printf("The queue dey empty.\n");
    return -1;
  }

  Node *currNode = queue->top;
  if(queue->size == 1) {
    queue->top = NULL;
  }
  else {
    queue->top = currNode->next;
  }

  queue->size --;
  
  int poppedData = currNode->data;

  free(currNode);

  return poppedData;
}


/**
  * This function na to get the data wey dey top of the queue.
  *
  * @return int The data at the top of the queue.
  */
int peek(LinkedListQueue *queue) {
  return queue->top->data;
}


void freeNodes(Node *top) {
  while(top->next != NULL) {
    Node *currNode = top;

    top = top->next;
    free(currNode);
  }

  free(top);
}

int main() {
  LinkedListQueue queue;

  initQueue(&queue);

  push(&queue, 0);
  push(&queue, 1);
  push(&queue, 2);
  push(&queue, 3);
  push(&queue, 4);

  pop(&queue);

  Node *node = queue.top;
  while(node->next != NULL) {
    printf("%d\n", node->data);

    node = node->next;
  }
  printf("%d\n", node->data);

  printf("Data wey dey top of the queue: %d\n", peek(&queue));

  freeNodes(queue.top);
  return 0;
}
