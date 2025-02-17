/**
* example1_singly_linked_list.c 
*
* Example use case for using singly linked list in C.
*
* WTD: we go collect the grades of 5 students,
* we go calculate the sum and average, then we go print them out alongside the grades.
*
* Author: NULL
* Date: 14/02/2024
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESULT_NUM 5

// struct wey go store result data
typedef struct Result {
  char student[100];
  int grade;
} Result;

// node for our linked list
typedef struct Node {
  struct Result data;
  struct Node *next;
} Node;


/**
* This function na to create node then give am result data make e hold.
*
* @param Result result Result data wey we wan give the created node.
*
* @return Node * Pointer to the newly created node.
*/
Node *createNode(Result *result) {
  Node *newNode;

  newNode = (Node *) malloc(sizeof(Node));
  if(newNode == NULL) {
    printf("Memory allocation for new node no work");
    exit(0);
  }

  newNode->data = *result;
  newNode->next = NULL;

  return newNode;
}


/**
* This function go create node with result data wey we supply, then add am after any node wey we supply as argument.
*
* @param Node *node Pointer to the node we wan insert after.
* @param Result *result Pointer to the data of the newly created node.
*
* @return Node * Pointer to the newly created and inserted node.
*
*/
Node *insertAfter(Node *node, Result *result) {
  Node *newNode = createNode(result);

  Node *nextNode = node->next;
  newNode->next = nextNode;
  node->next = newNode;

  return newNode;
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
* This function go print the result or contents of our linked list from head to tail.
*
* @param Node *head The head pointer of the linked list.
*/
void printResultData(Node *head) {
  printf("\n");
  printf("*******************************************************************************\n");
  printf("*                              RESULT PRINT OUT                               *\n");
  printf("*******************************************************************************\n");

  int count = 1;
  int total = 0;

  while (head->next != NULL) {
    Result *result = &head->data;

    if(count > 1)
      printf("\n");

    printf("***  %d   ***\n*  Name: %s\n*  Grade: %d\n", count, result->student, result->grade);

    head = head->next;
    count ++;
    total += result->grade;
  }

  Result *result = &head->data;
  printf("\n***  %d   ***\n*  Name: %s\n*  Grade: %d\n", count, result->student, result->grade);

  printf("*******************************************************************************\n");
  printf("* TOTAL: %d *\n", total);
  printf("* AVERAGE: %d *\n", (total/RESULT_NUM));
  printf("*******************************************************************************\n");
}

int main() {
  printf("Tuale Boss!! Abeg enter result for %d students:\n", RESULT_NUM);

  Node *head;
  char studentName[100];
  int studentGrade;

  Node *node = NULL;
  for(int i = 1; i <= RESULT_NUM; i ++) {
    Result result;

    printf("Enter student %d name:", i);
    fgets(result.student, 99, stdin);
    result.student[strcspn(result.student, "\n")] = '\0';

    printf("Enter student %d grade:", i);
    scanf("%d", &result.grade);
    getchar();

    printf("\n");

    if(i == 1) {
      head = createNode(&result);
      node = head;
      continue;
    }

    node = insertAfter(node, &result);

  }

  printResultData(head);

  freeNodes(head);

  return 0;
}

