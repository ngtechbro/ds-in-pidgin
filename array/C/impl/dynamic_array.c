/**
 * dynamic_array.c 
 *
 * Implementation of dynamic arrays in C.
 *
 * Wetin be dynamic array?
 * dynamic arays na array wey no get fixed size and memory for the array dey allocated at runtime.
 * So, once you create this type of array, na you go use your hand dey manage the size and memory allocation.
 * And you go fit do the management if you use pointers.
 *
 * Operations:
 * - Insertion: O(1)
 * - Deletion: O(n) -> because we gats shift other elements after we delete one.
 * - Access: O(1)
 * - Search: O(n)
 *
 * Author: NULL
 * Date: 12/02/2024
 **/

#include <stdio.h>
#include <stdlib.h>   // we need this for memory allocation and reallocation

// now we go define our array strcture
typedef struct {
  int *data;    // pointer to the array data(na same thing as the dynamic memory)
  int size;     // the size of the array.
  int capacity; // the capacity of elements we want make this array carry.
} DynamicArray;


/**
* This function na to initialize the array.
*
* @param DynamicArray arr Pointer to the DynamicArray structure
* @param capacity The number of elements we want make our array fit carry
**/
void initArray(DynamicArray* arr, int capacity) {
  arr->data = (int *) malloc(capacity * sizeof(int)); // na here we do the memory allocation
  if(arr->data == NULL) {
    printf("memory allocation no gree work.\n");
    exit(0);
  }

  arr->capacity = capacity;

  // we need initialize the size to 0 (asin empty array)
  // with this, we fit know say any element we put inside the array go dey the begining(index = 0). 
  arr->size = 0;
}


/**
* This function na to add element inside our array
* This operation get constant time complexity O(1)
*
* @param DynamicArray arr Pointer to the DynamicArray structure
* @param int element The element we wan add to the array
*
**/
void insert(DynamicArray *arr, int element) {
  // if the array don dey filled up, we need increase the capacity(reallocate memory),
  // remember na we go manage the memory ourselves.
  if(arr->size == arr->capacity) {
    int capacity = arr->capacity + 1;

    arr->data = (int *) realloc(arr->data, capacity * sizeof(int));
    if(arr->data == NULL) {
      printf("memory reallocation no gree work.\n");
      exit(0);
    }

    arr->capacity = capacity;
  }
 
  // we put the new element for the end of the array then update size counter.
  arr->data[arr->size] = element;
  arr->size ++;
}


/**
* This function na to delete element komot from the array.
* After we delete, and no be the last element we delete, we go need shift other elements inside the array,
* doing that go make us dey able to add new array element after the index of the last element wey dey the array.
* This operation get linear time complexity O(n).
*
* @param DynamicArray arr Pointer to the DynamicArray structure
* @param int idx The index where we wan komot element from.
*/
void delete(DynamicArray *arr, int idx) {
  if(idx < 0 || idx >= arr->capacity) {
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
* @param DynamicArray arr Pointer to the DynamicArray structure
* @param int idx The index where we wan access element from.
*
* @return int The element wey we access.
*/
int access(DynamicArray *arr, int idx) {
  if(idx < 0 || idx >= arr->capacity) {
    printf("This index: %d no dey make any sense", idx);
  }

  return arr->data[idx];
}


/**
* This function na to search for element inside array.
* This operation get linear time complexity O(n).
*
* @param DynamicArray arr Pointer to the DynamicArray structure
* @param int element The element wey we dey search for.
*
* @return int The index where see the search element or -1 if we no see wetin we search for.
*/
int search(DynamicArray *arr, int element) {
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
* @param DynamicArray arr Pointer to the DynamicArray structure.
*/
void printArray(DynamicArray *arr) {
  printf("Array elements: ");
  for (int i = 0; i < arr->size; i++) {
    printf("%d ", arr->data[i]);
  }
  printf("\n");
}


int main() {
  // Create the array
  DynamicArray arr;
  initArray(&arr, 1);

  // put elements inside the array
  insert(&arr, 10); // Insert 10 at index 0
  insert(&arr, 20); // Insert 20 at index 1
  insert(&arr, 30); // Insert 30 at index 2

  // Print the array
  printArray(&arr);

  // Delete element wey dey index 1
  delete(&arr, 1);
  // Print the array after we don carry out deletion operation
  printArray(&arr);

  free(arr.data);

  return 0;
}
