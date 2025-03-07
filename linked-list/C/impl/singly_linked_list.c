/**
* singly_linked_list.c 
*
* Implementation of singly linked list in C.
*
* Wetin be singly linked list?
* Singly linked list na type of linked list wey each node wey dey the list dey hold the data wey the list go store,
* and a pointer or reference to the next node. The first node of singly linked list, them dey call am HEAD,
* Singly linked list dey linear, and the TAIL dey always point to NULL.
*
* Operations:
* - Insertion: O(1)
* - Deletion: O(1)
* - Access: O(n)
* - Search: O(n)
*
* Author: NULL
* Date: 14/02/2024
**/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;   // assuming say na integer data we wan store.
  struct Node *next; // the pointer to the next node for the list, or null if na the tail node.
}Node;


/**
* This function na to create the node wey we go use for our linked list.
* After we don create am, we go set the node data to wetin dey our function argument,
* then we go set the next pointer to NULL.
*
* @param int val The value wey we plan assign to the data of our node.
*
* @return Node * Pointer to the created node.
*/
Node *createNode(int val) {
  Node *node;
  node = (Node *) malloc(sizeof(Node));
  if(node == NULL) {
    printf("Memory allocation for Node no work\n");
    exit(0);
  }

  node->data = val;   // set the node data.
  node->next = NULL;  

  return node;
}


/**
* This function na to add node to our linked list.
* First, we go create new node with the data wey we want make the node data hold,
* then we go add the node after the previous node we supply as argument.
*
* @param Node *prev The pointer to the node wey dey before where we wan add our new node.
* @param int data The value wey we want make our new node data hold
*
* @return Node * Pointer to the newly added node.
*/
Node *insert(Node *prev, int data) {
  Node *newNode = createNode(data);
  
  if(prev->next != NULL) {
    Node *nextNode = prev->next;
    newNode->next = nextNode;
  }

  prev->next = newNode;

  return newNode;
}


/**
* This function na to add node at the end of our linked list(remember say any node wey dey last, them dey call am TAIL).
* First, we go create new node with the data wey we want make the node data hold,
* then we go from HEAD, go the next node one after the other till we reach the TAIL(tail na where next pointer dey null) where we go add our new node.
*
* @param Node *node Any node wey dey the linked list.
* @param int data The value wey we want make our new node data hold
*
* @return Node * Pointer to the newly addeed node.
*/
Node *insertTail(Node *node, int data) {
  Node *newNode = createNode(data);

  while (node->next != NULL) {
    node = node->next;
  }

  node->next = newNode;

  return newNode;
}


/**
* This function na to delete node komot from our linked list.
* This function go delete the node wey dey after the previous node wey we supply as argument.
*
* @param Node *prev The node wey dey before the node wey we wan komot.
*
*/
void delete(Node *prev) {
  Node *current = prev->next;
  Node *next = current->next;
  prev->next = next;

  free(current);
}


/**
* This function na to get the tail(pointer) wey dey our linked list.
*
* @param Node *node Any node wey dey the linked list.
*
* @return Node * Pointer to the tail of our linked list.
*/
Node *getTail(Node *node) {
  while (node->next != NULL) {
    node = node->next;
  }

  return node;
}


/**
* This function na to search for node wey dey our linked list by value of data wey the node dey hold.
* We go from head of our linked list dey go through every next node till the tail until we find the node wey hold the data we dey find.
*
* @param Node *head Head pointer of our linked list.
* @param int val The value wey we dey search for.
*
* @return Node * Pointer to the node wey hold wetin we dey search for.
*/
Node *search(Node *head, int val) {
  Node *node = head;

  if(node->data == val)
    return node;

  while (node->next != NULL) {
    if(node->data == val)
      return node;
    
    node = node->next;
  }
}


/**
* This function na to free up all dynamically allocated memory wey we don set for each node.
* We go from head of our linked list dey go through every next node dey free up memory till we reach the tail.
* E dey important say we call this function when we finish work with our linked list so we no go waste memory(Java folks can't relate lol).
*
* @param Node *head Head pointer of our linked list.
*
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
 * ******************************************************************************************************
 * MAKE WE PLAY WITH OUR DATA STRUCTURE.
 **/

/**
* Print out wetin dey our linked list.
* 
* @param Node *head Head pointer of our linked list.
*/
void printLinkedList(Node *head) {
  int count = 1;
  Node *node = head;

  while (node->next != NULL) {
    if(count == 1)
      printf("HEAD-> Val: %d, pos: %d\n", node->data, count);
    else 
      printf("NODE-> Val: %d, pos: %d\n", node->data, count);

    node = node->next;
    count ++;
  }

  printf("TAIL-> Val: %d, pos: %d\n", node->data, count);

  printf("\n");
}

int main() {
  // create our first node(HEAD = TAIL)
  Node *head = createNode(1);

  // insert nodes inside our linked list.
  Node *offNode = insert(head, 9);
  insertTail(head, 11);
  Node *originalNode = insertTail(head, 3);
  insertTail(offNode, 7);

  printf("** AFTER ALL INSERT **\n");
  printLinkedList(head);

  // delete nodes from our linked list
  delete(head);
  delete(originalNode);

  printf("** AFTER ALL DELETE **\n");
  printLinkedList(head);

  printf("** GET TAIL FUNC **\n");
  // get the tail node
  Node *tail = getTail(head);
  printf("tail: %d\n\n", tail->data);

  // search for node and update data wey e hold.
  Node *searchedNode = search(head, 11);
  searchedNode->data = 2;
  printf("** AFTER UPDATING WITH A SEARCH FUNC **\n");
  printLinkedList(head);

  // free memory
  freeNodes(head);
}
