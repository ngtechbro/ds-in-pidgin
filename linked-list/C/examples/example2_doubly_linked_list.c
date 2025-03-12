/**
* example2_doubly_linked_list.c 
*
* Example use case for using doubly linked list in C.
*
* WTD: Our program go get options where users fit enter urls, navigate to next and previous urls, then delete urls.
*
* Author: NULL
* Date: 14/02/2025
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESULT_NUM 5

// node for our linked list
typedef struct Node {
  char url[100];
  struct Node *next;
  struct Node *prev;
} Node;


/**
* This function na to create node, then store url inside.
*
* @param char url Pointer to the url data wey we wan save inside the created node.
*
* @return Node * Pointer to the newly created node.
*/
Node *createNode(char *url) {
  Node *newNode;

  newNode = (Node *) malloc(sizeof(Node));
  if(newNode == NULL) {
    printf("Memory allocation for new node no work");
    exit(0);
  }

  strcpy(newNode->url, url);
  newNode->next = NULL;
  newNode->prev = NULL;

  return newNode;
}


/**
* This function go create node with url wey we supply, then add am for the end of the linked list.
*
* @param Node *head Pointer to the head of the linked list.
* @param char *url Pointer to the url we wan save inside the created node.
*
* @return Node * Pointer to the newly created and inserted node.
*
*/
Node *insertTail(Node *head, char *url) {
  Node *newNode = createNode(url);

  Node *node = head;
  while(node->next != NULL) {
    node = node->next;
  }

  node->next = newNode;
  newNode->prev = node;

  return newNode;
}


/**
* This function go delete the node we pass as argument
*
* @param Node *node Pointer to the node we wan delete.
*/
void deleteNode(Node *node) {
  if(node == NULL) {
    printf("Omo, this node no dey recognized");
    exit(0);
  }

  Node *nextNode = node->next;
  Node *prevNode = node->prev;
  
  prevNode->next = nextNode;
  nextNode->prev = prevNode;

  free(node);
}


/**
* This function na to free up all dynamically allocated memory wey we don set for each node.
*
* @param Node *head Head pointer of our linked list.
*/
void freeNodes(Node *head) {
  Node *currNode = head;
  Node *nextNode;

  while (currNode->next != NULL) {
    nextNode = currNode->next;
    free(currNode);
    currNode = nextNode;
  }

  free(currNode);
}


int main() {
  Node *currNode = NULL, *head = NULL;

  while(1) {
    printf("\n");
    printf("*******************************************************************************\n");
    printf("*             Tuale Boss!! See available options wey dey:                     *\n");
    printf("*******************************************************************************\n");
    printf("* 1. Enter new url.\n");
    printf("* 2. Go the next url.\n");
    printf("* 3. Go the previous url.\n");
    printf("* 4. Delete current url.\n");
    printf("* 0. Exit.\n");
    printf("*******************************************************************************\n");
    printf("* CURRENT URL: %s\n", currNode == NULL ? "No url" : currNode->url);
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
        printf("\nEnter url: ");
        char url[100];
        fgets(url, 99, stdin);
        url[strcspn(url, "\n")] = '\0';

        if(head == NULL) {
          head = createNode(url);
          currNode = head;
        }
        else {
          currNode = insertTail(head, url);
        }

        break;
      case 2:
        if(currNode->next != NULL)
          currNode = currNode->next;

        printf("We don move go the next url\n");
        break;
      case 3:
        if(currNode->prev != NULL)
          currNode = currNode->prev;

        printf("We do go back to the previous url.\n");
        break;
      case 4:
        Node *nodeToDelete = currNode;

        if(currNode->prev != NULL)
          currNode = currNode->prev;
        else if(currNode->next != NULL)
          currNode = currNode->next;

        deleteNode(nodeToDelete);

        printf("The url don komot.\n");
        break;
      default:
        printf("The option wey you enter no dey make sense boss.\n");
        break;
    }
  }

  freeNodes(head);

  return 0;
}

