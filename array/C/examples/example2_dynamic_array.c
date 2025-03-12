/**
* example2_dynamic_array.c 
*
* Example use case for managing a To-Do list in C.
*
* WTD: we go build To-Do list.
*
* Author: NULL
* Date: 12/02/2025
**/

#include <stdio.h>
#include <stdlib.h>     // for memory allocation & reallocation
#include <string.h>     // for some kind string manipulation eg strcpy, etc.

// Task
typedef struct {
  char description[100];
  int isComplete;
} Task;

// Todo
typedef struct {
  Task *task;
  int capacity;
  int size;
} Todo;


/**
 * This function na to initialize the array(dynamic array) wey we wan store our Todo list tasks.
 *
 * @param Todo todo Pointer to the Todo structure
 * @param int capacity The capacity of the dynamic array
 */
void initArray(Todo *todo, int capacity) {
  if(capacity < 1) {
    printf("Array capacity wey you set no dey make sense.\n");
    return;
  }

  // we dey allocate memory for our tasks(dynamic array)
  todo->task = (Task*) malloc(capacity * sizeof(int));

  if(todo->task == NULL) {
    printf("Memory allocation for the array no gree work\n");
    exit(0);
  }

  todo->capacity = capacity;
  todo->size = 0;
}


/**
 * This function na to add task inside our Todo list.
 *
 * @param Todo todo Pointer to the Todo structure
 */
void addTask(Todo *todo) {
  if(todo->size == todo->capacity) {
    int capacity = todo->capacity + 1;
    todo->task = (Task*) realloc(todo->task, capacity * sizeof(int));

    if(todo->task == NULL) {
      printf("Memory reallocation for the array no gree work\n");
      exit(0);
    }

    todo->capacity = capacity;
  }

  printf("Abeg enter task here:");
  fgets(todo->task[todo->size].description, sizeof(todo->task[todo->size].description), stdin);
  todo->task[todo->size].description[strcspn(todo->task[todo->size].description, "\n")] = '\0';

  todo->task[todo->size].isComplete = 0;

  todo->size ++;
}


/**
 * This function na to delete task wey dey inside our Todo list.
 *
 * @param Todo todo Pointer to the Todo structure
 * @param int idx Index of the task we wan delete 
 */
void deleteTask(Todo *todo, int idx) {
  if(idx < 0 && idx >= todo->capacity) {
    printf("This index: %d no dey make sense\n", idx);
    exit(0);
  }

  for(int i = idx; i < (todo->size - 1); i ++) {
    strcpy(todo->task[i + 1].description, todo->task[i].description);
    todo->task[i].isComplete = todo->task[i + 1].isComplete;
  }

  todo->size --;
}


/**
 * This function na to complete task wey dey inside our Todo list.
 *
 * @param Todo todo Pointer to the Todo structure
 * @param int idx Index of the task we wan complete 
 */
void completeTask(Todo *todo, int idx) {
  if(idx < 0 && idx >= todo->capacity) {
    printf("This index: %d no dey make sense\n", idx);
    exit(0);
  }

  todo->task[idx].isComplete = 1;
}


/**
 * This function na to edit task inside our Todo list.
 * Here we dey replace the old description with a new static description
 *
 * @param Todo todo Pointer to the Todo structure
 * @param int idx Index where we wan make this edit
 */
void editTask(Todo *todo, int idx) {
  if(idx < 0 && idx >= todo->capacity) {
    printf("This index: %d no dey make sense\n", idx);
    exit(0);
  }

  strcpy(todo->task[idx].description, "This is now a new description");
}


/**
 * This function na to print the all the task wey dey inside our To-Do list.
 *
 * @param Todo todo Pointer to the Todo structure 
 */
void printTodo(Todo *todo) {
  printf("ALL TASKS\n");
  for(int i = 0; i < todo->size; i ++) {
    printf("Task %d: %s <%s>\n", i, todo->task[i].description, todo->task[i].isComplete == 1 ? "Completed" : "Uncompleted");
  }
  printf("\n");
}


int main() {
  Todo todo;
  
  initArray(&todo, 2);

  addTask(&todo);
  addTask(&todo);
  addTask(&todo);
  addTask(&todo);

  printTodo(&todo);

  completeTask(&todo, 0);
  printf("*** completed a task **\n");
  printTodo(&todo);

  editTask(&todo, 1);
  printf("*** edited a task **\n");
  printTodo(&todo);

  deleteTask(&todo, 3);
  printf("*** deleted a task **\n");
  printTodo(&todo);

  free(todo.task);  // ALWAYS USE free(), C NO GO DO AM FOR YOU.
}

