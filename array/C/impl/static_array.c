/**
 * static_array.c 
 *
 * Implementation of static arrays in C.
 *
 * Wetin be static array?
 * Static arrays na array wey dey get fixed size and memory for the array dey allocated at compile time.
 * one thing you suppose know na say; once you set size for static array, you no go ever fit change am again inside that program.
 *
 * Operations:
 * - Insertion: O(1)
 * - Deletion: O(n) -> because we gats shift other elements after we delete one.
 * - Access: O(1)
 * - Search: O(n)
 *
 * Author: NULL
 * Date: 12/02/2025
 **/

#include <stdio.h>

// make we define fixed size of our array as constant
#define MAX_SIZE 4

// now we go define our array strcture
typedef struct {
  int data[MAX_SIZE];  // we declare the array here with that fixed sized constant
  int size;  // we go use this struct member to manually keep track of size of this array
} StaticArray;


/**
* This function na to initialize the array.
*
* @param StaticArray arr Pointer to the StaticArray structure
**/
void initArray(StaticArray* arr) {
  // we need initialize the size to 0 (asin empty array)
  // with this, we fit know say any element we put inside the array go dey the begining(index = 0). 
  arr->size = 0;
}


/**
* This function na to add element inside our array
* Just like i don write for up, this operation na one of the operations you fit do with array.
* This operation get constant time complexity O(1)
*
* @param StaticArray arr Pointer to the StaticArray structure
* @param int idx The index where we wan do our Insertion
* @param int element The element we wan add to the array
*
**/
void insert(StaticArray *arr, int idx, int element) {
  if(arr->size == MAX_SIZE && idx >= arr->size) {
    printf("Array don full with %d elements", arr->size);
    return;
  }

  if(idx < 0 || idx >= MAX_SIZE) {
    printf("This index: %d no dey make any sense\n", idx);
    return;
  }

  // if supplied index dey less than array size, meaning we don already set element for that index before,
  // we go need overwrite.
  if(idx < arr->size) {
    arr->data[idx] = element;
    return;
  }

  // if all the conditions wey dey for up no dey true, we fit add that element to the array,
  // then increase the size of the array.
  arr->data[idx] = element;
  arr->size ++;
}


/**
* This function na to delete element komot from the array.
* After we delete, and no be the last element we delete, we go need shift other elements inside the array,
* doing that go make us dey able to add new array element after the index of the last entered element.
* This operation get linear time complexity O(n).
*
* @param StaticArray arr Pointer to the StaticArray structure
* @param int idx The index where we wan komot element from.
*/
void delete(StaticArray *arr, int idx) {
  if(idx < 0 || idx >= MAX_SIZE) {
    printf("This index: %d no dey make any sense", idx);
  }
  
  // wetin we wan do here na to shift every element wey dey after the index element, one step back.
  for(int i = idx; i < arr->size - 1; i ++) {
    arr->data[i] = arr->data[i + 1];
  }
  arr->size --;
}


/**
* This function na to get/access element we dey at a particular index.
* This operation get constant time complexity O(1).
*
* @param StaticArray arr Pointer to the StaticArray structure
* @param int idx The index where we wan access element from.
*
* @return int The element wey we access.
*/
int access(StaticArray *arr, int idx) {
  if(idx < 0 || idx >= MAX_SIZE) {
    printf("This index: %d no dey make any sense", idx);
  }

  return arr->data[idx];
}


/**
* This function na to search for element inside array.
* This operation get linear time complexity O(n).
*
* @param StaticArray arr Pointer to the StaticArray structure
* @param int element The element wey we dey search for.
*
* @return int The index where see the search element or -1 if we no see wetin we search for.
*/
int search(StaticArray *arr, int element) {
  for(int i = 0; i < arr->size; i ++) {
    if(arr->data[i] == element) {
      printf("The element dey, we see am for this index: %d", element);
      return i;
    }
  }

  printf("The element you dey find no dey inside this array");
  return -1;
}

/**
 * ******************************************************************************************************
 * MAKE WE PLAY WITH OUR DATA STRUCTURE.
 **/

/**
* Print out elements wey dey inside array.
* 
* @param StaticArray arr Pointer to the StaticArray structure.
*/
void printArray(StaticArray *arr) {
  printf("Array elements: ");
  for (int i = 0; i < arr->size; i++) {
    printf("%d ", arr->data[i]);
  }
  printf("\n");
}


int main() {
  // Create the array
  StaticArray arr;
  initArray(&arr);

  // put elements inside the array
  insert(&arr, 0, 10); // Insert 10 for index 0
  insert(&arr, 1, 20); // Insert 20 for index 1
  insert(&arr, 2, 30); // Insert 30 for index 2

  // Print the array
  printArray(&arr);

  // Delete element wey dey index 1
  delete(&arr, 1);
  // Print the array after we don carry out deletion operation
  printArray(&arr);

  return 0;
}
