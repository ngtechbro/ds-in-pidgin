/**
* example1_array_stack.c 
*
* Example use case for array stack in C.
*
* WTD: We go do some navigations to different urls, then we go mimic browser back button nav.
* wetin the back button dey expected to do na to pop from the stack.
*
* Author: NULL
* Date: 09/03/2025
**/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Stack {
  char **urls;
  int size;
  int capacity;
} ArrayStack;


/**
* This function na to initialize the stack.
*
* @param ArrayStack *stack The pointer to the stack.
**/
void initStack(ArrayStack *stack) {
  stack->capacity = 1;

  stack->urls = (char **) malloc(stack->capacity * sizeof(char));
  if(stack->urls == NULL) {
      printf("Memory allocation no gree work\n");
      return;
  }

  stack->size = 0;
}


/**
* This function na to visit new url.
* This na same thing as visitUrling the url to the stack.
*
* @param ArrayStack *stack The pointer to the stack.
* @param char *url The pointer to the url we wan navigate to.
*/
void visitUrl(ArrayStack *stack, char *url) {
  if(stack->size == stack->capacity ) {
    stack->capacity *= 2;
    stack->urls = (char **) realloc(stack->urls, stack->capacity * sizeof(int));
    
    if(stack->urls == NULL) {
      printf("Memory reallocation no gree work\n");
      return;
    }
  }

  stack->urls[stack->size] = (char *) malloc((strlen(url) + 1) * sizeof(char));
  if(stack->urls[stack->size] == NULL) {
    printf("Memory allocation no gree work\n");
    return;
  }

  strcpy(stack->urls[stack->size], url);
  stack->size ++;

  return;
}


/**
* This function na to go back to the previously visited url.
* This na same thing as poping from the stack, so the new top of the stack na the url we wan go back to.
*
* @param ArrayStack *stack The pointer to the stack.
*/ 
void back(ArrayStack *stack) {
  if(stack->size == 0) {
    printf("Stack Underflow | The stack dey empty");
    return;
  }

  // printf("\nNavigating back...\n");

  char *tmp = stack->urls[stack->size - 1];
  free(tmp);

  stack->size --;

  return;
}


/**
* This function na to access the data wey dey the top of the stack.
*
* @param ArrayStack *stack The pointer to the stack.
*/ 
char* peek(ArrayStack *stack) {
  if(stack->size == 0) {
    printf("Stack Underflow | The stack dey empty");
    return '\0';
  }

  return stack->urls[stack->size - 1];
}

int main() {
  ArrayStack stack;

  initStack(&stack);

  while(1) {
    char *topData = peek(&stack);

    printf("\n");
    printf("*******************************************************************************\n");
    printf("*             Tuale Boss!! See available options wey dey:                     *\n");
    printf("*******************************************************************************\n");
    printf("* 1. Enter new url\n");
    printf("* 2. Back.\n");
    printf("* 0. Exit.\n");
    printf("*******************************************************************************\n");
    printf("* CURRENT URL: %s\n", topData == NULL ? "" : topData);
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
        printf("\nEnter new url: ");
        char text[100]; 
        fgets(text, sizeof(text), stdin);

        text[strcspn(text, "\n")] = '\0';

        visitUrl(&stack, text);

        break;
      case 2:
        back(&stack);

        printf("\n\nBack to previous url!!\n\n");
        break;
      default:
        printf("\n\nThe option wey you enter no dey make sense boss.\n\n");
        break;
    }
  }


  ArrayStack *stk = &stack;
  free(stk->urls);

  return 0;
}
