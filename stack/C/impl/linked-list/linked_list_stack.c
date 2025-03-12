/**
* linked_list_stack.c 
*
* Implementation of stack using linked list in C.
*
* Wetin be stack?
* Stack na a type of linear data structure wey dey follow the "Last in First out" (LIFO) principle.
* Wetin this mean na say data go dey arranged in the stack in a linear order,
* the last data/content wey you put inside must be the first to komot if you dey do any remove operation ontop that stack.
* JUST KNOW SAY THE LOGIC BEHIND STACK NA SAY THE DATA WEY LAST ENTER, NA WETIN GO FIRST KOMOT IF YOU WAN DO ANY REMOVING.
* You fit implement stack with arrays or linked list provided say you follow the logic.
*
* Operations:
* - Push(to add data): O(1)
* - Pop(to komot data): O(1)
* - Peek(to get the top data): O(1)
*
* Author: NULL
* Date: 09/03/2025
**/

#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
  int data;
  struct Node *next;
} Node;

typedef struct Stack {
  Node *top;    // the node wey we wan use point to the top of the stack.
  int size;     // the size of the stack.
} LinkedListStack;


/**
* This function na to initialize the stack.
*
* @param LinkedListStack *stack The pointer to the stack.
**/
void initStack(LinkedListStack *stack) {
  stack->top = NULL;
  stack->size = 0;
}


/**
* This function na to add data to the top of the stack
*
* @param LinkedListStack *stack The pointer to the stack.
* @param int val The value/data we wan add.
*/
void push(LinkedListStack *stack, int val) {
  Node *node = (Node *) malloc(sizeof(Node));
  if(node == NULL) {
    printf("Memory allocation for node no gree work\n");
    return;
  }

  node->data = val;

  if(stack->top == NULL) {
    node->next = NULL;
  }
  else {
    Node *tmp = stack->top;
    node->next = tmp;
  }

  stack->top = node;
  stack->size ++;

  return;
}


/**
* This function na to komot data from the top of the stack.
* No forget say stack must follow the LIFO implementation.
*
* @param LinkedListStack *stack The pointer to the stack.
*/ 
int pop(LinkedListStack *stack) {
  if(stack->size == 0) {
    printf("Stack Underflow | The stack dey empty");
    return -1;
  }

  Node *tmp = stack->top;
  stack->top = tmp->next;
  stack->size --;
  int poppedData = tmp->data;

  free(tmp);

  return poppedData;
}


/**
* This function na to access the data wey dey the top of the stack.
*
* @param LinkedListStack *stack The pointer to the stack.
*/ 
int peek(LinkedListStack *stack) {
  if(stack->size == 0) {
    printf("Stack Underflow | The stack dey empty");
    return -1;
  }

  return stack->top->data;
}


/**
* This function na to free up nodes wey dey the linked list we use implement our stack.
*/ 
void freeNodes(Node *node) {
  if(node == NULL) {
    printf("Node already dey null");
    return;
  }

  while(node->next != NULL) {
    Node *tmp = node;
    node = node->next;
    free(tmp);
  }

  free(node);
}


int main() {
  LinkedListStack stack;

  initStack(&stack);
  push(&stack, 1);
  push(&stack, 2);
  push(&stack, 4);
  pop(&stack);
  push(&stack, 6);
  push(&stack, 8);
  int topData = peek(&stack);

  Node *node = stack.top;
  while(node->next != NULL) {
    printf("%d\n", node->data);

    node = node->next;
  }

  printf("%d\n", node->data);

  printf("Data wey dey top of stack: %d\n", topData);

  LinkedListStack *stk = &stack;
  freeNodes(stk->top);

  return 0;
}
