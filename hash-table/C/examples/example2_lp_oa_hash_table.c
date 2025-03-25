/**
* example2_lp_oa_hash_table.c 
*
* Example use case for hash table with open addressing(linear probing) collision handling technique in C.
*
* WTD: We go just build simple sentence word counter. Wetin our program go do be say: e go collect sentence as input,
* then count the number of times each word inside that sentence appear.
*
* Author: NULL
* Date: 24/03/2025
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LOAD_FACTOR_TRESHOLD 0.7

typedef enum { EMPTY, DELETED, OCCUPIED } TombStone;

typedef struct Bucket {
  char *word;
  int occurance;
} Bucket;

typedef struct Ht {
  Bucket **buckets;
  TombStone *ts;
  int size;
  int capacity;
} Ht;

void addWord(Ht *ht, char *word);


/**
  * This function na to create the hash table where we go store all the words and number of occurance.
  * Na the same thing as initializing the hash table.
  *
  * @param Ht *ht Pointer to the hash table.
  * @param int capacity The number of buckets the hash table go get.
  */
void createHt(Ht *ht, int capacity) {
  ht->buckets = (Bucket **) malloc(capacity * sizeof(Bucket));
  if(ht->buckets == NULL) {
    printf("Memory allocation no gree work.\n");
    return;
  }

  ht->ts = (TombStone *) malloc(capacity * sizeof(TombStone));
  if(ht->ts == NULL) {
    printf("Memory allocation no gree work.\n");
    free(ht->buckets);

    return;
  }

  for(int i = 0; i < capacity; i ++) {
    ht->buckets[i] = NULL;
    ht->ts[i] = EMPTY;
  }

  ht->size = 0;
  ht->capacity = capacity;
}


/**
  * This function na to compute for the index of a particular bucket from a key.
  *
  * @param *key Pointer to the key to compute.
  * @param int capacity The total capacity of buckets the hash table dey carry.
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
  * This function na to create new bucket, then return that bucket.
  *
  * @param char *word Pointer to the word we wan put inside the bucket.
  *
  * @return Bucket* Pointer to the newly created bucket.
  */
Bucket *createBucket(char *word) {
  Bucket *bkt = (Bucket *) malloc(sizeof(Bucket));
  if(bkt == NULL) {
    printf("Memory allocation no gree work.\n");
    return NULL;
  }

  bkt->word = (char *) malloc((strlen(word) + 1) * sizeof(char));

  if(bkt->word == NULL) {
    printf("Memory allocation no gree work.\n");

    free(bkt);
    
    return NULL;
  }

  strcpy(bkt->word, word);
  bkt->occurance = 1;

  return bkt;
}


/**
  * This function na to search for a particular bucket by word wey dey contained inside am.
  *
  * @param Ht *ht Pointer to the hash table.
  * @param char *word Pointer to the word we go use carry out our search.
  *
  * @return Bucket* Pointer to the bucket wey dey hold same word as word wey dey our func arg 2.
  * @return NULL If no bucket contain same word as our search word.
  */
Bucket *searchBucket(Ht *ht, char *word) {
  int originalIdx = hash(word, ht->capacity);
  int idx = originalIdx;

  do {
    if (ht->ts[idx] == EMPTY) {
      break;
    } else if (ht->ts[idx] == OCCUPIED && strcmp(ht->buckets[idx]->word, word) == 0) {
      return ht->buckets[idx];
    }
    idx = (idx + 1) % ht->capacity;
  } while (idx != originalIdx);

  return NULL;
}


/**
  * This function na to increase the capacity of our hash table.
  * ie: we go increase the number of buckets the hash table fit carry.
  *
  * @param Ht *ht Pointer to the hash table we wan resize.
  */
void resizeHt(Ht *ht) {
  Ht newHt;
  int newCapacity = ht->capacity * 2;

  createHt(&newHt, newCapacity);

  for(int i = 0; i < ht->capacity; i ++) {
    if(ht->ts[i] == OCCUPIED) {
      addWord(&newHt, ht->buckets[i]->word);
      free(ht->buckets[i]->word);
      free(ht->buckets[i]);
    }
  }

  free(ht->ts);
  free(ht->buckets);
  
  ht->buckets = newHt.buckets;
  ht->ts = newHt.ts;
  ht->size = newHt.size;
  ht->capacity = newHt.capacity;
}


/**
  * This function na to add new word inside hash table.
  *
  * @param Ht *ht Pointer to the hash table we wan add the word to.
  * @param char *word Pointer to the word we wan add.
  */
void addWord(Ht *ht, char *word) {
  if((float)ht->size / ht->capacity >= LOAD_FACTOR_TRESHOLD) {
    resizeHt(ht);
  }

  Bucket *duplicateBucket = searchBucket(ht, word);
  if(duplicateBucket != NULL) {
    duplicateBucket->occurance ++;
    
    return;
  }
  
  Bucket *newBkt = createBucket(word);

  int idx = hash(word, ht->capacity);
  while(ht->ts[idx] == OCCUPIED) {
    idx = (idx + 1) % ht->capacity;
  }

  ht->buckets[idx] = newBkt;
  ht->ts[idx] = OCCUPIED;
  ht->size ++;
}


/**
  * This function na to print all words and occurances wey dey inside the hash table.
  *
  * @param Ht *ht The pointer to the hash table we wan print out all the stuffs from.
  */
void printWordsAndOccurances(Ht *ht) {
  for (int i = 0; i < ht->capacity; i++) {
    if (ht->ts[i] == OCCUPIED) {
      Bucket *bkt = ht->buckets[i];
      printf("Word: %s --- No. Of Occurance: %d\n", bkt->word, bkt->occurance);
    }
  }
}


/**
  * This function na to free all memory we don allocate to this hash table.
  *
  * @param Ht *ht Pointer to the hash table we wan free.
  */
void freeHt(Ht *ht) {
    for(int i = 0; i < ht->capacity; i ++) {
    if(ht->ts[i] != EMPTY) {
      if(ht->ts[i] == OCCUPIED) free(ht->buckets[i]->word);

      free(ht->buckets[i]);
    }
  }

  free(ht->buckets);
  free(ht->ts);
}


/**
  * This function na to convert any word to lowercase.
  * wey need this function because the function wey we dey use compare words dey case sensitive.
  *
  * @param char *str Pointer to the string or word we wan convert to lower case.
  */
void toLowerCase(char *str) {
  while (*str) {
    *str = tolower((unsigned char)*str);
    str++;
  }
}


int main() {
  Ht ht;
  createHt(&ht, 4);

  printf("\n");
  printf("*************************************************************************************\n");
  printf("* Tuale Boss!! Enter sentence or paragraph make i count occurances of words inside. *\n");
  printf("*************************************************************************************\n");

  // get sentence or paragraph
  printf("\nEnter sentence/paragraph(<500): ");
  char p[500]; 
  fgets(p, sizeof(p), stdin);
  p[strcspn(p, "\n")] = '\0';

  char *pTok = strtok(p, " ");

  while(pTok != NULL) {
    toLowerCase(pTok);

    addWord(&ht, pTok);

    pTok = strtok(NULL, " ");
  }

  printWordsAndOccurances(&ht);

  freeHt(&ht);

  return 0;
}
