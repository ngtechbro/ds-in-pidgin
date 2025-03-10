/**
* example2_linked_list_stack.c 
*
* Example use case for linked list stack in C.
*
* WTD: We go try mimic the undo and redo action if person dey type. we go only perform the action per character
* undo go pop from the stack, while redo go push popped character back to the stack.
* PS: i been try this thing with singly linked list, but because of the inversion, the typed words in full no dey make sense,
*     so i gats use doubly linked list
*
* Author: NULL
* Date: 09/03/2025
**/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node {
  char *typedText;
  struct Node *next;
  struct Node *prev;
} Node;

typedef struct Stack {
  Node *top;    // the node wey we wan use point to the top of the stack.
  Node *bottom;
  int size;     // the size of the stack.
} LinkedListStack;


/**
* This function na to initialize the stack.
*
* @param LinkedListStack *stack The pointer to the stack.
**/
void initStack(LinkedListStack *stack) {
  stack->top = NULL;
  stack->bottom = NULL;
  stack->size = 0;
}


/**
* This function na to add data to the top of the stack
*
* @param LinkedListStack *stack The pointer to the stack.
* @param char *text Pointer to new text wey user type
*/
void push(LinkedListStack *stack, char *text) {
  Node *node = (Node *) malloc(sizeof(Node));
  if(node == NULL) {
    printf("Memory allocation for node no gree work\n");
    return;
  }

  node->typedText = (char *) malloc((strlen(text) + 1) * sizeof(char));
  if(node->typedText == NULL) {
    printf("Memory allocation for node no gree work\n");
    free(node);
    return;
  }

  strcpy(node->typedText, text);

  if(stack->top == NULL) {
    node->next = NULL;
    stack->bottom = node;
  }
  else {
    Node *tmp = stack->top;
    tmp->prev = node;
    node->next = tmp;
  }

  node->prev = NULL;
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
char* pop(LinkedListStack *stack) {
  if(stack->size == 0) {
    printf("Stack Underflow | The stack dey empty");
    return NULL;
  }

  Node *tmp = stack->top;
  stack->top = tmp->next;
  if (stack->top != NULL) {
    stack->top->prev = NULL;
  }
  
  stack->size--;
  char *poppedData = tmp->typedText;

  free(tmp);

  return poppedData;
}


/**
* This function na to access the data wey dey the top of the stack.
*
* @param LinkedListStack *stack The pointer to the stack.
*/ 
char* peek(LinkedListStack *stack) {
  if(stack->size == 0) {
    printf("Stack Underflow | The stack dey empty");
    return NULL;
  }

  return stack->top->typedText;
}


/**
 * This function na to concat all the typed text so we fit display am.
 *
 * @return char* Pointer to the concatenated string(i mean the whole text)
 */
char* getTypedText(LinkedListStack *stack) {
  if(stack == NULL || stack->top == NULL) return NULL;
  
  Node *node = stack->bottom;
  int totalLength = 0;

  // Calculate total length we go need for the concatenated string
  while (node != NULL) {
    totalLength += strlen(node->typedText);
    node = node->prev;
  }

  // Allocate memory for the concatenated string
  char *typedText = (char *) malloc((totalLength + 1) * sizeof(char));
  if (typedText == NULL) {
    printf("Memory allocation failed\n");
    return NULL;
  }

  typedText[0] = '\0'; // e gats first dey empty

  node = stack->bottom;
  while (node != NULL) {
    strcat(typedText, node->typedText);
    node = node->prev;
  }

  return typedText;
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
    free(tmp->typedText);
    free(tmp);
  }

  free(node);
}


int main() {
  LinkedListStack undoStack, redoStack;
  initStack(&undoStack);
  initStack(&redoStack);

  while(1) {
    char *displayText = getTypedText(&undoStack);

    printf("\n");
    printf("*******************************************************************************\n");
    printf("*             Tuale Boss!! See available options wey dey:                     *\n");
    printf("*******************************************************************************\n");
    printf("* 1. Type any word or phrase or sentence.\n");
    printf("* 2. Undo.\n");
    printf("* 3. Redo.\n");
    printf("* 0. Exit.\n");
    printf("*******************************************************************************\n");
    printf("* TYPED TEXT: %s\n", displayText == NULL ? "" : displayText);
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
        printf("\nType any word/phrase/sentence(<100): ");
        char text[100]; 
        fgets(text, sizeof(text), stdin);

        text[strcspn(text, "\n")] = '\0';

        push(&undoStack, text);

        break;
      case 2:
        if(undoStack.top == NULL) {
          break;
        }
        char *poppedUndo = pop(&undoStack);
        push(&redoStack, poppedUndo);

        printf("\n\nUndo successfull!!\n\n");
        break;
      case 3:
        if(redoStack.top == NULL) {
          break;
        }
        char *poppedRedo = pop(&redoStack);
        push(&undoStack, poppedRedo);

        printf("\n\nRedo successfull!!\n\n");
        break;
      default:
        printf("\n\nThe option wey you enter no dey make sense boss.\n\n");
        break;
    }
  }

  LinkedListStack *stk0 = &undoStack;
  LinkedListStack *stk1 = &redoStack;
  freeNodes(stk0->top);
  freeNodes(stk1->top);

  return 0;
}
