/**
 * lp_oa_hash_table.c 
 *
 * Implementation of hash table using open addressing(linear probing) to handle collision in C.
 *
 * Wetin be hash table?
 * i don explain hash table and other concepts related to hash table for here ../../seperate-chaining/sc_hash_table.c

 * OPEN ADDRESSING: With open addressing, we no go introduce linked list or any other data structure inside the bucket. Instead,
 * if we use our hash index reach the bucket wey we go enter our data and if e dey empty, we go search for the next available position to put our data(aka probing).
 * Many methods of probing dey: Linear probing, quadratic probing, open hashing. any other one wey dey, i no know about am :(
 * I go only show implementation with linear probing here. You fit learn on the others wey dey, fork this repo, ad am then create pr, i go merge.
 *
 * I go show implementation of hash table here using open addressing - linear probing for collision handling.
 *
 *
 * Operations:
 * - Insertion: O(n)
 * - Deletion: O(n)
 * - Searching: O(n)
 * - Modification: O(n)
 *
 * Author: NULL
 * Date: 19/03/2025
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOAD_FACTOR_TRESHOLD 0.7

typedef enum { EMPTY, OCCUPIED, DELETED } TombStone;

typedef struct Bucket {
  char *key;
  int value;
} Bucket;

typedef struct HashTable {
  Bucket **buckets;
  TombStone *ts;
  int capacity;
  int size;
} HashTable;

// function delcaration(prototype)
void insert(HashTable *ht, char *key, int value);


/**
  * This function na to initialize the hash table, then add empty buckets.
  *
  * @param HashTable *ht Pointer to the hash table.
  * @param int capacity The number of buckets the hash table go get.
  */
void initHashTable(HashTable *ht, int capacity) {
  ht->buckets = (Bucket **) malloc(capacity * sizeof(Bucket));
  ht->ts = (TombStone *) malloc(capacity * sizeof(TombStone));
  if (ht->buckets == NULL || ht->ts == NULL) {
    printf("Memory allocation no gree work\n");
    free(ht->buckets);
    free(ht->ts);
    return;
  }

  for(int i = 0; i < capacity; i ++) {
    ht->buckets[i] = NULL;
    ht->ts[i] = EMPTY;
  }

  ht->capacity = capacity;
  ht->size = 0;
}


/**
  * This function na to hash our key so we fit get the index of a particular bucket - POLYNOMIAL ROLLING HASH.
  *
  * @param char *key The pointer to the key we wan hash.
  * @param int capacity The capacity/no of bucket wey the hash table get.
  *
  * @return int The index of the bucket.
  */
int hash(char *key, int capacity) {
  int keyVal = 0;
  for(int i = 0; key[i] != '\0'; i++) {
    keyVal = keyVal * 31 + key[i]; 
  }

  keyVal %= capacity;

  if(keyVal < 0) {
    keyVal += capacity;
  }

  return keyVal;
}


/**
  * This method na to resize a hash table(multiply the no of bucket by two).
  * The reason we dey do this na to reduce the chances of collision.
  *
  * @param HashTable *ht The pointer to the hash table we wan resize.
  */
void resize(HashTable *ht) {
  HashTable newHt;
  int newCapacity = ht->capacity * 2;

  initHashTable(&newHt, newCapacity);
  if(newHt.capacity == newCapacity) {
    for(int i = 0; i < ht->capacity; i ++) {
      insert(&newHt, ht->buckets[i]->key, ht->buckets[i]->value);
      free(ht->buckets[i]->key);
      free(ht->buckets[i]);
    }

    free(ht->ts);
    free(ht->buckets);

    ht->buckets = newHt.buckets;
    ht->ts = newHt.ts;
    ht->capacity = newHt.capacity;
    ht->size = newHt.size;
  }
}


/**
  * This function na to insert data(key & value) inside our hash table.
  *
  * @param HashTable *ht The pointer to the hash table we wan add the data.
  * @param char *key The pointer to the key.
  * @param int value The value wey dey associated to the key.
  */
void insert(HashTable *ht, char *key, int value) {
  if((ht->size / ht->capacity) >= LOAD_FACTOR_TRESHOLD) {
    resize(ht);
  }

  int index = hash(key, ht->capacity);

  if(ht->buckets[index] != NULL) {
    char *firstKey = ht->buckets[index]->key;
    while(ht->ts[index] == OCCUPIED) {
      // if key dey duplicate
      if(strcmp(ht->buckets[index]->key, key) == 0) {
        printf("Duplicate key\n");
        return;
      }

      index = (index + 1) % ht->capacity;
      
      if(ht->buckets[index] != NULL && ht->ts[index] == OCCUPIED)
        if(strcmp(ht->buckets[index]->key, firstKey) == 0) {
          printf("The hash table don full.\n");
          return;
        }
    }
  }

  // enter the new key&value.
  Bucket *bucket = (Bucket *) malloc(sizeof(Bucket));
  bucket->key = (char *) malloc((strlen(key) + 1) * sizeof(char));
  strcpy(bucket->key, key);
  bucket->value = value;
  ht->buckets[index] = bucket;
  ht->ts[index] = OCCUPIED;
  ht->size ++;
}


/**
  * This method na to search for bucket we dey hold a particular key.
  *
  * @param HashTable *ht The pointer to the hash table we wan search for the bucket from.
  * @param char *key The pointer to the key we wan search for.
  *
  * @return int index of the bucket wey dey hold the searched key or -1 if we no see any bucket with that key.
  */
int search(HashTable *ht, char *key) {
  int idx = hash(key, ht->capacity);
  int originalIdx = idx;

  do {
    if(ht->ts[idx] == EMPTY)
      break;
    else if(ht->ts[idx] == OCCUPIED && strcmp(ht->buckets[idx]->key, key) == 0)
      return idx;

    idx = (idx + 1) % ht->capacity;
  } while(idx != originalIdx);

  return -1;
}


/**
  * This function na to delete any key along with associated value inside bucket.
  *
  * @param HashTable *ht The pointer to the hash table we wan delete the data from.
  * @param char *key The pointer to the key we wey delete all associated data.
  */
void delete(HashTable *ht, char *key) {
  int index = search(ht, key);

  if(index >= 0)
    free(ht->buckets[index]->key);
    ht->buckets[index] = NULL;
    ht->ts[index] = DELETED;
    ht->size --;
}


/**
  * This function na to modify value wey dey associated with any key inside our hash table.
  *
  * @param HashTable *ht The pointer to the hash table wey hold the value we wan modify.
  * @param char *key The pointer to the key associated to the value we wan modify.
  * @param int value The value we wan modify.
  */
void modify(HashTable *ht, char *key, int value) {
  int index = search(ht, key);
  
  if(index >= 0)
    ht->buckets[index]->value = value;
}


/**
  * This function na to print all key and value wey dey inside any hash map.
  *
  * @param HashTable *ht The pointer to the hash table we wan print out all key & value from.
  */
void printHashTable(HashTable *ht) {
  for(int i = 0; i < ht->capacity; i ++) {
    if(ht->ts[i] == OCCUPIED) {
      printf("Key: %s --- Value: %d\n", ht->buckets[i]->key, ht->buckets[i]->value);
    }
  }
}


/**
  * This function na to free all availabe memory wey don allocate inside any hash table.
  * Normally, this function dey only dey called when we don finish all work we wan do with the hash table.
  *
  * @param HashTable *ht The pointer to the hash table we wan free.
  */
void freeHashTable(HashTable *ht) {
  for(int i = 0; i < ht->capacity; i ++) {
    if(ht->ts[i] != EMPTY) {
      if(ht->ts[i] == OCCUPIED) free(ht->buckets[i]->key);

      free(ht->buckets[i]);
    }
  }

  free(ht->buckets);
  free(ht->ts);
}


int main() {
  HashTable ht;
  initHashTable(&ht, 10);

  insert(&ht, "apple", 10);
  insert(&ht, "banana", 20);
  insert(&ht, "cherry", 30);
  insert(&ht, "date", 40);
  insert(&ht, "elderberry", 50);
  insert(&ht, "fig", 60);
  insert(&ht, "grape", 70);
  insert(&ht, "honeydew", 80);

  printHashTable(&ht);

  int resultIdx = search(&ht, "banana");
  if (resultIdx >= 0) {
    printf("\n\nFound: %s -> %d\n\n", ht.buckets[resultIdx]->key, ht.buckets[resultIdx]->value);
  } else {
    printf("\n\nKey not found\n\n");
  }

  delete(&ht, "banana");
  modify(&ht, "date", 400);

  printHashTable(&ht);

  freeHashTable(&ht);

  return 0;
}
