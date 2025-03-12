/**
* example1_static_array.c 
*
* Example use case for using static arrays in C.
*
* WTD: we go collect the grades of 5 students,
* we go calculate the sum and average, then we go print them out alongside the grades.
*
* Author: NULL
* Date: 12/02/2025
**/

#include <stdio.h>

// make we define fixed size of our array as constant
#define MAX_SIZE 5

int main() {
  int grades[MAX_SIZE];
  int total = 0;
  int average = 0;

  printf("Boss abeg, enter grade for 5 students\n");
  for(int i = 0; i < MAX_SIZE; i ++) {
    printf("Student %d: ", i + 1);
    scanf("%d", &grades[i]);   // we go collect grade as input on each loop
  }

  printf("\n");

  // make we determine the total.
  for(int i = 0; i < MAX_SIZE; i ++) {
    total += grades[i];
  }

  // determine average
  average = total / MAX_SIZE;

  // make we print out the grades
  printf("All students grade:\n");
  for(int i = 0; i < MAX_SIZE; i ++) {
    printf("Student %d: %d\n", i + 1, grades[i]);
  }

  printf("\n");

  // output total & average
  printf("TOTAL: %d\n", total);
  printf("AVERAGE: %d\n", average);

  return 0;
}

