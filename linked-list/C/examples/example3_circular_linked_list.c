/**
* example3_circular_linked_list.c 
*
* Example use case for using circular linked list in C.
*
* WTD: we go create music playlist simulator with some songs inside,
* we go con implement functionalities to play next and previous songs,
* then func for adding to and removing from the playlist.
*
* Author: NULL
* Date: 15/02/2025
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// node for our linked list
typedef struct Node {
  char song[100];
  struct Node *next;
} Node;


/**
* This function na to create node then give am song make e hold.
*
* @param char *song Pointer to the song wey we wan give the created node.
*
* @return Node * Pointer to the newly created node.
*/
Node *createNode(char *song) {
  Node *newNode;

  newNode = (Node *) malloc(sizeof(Node));
  if(newNode == NULL) {
    printf("Memory allocation for new node no work");
    exit(0);
  }

  strcpy(newNode->song, song);
  newNode->next = newNode;

  return newNode;
}


/**
* This function go create tail node with song wey we supply.
*
* @param Node *head Pointer to the head node.
* @param char *song Pointer to the song of the newly created node.
*
* @return Node * Pointer to the newly created and inserted node.
*
*/
Node *insertTail(Node *head, char *song) {
  Node *node = head;
  Node *newNode = createNode(song);

  while(node->next != head) {
    node = node->next;
  }

  newNode->next = head;
  node->next = newNode;

  return newNode;
}


void deleteNode(Node *node) {
  if(node == NULL) {
    printf("This node no dey recognized\n");
    exit(0);
  }

  Node *currNode = node;
  while(currNode->next != node) {
    currNode = currNode->next;
  }

  currNode->next = node->next;

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


/**
* This function go print the songs or contents of our linked-list/playlist from head to tail.
*
* @param Node *head The head pointer of the linked list.
*/
void printSongs(Node *head) {
  printf("\n");
  // printf("*******************************************************************************\n");
  printf("*-------                         PLAYLIST CONTENT                      -------*\n");
  // printf("*******************************************************************************\n");

  if(head == NULL) {
    printf("*                                                                              \n");
    printf("*                        No song in playlist                                   \n");
    printf("*                                                                              \n");
    printf("*******************************************************************************\n");
    return; 
  }

  int count = 1;
  Node *headNode = head;

  printf("\n");
  while (headNode->next != head) {

    printf("*  %d. %s\n", count, headNode->song);

    headNode = headNode->next;
    count ++;
  }

  printf("*  %d. %s\n", count, headNode->song);

  printf("\n*******************************************************************************\n");
  printf("* TOTAL: %d %s *\n", count, count > 1 ? "songs" : "song");
  printf("*******************************************************************************\n");
}

int main() {
  Node *currNode = NULL, *head = NULL;

  head = createNode("Burna Boy - 23");    // This guy dey sing, e no get wetin anybody wan tell me.
  insertTail(head, "Bnxn - I Do");       // If you put mind say you go learn this stuff, you go learn am.
  insertTail(head, "kendric Lamar - Man at the garden");  // I DESERVE IT ALL!!!!

  currNode = head;

  while(1) {
    printf("\n");
    printf("*******************************************************************************\n");
    printf("*             Tuale Boss!! See available options wey dey:                     *\n");
    printf("*******************************************************************************\n");
    printf("* 1. Enter new song.\n");
    printf("* 2. Go the next song.\n");
    printf("* 3. Go the previous song.\n");
    printf("* 4. Delete current song.\n");
    printf("* 0. Exit.\n");
    printf("*******************************************************************************\n");
    printf("* NOW PLAYING: %s\n", currNode == NULL ? "No song available" : currNode->song);
    printf("*******************************************************************************\n");

    printSongs(head);

    printf("\nEnter your option: \n");

    int option;
    scanf("%d", &option);

    getchar();

    switch (option) {
      case 0:
        printf("Exiting program...\n");
        return 0;
      case 1:
        printf("\nEnter song: ");
        char song[100];
        fgets(song, 99, stdin);
        song[strcspn(song, "\n")] = '\0';

        if(head == NULL) {
          head = createNode(song);
          currNode = head;
        }
        else {
          insertTail(head, song);
        }

        break;
      case 2:
        if(currNode != NULL)
          currNode = currNode->next;

        printf("\n\nWe don move go the next song\n\n");
        break;
      case 3:
        Node *node = currNode;
        if(currNode != NULL)
          while(node->next != currNode)
            node = node->next;

        currNode = node;

        printf("\n\nWe do go back to the previous song.\n\n");
        break;
      case 4:
        Node *nodeToDelete = currNode;

        if(currNode != NULL)
          currNode = currNode->next;

        deleteNode(nodeToDelete);
        printf("\n\nThe song don komot.\n\n");
        break;
      default:
        printf("\n\nThe option wey you enter no dey make sense boss.\n\n");
        break;
    }
  }

  freeNodes(head);

  return 0;
}

