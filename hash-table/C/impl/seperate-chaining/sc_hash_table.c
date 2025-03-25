/**
 * sc_hash_table.c 
 *
 * Implementation of hash table using seperate chaining to handle collision in C.
 *
 * Wetin be hash table?
 * Hash table aka Hash map na data structure wey dey store data in key-value pairs. meaning say for every data you wan store, key must dey,
 * that key dey mapped to the data so e go dey very easy to acces.
 * To dey able to understand and implement hash tables, you must sabi these concepts:
 * 0. Bucket: The data wey dey inside hash table dey always dey stored inside array. Now every slot inside that array, them dey call am BUCKET.
 *            Example, if the array fit hold seven elements inside(array size = 7), then we fit say the hash table get 7 buckets inside.
 * 1. Hash function: This na function wey go convert our key, this key fit be string, or in rare case, number to index of a bucket.
 *                   The value wey we wan store go con dey inserted inside this bucket.
 * 2. Collision: This na when two keys after hash function don convert them, produce the same result(same thing as same index).
 *               Two methods i know of dey availabe and na one of the two people dey mostly use to take handle collision.
 *               The methods na: Seperate Chaining & Open Addressing.
 * 3. Resizing: Shey you know say the number of buckets na one of the factors wey dey affect collision. eg: hash table wey get 10 buckets,
 *              get more chances for collision to happen compared to hash table wey get 20 buckets.
 *              Because of that, na good practice to dey resize the array wey your value go enter(add more buckets) if e grow pass a particular size, but no be by force.
 *
 * SEPERATE CHAINING: This na one of the methods to use tackle collision, see how e dey work; Shey you remember say data inside hash table dey dey stored inside bucket,
 *                    you fit don reason am say each data dey dey stored inside one one bucket, you no dey wrong oo, but chances of collision na wetin we dey try avoid.
 *                    So because of that we go convert each bucket to linked list store all the data with collided index inside. Meaning say;
 *                    if three keys collide, we go store all three of those data as linked list inside that bucket.
 *
 * I go show implementation of hash table here using seperate chaining for collision handling.
 *
 *
 * Operations:
 * - Insertion: O(1)
 * - Deletion: O(n)
 * - Searching: O(n)
 * - Modification: O(n)
 *
 * Author: NULL
 * Date: 15/03/2025
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOAD_FACTOR_THRESHOLD 0.7

typedef struct Node {
  char *key;
  int value;
  struct Node *next;
} Node;

typedef struct HashMap {
  int noOfBuckets;
  int noOfElements;
  Node **buckets;
} HashMap;

// function declarations(prototype)
void insert(HashMap *hmap, char *key, int value);


/**
  * This function na to initialize the hash map with the with the number of buckets we want iniside.
  *
  * @param HashMap *hmap The pointer to the hash map we wan initialize.
  * @param int noOfBuckets The number of buckets we want inside the hashmap.
  */
void initHashMap(HashMap *hmap, int noOfBuckets) {
  hmap->buckets = (Node **) calloc(noOfBuckets, sizeof(Node*));
  if (hmap->buckets == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
  }

  hmap->noOfBuckets = noOfBuckets;
  hmap->noOfElements = 0;
}


/**
  * This function na to create node wey go dey the linked list inside our hash map bucket.
  *
  * @param char *key The pointer to the key this node go hold.
  * @param int value The value this node go hold.
  *
  * @return *Node The pointer to the created node.
  */
Node *createNode(char *key, int value) {
  Node *node = (Node *) malloc(sizeof(Node));
  if (node == NULL) {
    printf("Memory allocation failed\n");
    return NULL;
  }

  node->key = (char *) malloc((strlen(key) + 1) * sizeof(char));
  if (node->key == NULL) {
    printf("Memory allocation failed\n");
    free(node);
    return NULL;
  }

  strcpy(node->key, key);
  node->value = value;
  node->next = NULL;

  return node;
}


/**
  * This function na to hash our key so we fit get the index of the bucket the value go dey.
  * The calculation we go do to obtain this index, them dey call am POLYNOMIAL ROLLING HASH.
  *
  * @param char *key The pointer to the key we wan hash.
  * @param int capacity The capacity/no of bucket wey the hash table get.
  *
  * @return int The index of the bucket.
  */
int hash(char *key, int capacity) {
  // polynomilal rolling hash.
  int keyVal = 0;
  for (int i = 0; key[i] != '\0'; i++) {
    keyVal = (keyVal * 31) + key[i];
  }

  keyVal %= capacity;

  /**
  * omoo
  * body tell me before i find out say the polynomilal rolling hash for up fit result in negative index.
  * so i gats account for that.
  */
  if (keyVal < 0) {
    keyVal += capacity;
  }

  return keyVal;
}


/**
  * This method na to resize a hashmap(multiply the no of bucket by two).
  * The reason we dey do this na to reduce the chances of collision inside our hashmap.
  *
  * @param HashMap *hmap The pointer to the hash map we wan resize.
  */
void resizeHashMap(HashMap *hmap) {
  HashMap newHmap;
  int newNoOfBuckets = hmap->noOfBuckets * 2;

  // Initialize the new hash map
  initHashMap(&newHmap, newNoOfBuckets);

  // Copy elements from the old hash map to the new one
  for (int i = 0; i < hmap->noOfBuckets; i++) {
    Node *head = hmap->buckets[i];
    while (head != NULL) {
      insert(&newHmap, head->key, head->value);
      Node *temp = head;
      head = head->next;
      free(temp->key); // Free the old node's key
      free(temp);      // Free the old node
    }
  }

  // Free the old buckets array
  free(hmap->buckets);

  // Assign every data wey dey the new hash map to the original hash map
  hmap->buckets = newHmap.buckets;
  hmap->noOfBuckets = newHmap.noOfBuckets;
  hmap->noOfElements = newHmap.noOfElements;
}


/**
  * This method na to search for node we dey hold a particular key.
  *
  * @param HashMap *hmap The pointer to the hash map we wan search for this node from.
  * @param char *key The pointer to the key we wan search for.
  *
  * @return Node* Pointer to the node wey dey hold the searched key or NULL if we no see any node with that key.
  */
Node* search(HashMap *hmap, char *key) {
  int index = hash(key, hmap->noOfBuckets);
  Node *head = hmap->buckets[index];

  while (head != NULL) {
    if (strcmp(head->key, key) == 0) {
      return head;
    }
    head = head->next;
  }

  return NULL;
}


/**
  * This function na to insert data(key & value) inside our hash map.
  *
  * @param HashMap *hmap The pointer to the hashmap we wan add the data.
  * @param char *key The pointer to the key.
  * @param int value The value wey dey associated to the key.
  */
void insert(HashMap *hmap, char *key, int value) {
  if (hmap->noOfElements > 0) {
    float loadFactor = (float) hmap->noOfElements / hmap->noOfBuckets;
    if (loadFactor >= LOAD_FACTOR_THRESHOLD) {
      resizeHashMap(hmap);
    }
  }

  Node *existingNode = search(hmap, key);
  if (existingNode != NULL) {
    printf("Duplicate key.\n");
    return;
  }

  Node *newNode = createNode(key, value);
  if (newNode == NULL) {
    return;
  }

  int index = hash(key, hmap->noOfBuckets);
  newNode->next = hmap->buckets[index];
  hmap->buckets[index] = newNode;
  hmap->noOfElements++;
}


/**
  * This function na to delete any key along with associated value(same thing as node wey dey linked list inside bucket).
  *
  * @param HashMap *hmap The pointer to the hash map we wan delete the data from.
  * @param char *key The pointer to the key we wey delete all associated data.
  */
void delete(HashMap *hmap, char *key) {
  int index = hash(key, hmap->noOfBuckets);
  Node *head = hmap->buckets[index];
  Node *prevNode = NULL;

  while (head != NULL) {
    if (strcmp(head->key, key) == 0) {
      if (prevNode == NULL) {
        hmap->buckets[index] = head->next;
      } else {
        prevNode->next = head->next;
      }

      free(head->key);
      free(head);
      hmap->noOfElements--;
      return;
    }

    prevNode = head;
    head = head->next;
  }
}


/**
  * This function na to modify value wey dey associated with any key inside our hash map.
  *
  * @param HashMap *hmap The pointer to the hash map wey hold the value we wan modify.
  * @param char *key The pointer to the key associated to the value we wan modify.
  * @param int value The value we wan modify.
  */
void modify(HashMap *hmap, char *key, int value) {
  Node *node = search(hmap, key);
  if (node != NULL) {
    node->value = value;
  }
}


/**
  * This function na to print all key and value wey dey inside any hash map.
  *
  * @param HashMap *hmap The pointer to the hash map we wan print out all key & value from.
  */
void printHashMap(HashMap *hmap) {
  for (int i = 0; i < hmap->noOfBuckets; i++) {
    Node *node = hmap->buckets[i];
    while (node != NULL) {
      printf("Key: %s --- Value: %d\n", node->key, node->value);
      node = node->next;
    }
  }
}


/**
  * This function na to free all availabe memory wey don allocate inside any hashmap.
  * Normally, this function dey only dey called when we don finish all work we wan do with the hash map.
  *
  * @param HashMap *hmap The pointer to the hash map we wan free.
  */
void freeHashMap(HashMap *hmap) {
  for (int i = 0; i < hmap->noOfBuckets; i++) {
    Node *node = hmap->buckets[i];
    while (node != NULL) {
      Node *temp = node;
      node = node->next;
      free(temp->key);
      free(temp);
    }
  }
  free(hmap->buckets);
}

int main() {
  HashMap hmap;
  initHashMap(&hmap, 10);

  insert(&hmap, "apple", 10);
  insert(&hmap, "banana", 20);
  insert(&hmap, "cherry", 30);
  insert(&hmap, "date", 40);
  insert(&hmap, "elderberry", 50);
  insert(&hmap, "fig", 60);
  insert(&hmap, "grape", 70);
  insert(&hmap, "honeydew", 80);

  printHashMap(&hmap);

  Node *result = search(&hmap, "banana");
  if (result != NULL) {
    printf("\n\nFound: %s -> %d\n\n", result->key, result->value);
  } else {
    printf("\n\nKey not found\n\n");
  }

  delete(&hmap, "banana");
  modify(&hmap, "date", 400);

  printHashMap(&hmap);

  freeHashMap(&hmap);

  return 0;
}
