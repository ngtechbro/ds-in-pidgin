/**
* example1_sc_hash_table.c 
*
* Example use case for hash table with separate chaining collision handling technique in C.
*
* WTD: We go just build simple phone book. With this phone book, you fit store contact, search for contact, delete contacts, etc.
*
* Author: NULL
* Date: 21/03/2025
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOAD_FACTOR_TRESHOLD 0.7

typedef struct Node {
  char *name;
  char *number;
  struct Node *next;
} Node;

typedef struct PhoneBook {
  Node **contacts;
  int size;
  int capacity;
} PhoneBook;

void addContact(PhoneBook *pb, char *name, char *number);


/**
  * This function na to create the phone book.
  * Na the same thing as initializing the hash table.
  *
  * @param PhoneBook *pb Pointer to the phone book.
  * @param int capacity The number of contacts the phone book fit hold
  */
void createPhoneBook(PhoneBook *pb, int capacity) {
  pb->contacts = (Node **) malloc(capacity * sizeof(Node));
  if(pb->contacts == NULL) {
    printf("Memory allocation no gree work.\n");
    return;
  }

  for(int i = 0; i < capacity; i ++) {
    pb->contacts[i] = NULL;
  }

  pb->size = 0;
  pb->capacity = capacity;
}


/**
  * This function na to compute for the index of a particular contact from a key.
  * Normally, this contact go dey inside phone book.
  *
  * @param *key Pointer to the key to compute.
  * @param int capacity The total capacity of contacts the phone book fit carry.
  */
int hash(char *key, int capacity) {
  int keyVal = 0;
  for(int i = 0; key[i] != '\0'; i ++) {
    keyVal = keyVal * 31 + key[i];
  }

  keyVal %= capacity;

  if(keyVal < 0) {
    keyVal += capacity;
  }

  return keyVal;
}


/**
  * This function na to create new contact node, then return that node.
  *
  * @param char *name Pointer to the name of the new contact.
  * @param char *number Pointer to the number of the new contact.
  *
  * @return Node* Pointer to the new contact node.
  */
Node *createContact(char *name, char *number) {
  Node *node = (Node *) malloc(sizeof(Node));
  if(node == NULL) {
    printf("Memory allocation no gree work.\n");
    return NULL;
  }

  node->name = (char *) malloc((strlen(name) + 1) * sizeof(char));
  node->number = (char *) malloc((strlen(number) + 1) * sizeof(char));

  if(node->name == NULL || node->number == NULL) {
    printf("Memory allocation no gree work.\n");

    free(node->name);
    free(node->number);
    free(node);

    return NULL;
  }

  strcpy(node->name, name);
  strcpy(node->number, number);
  node->next = NULL;

  return node;
}


/**
  * This function na to search for a particular contact node by the the name of the contact.
  *
  * @param PhoneBook *pb Pointer to the phone book.
  * @param char *name Pointer to the name of the contact we go use carry out our search.
  *
  * @return Node* Pointer to the node wey dey hold same name as name we dey our func arg 2.
  * @return NULL If no contact node get same name as our search name.
  */
Node *searchContact(PhoneBook *pb, char *name) {
  int idx = hash(name, pb->capacity);

  Node *node = pb->contacts[idx];
  while(node != NULL) {
    if(strcmp(node->name, name) == 0) {
      return node;
    }

    node = node->next;
  }

  return NULL;
}


/**
  * This function na to increase the capacity of our phone book.
  * ie: increase the number of contacts our phone book go fit carry.
  *
  * @param PhoneBook *pb Pointer to the phone book we wan resize.
  */
void resizePhoneBook(PhoneBook *pb) {
  PhoneBook newPb;
  int newCapacity = pb->capacity * 2;

  createPhoneBook(&newPb, newCapacity);

  for(int i = 0; i < pb->capacity; i ++) {
    if(pb->contacts[i] != NULL) {
      Node *node = pb->contacts[i];
      while(node != NULL) {
        addContact(&newPb, node->name, node->number);

        free(node->name);
        free(node->number);
        free(node);

        node = node->next;
      }
    }
  }
  
  free(pb->contacts);
  
  pb->contacts = newPb.contacts;
  pb->size = newPb.size;
  pb->capacity = newPb.capacity;
}


/**
  * This function na to add new contact inside our phone book.
  *
  * @param PhoneBook *pb Pointer to the phone book we wan add the contact to.
  * @param char *name Pointer to the name of the contact we wan add.
  * @param char *number Pointer to the number of the contact we wan add.
  */
void addContact(PhoneBook *pb, char *name, char *number) {
  if((pb->size/pb->capacity) >= LOAD_FACTOR_TRESHOLD) {
    resizePhoneBook(pb);
  }

  Node *duplicateNode = searchContact(pb, name);
  if(duplicateNode != NULL) {
    printf("This name already dey this phone book\n");
    return;
  }
  
  Node *node = createContact(name, number);

  int idx = hash(name, pb->capacity);
  Node *contact = pb->contacts[idx];
  node->next = contact;
  pb->contacts[idx] = node;
  pb->size ++;
}


/**
  * This function na to edit or modify a particular contact number inside phone book.
  *
  * @param char *name Pointer to the name of the contact wey dey paired with the number we wan edit.
  * @param char *number Pointer to the number we wan edit.
  */
void editContact(PhoneBook *pb, char *name, char *number) {
  Node *node = searchContact(pb, name);
  if(node != NULL) {
    strcpy(node->number, number);
    return;
  }

  printf("Contact no dey with that name.\n");
}


/**
  * This function na to delete contact komot from phone book.
  *
  * @param PhoneBook *pb Pointer to the phone book we wan delete the contact from.
  * @param char *name Pointer to the name of the contact we wan delete.
  */
void deleteContact(PhoneBook *pb, char *name) {
  int idx = hash(name, pb->capacity);

  Node *node = pb->contacts[idx];
  Node *prev = NULL;
  while(node != NULL) {
    if(strcmp(node->name, name) == 0) {
      if(prev == NULL) {
        pb->contacts[idx] = node->next;
      }
      else {
        prev->next = node->next;
      }

      free(node->name);
      free(node->number);
      free(node);

      pb->size --;

      return;
    }

    prev = node;
    node = node->next;
  }
}


/**
  * This function na to print all key and value wey dey inside any phone book.
  *
  * @param PhoneBook *pb The pointer to the phone book we wan print out all contacts from.
  */
void printPhoneBook(PhoneBook *pb) {
  for (int i = 0; i < pb->capacity; i++) {
    Node *node = pb->contacts[i];
    while (node != NULL) {
      printf("Name: %s --- Number: %s\n", node->name, node->number);
      node = node->next;
    }
  }
}


/**
  * This function na to free all memory we don allocate to this phone book.
  *
  * @param PhoneBook *pb Pointer to the phone book we want to free.
  */
void freePhoneBook(PhoneBook *pb) {
  for(int i = 0; i < pb->capacity; i ++) {
    Node *node = pb->contacts[i];
    while(node != NULL) {
      free(node->name);
      free(node->number);

      Node *tmp = node;
      node = node->next;
      
      free(tmp);
    }
  }

  free(pb->contacts);
}


int main() {
  PhoneBook pb;
  createPhoneBook(&pb, 5);

  while(1) {
    printf("\n");
    printf("*******************************************************************************\n");
    printf("*             Tuale Boss!! See available options wey dey:                     *\n");
    printf("*******************************************************************************\n");
    printf("* 1. Enter new contact\n");
    printf("* 2. Edit contact.\n");
    printf("* 3. Delete contact.\n");
    printf("* 4. Print contacts.\n");
    printf("* 0. Exit.\n");
    printf("*******************************************************************************\n");
    printf("* Total contacts: %d\n", pb.size);
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
        // get name
        printf("\nEnter contact name(<100): ");
        char name[100]; 
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';

        // get number
        printf("\nEnter contact number: ");
        char number[100]; 
        fgets(number, sizeof(number), stdin);
        number[strcspn(number, "\n")] = '\0';

        addContact(&pb, name, number);
        printf("\n Contact don dey added successfully!\n");

        break;
      case 2:
        // get name
        printf("\nEnter contact name to edit: ");
        char nameToEdit[100]; 
        fgets(nameToEdit, sizeof(nameToEdit), stdin);
        nameToEdit[strcspn(nameToEdit, "\n")] = '\0';

        Node *node = searchContact(&pb, nameToEdit);
        if(node == NULL) {
          printf("No contact with that name.\n");
          break;
        }
       
        // get number
        printf("\nEnter contact new number(old number: %s): ", node->number);
        char numberToEdit[100]; 
        fgets(numberToEdit, sizeof(numberToEdit), stdin);
        numberToEdit[strcspn(numberToEdit, "\n")] = '\0';

        editContact(&pb, nameToEdit, numberToEdit);

        break;
      case 3:
        // get name
        printf("\nEnter contact name to delete: ");
        char nameToDelete[100]; 
        fgets(nameToDelete, sizeof(nameToDelete), stdin);
        nameToDelete[strcspn(nameToDelete, "\n")] = '\0';

        Node *nd = searchContact(&pb, nameToDelete);
        if(nd == NULL) {
          printf("No contact with that name.\n");
          break;
        }

        deleteContact(&pb, nameToDelete);

        break;
      case 4:
        printPhoneBook(&pb);

        break;
      default:
        printf("\n\nThe option wey you enter no dey make sense boss.\n\n");
        break;
    }
  }

  freePhoneBook(&pb);

  return 0;
}
