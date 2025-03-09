/**
* array_stack.c 
*
* Implementation of stack using arrays in C.
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

typedef struct Stack {
  int *data;    // the array wey we wan use implement the stack
  int size;     // the size of the array
  int capacity; // the array capacity
} ArrayStack;


/**
* This function na to initialize the stack.
*
* @param ArrayStack *stack The pointer to the stack.
**/
void initStack(ArrayStack *stack) {
  stack->capacity = 1;

  stack->data = (int *) malloc(stack->capacity * sizeof(int));
  if(stack->data == NULL) {
      printf("Memory allocation no gree work\n");
      return;
  }

  stack->size = 0;
}


/**
* This function na to add data to the top of the stack
*
* @param ArrayStack *stack The pointer to the stack.
* @param int val The value/data we wan add.
*/
void push(ArrayStack *stack, int val) {
  if(stack->size == stack->capacity ) {
    stack->capacity *= 2;
    stack->data = (int *) realloc(stack->data, stack->capacity * sizeof(int));
    
    if(stack->data == NULL) {
      printf("Memory reallocation no gree work\n");
      return;
    }
  }

  stack->data[stack->size] = val;
  stack->size ++;

  return;
}


/**
* This function na to komot data from the top of the stack.
* No forget say stack must follow the LIFO implementation.
*
* @param ArrayStack *stack The pointer to the stack.
*/ 
int pop(ArrayStack *stack) {
  if(stack->size == 0) {
    printf("Stack Underflow | The stack dey empty");
    return -1;
  }

  int tmp = stack->data[stack->size - 1];
    
  stack->size --;

  return tmp;
}


/**
* This function na to access the data wey dey the top of the stack.
*
* @param ArrayStack *stack The pointer to the stack.
*/ 
int peek(ArrayStack *stack) {
  if(stack->size == 0) {
    printf("Stack Underflow | The stack dey empty");
    return -1;
  }

  return stack->data[stack->size - 1];
}

int main() {
  ArrayStack stack;

  initStack(&stack);
  push(&stack, 1);
  push(&stack, 2);
  push(&stack, 4);
  pop(&stack);
  push(&stack, 6);
  push(&stack, 8);
  int topData = peek(&stack);

  for(int i = 0; i < stack.size; i ++) {
    printf("%d\n", stack.data[i]);
  }

  printf("Data wey dey top of stack: %d\n", topData);

  ArrayStack *stk = &stack;
  free(stk->data);

  return 0;
}
