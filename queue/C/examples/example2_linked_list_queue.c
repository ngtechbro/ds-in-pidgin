/**
* example2_linked_list_queue.c 
*
* Example use case for linked list queue in C.
*
* WTD: We go just build simple restaurant order system wey go accept the dish name, and time(in seconds) wey e go take to process/make the dish.
* When we process the task, e go process all the orders(in this case; na just sleep for the time we expect the orders to dey process),
* but in real world, e go actually dey run any kind logic to compute time for the order processing.
*
* Author: NULL
* Date: 12/03/2025
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct Order {
  char *name;
  int time;
} Order;

typedef struct Node {
  Order data;
  struct Node *next;
} Node;

typedef struct LinkedListQueue {
  Node *top;
  int size;
} LinkedListQueue;


/**
  * This function na to initialize the order queue.
  *
  * @param LinkedListQueue *queue Pointer to the queue we wan initialize
  */
void initQueue(LinkedListQueue *queue) {
  queue->top = NULL;
  queue->size = 0;
} 


/**
  * This function na to add order to the queue.
  *
  * @param LinkedListQueue *queue The pointer to the queue
  * @param Order *order Pointer to the order we wan add to queue
  */
void addOrder(LinkedListQueue *queue, Order *order) {
  Node *node = (Node *) malloc(sizeof(Node));
  if(node == NULL) {
    printf("Memory allocation no gree work\n");
    return;
  }

  node->data.name = (char *) malloc((strlen(order->name) + 1) * sizeof(char));
  strcpy(node->data.name, order->name); 
  node->data.time = order->time;
  node->next = NULL;
  

  if(queue->size == 0) {
    queue->top = node;
  }
  else {
    Node *currNode = queue->top;
    while(currNode->next != NULL) currNode = currNode->next;

    currNode->next = node;
  }

  queue->size ++;
}


/**
  * This function na to process the order wey dey top of the queue.
  * This na in another word, popping from the queue.
  *
  * @param LinkedListQueue *queue Pointer to the linked list queue.
  */
void processTopOrder(LinkedListQueue *queue) {
  if(queue->size == 0) {
    printf("The queue dey empty");
    return;
  }

  Node *node = queue->top;
  queue->top = node->next;

  queue->size --;

  free(node->data.name);
  free(node);
}

int main() {
  LinkedListQueue queue;

  initQueue(&queue);

  while(1) {
    printf("\n");
    printf("*******************************************************************************\n");
    printf("*             Tuale Boss!! See available options wey dey:                     *\n");
    printf("*******************************************************************************\n");
    printf("* 1. Enter new order\n");
    printf("* 2. Process orders.\n");
    printf("* 0. Exit.\n");
    printf("*******************************************************************************\n");
    printf("* Total Orders: %d\n", queue.size);
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
        printf("\nEnter new order dish(<100): ");
        char dishName[100]; 
        fgets(dishName, sizeof(dishName), stdin);
        dishName[strcspn(dishName, "\n")] = '\0';

        // get time(in seconds) wey e go take to process
        int dishPrepTime;
        printf("\nEnter time(in seconds) e go take to process dish: ");
        scanf("%d", &dishPrepTime);

        Order newOrder;
        newOrder.name = dishName;
        newOrder.time = dishPrepTime;

        printf("Od name: %s", dishName);

        addOrder(&queue, &newOrder);
        printf("\n Order don dey added successfully!\n");

        break;
      case 2:
        printf("** PROCESSING FOOD ORDERS... **\n");
        if(queue.size == 0) {
          printf("No order dey to process\n");
          break;
        }

        printf("processing orders...\n");
        while(queue.size != 0) {
          Order order = queue.top->data;
          printf("DISH: %s\n", order.name);
          printf("PROCESSING TIME: %dsecs\n", order.time);

          sleep(order.time);
          processTopOrder(&queue);

          if(queue.size > 0) {
            printf("\ncurrent process complete, we dey move to the next order.\n");
          }
        }

        printf("\n\n** All orders don finish process **\n\n");
        break;
      default:
        printf("\n\nThe option wey you enter no dey make sense boss.\n\n");
        break;
    }
  }

  return 0;
}
