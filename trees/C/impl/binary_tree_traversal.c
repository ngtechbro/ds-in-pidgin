/**
* binary_tree_traversal.c
*
* Implementation of binary tree data structure traversal.
*
* Author: NULL
* Date: 08/04/2025
**/

#include <stdio.h>
#include <stdlib.h>
#include "binary_tree_traversal.h"

typedef struct Queue {
  TreeNode **data;
  int size;
  int capacity;
} Queue;

typedef struct TreeNode {
  int id;
  struct TreeNode *left;
  struct TreeNode *right;
} TreeNode;



void freeQueue(Queue *queue) {
  if(queue == NULL || queue->capacity == 0)
    return;

  free(queue->data);
  free(queue);
}


int enQueue(Queue *queue, TreeNode *node) {
  if(queue == NULL) {
    queue = (Queue *) malloc(sizeof(Queue));
    if(queue == NULL) {
      printf("Memory alloc no gree work.\n");
      return 0;
    }

    queue->data = (TreeNode **) malloc(5 * sizeof(TreeNode *));
    if(queue->data == NULL) {
      free(queue);
      printf("Memory alloc for tree node no gree work.\n");
      return 0;
    }

    queue->size = 0;
    queue->capacity = 5;
  }

  if(queue->size >= queue->capacity) {
    int newCapacity = queue->capacity * 2;
    queue->data = (TreeNode **) realloc(queue->data, newCapacity * sizeof(TreeNode *));
    if (queue->data == NULL) {
      freeQueue(queue);
      printf("Memory realloc no gree work.\n");
      return 0;
    }

    queue->capacity = newCapacity;
  }

  queue->data[queue->size] = node;
  queue->size ++;

  return 1;
}

TreeNode *deQueue(Queue *queue) {
  TreeNode *tmpNode = queue->data[0];

  for(int i = 1; i < queue->size; i ++) {
    queue->data[i - 1] = queue->data[i];
  }

  queue->size --;
  
  return tmpNode;
}

// level order traversal
void levelOrderTraversal(TreeNode *root) {
  if(root == NULL)
      return;

  Queue queue;
  int status = enQueue(&queue, root);
  if(status != 1) {
    printf("Traversal queue don fail.\n");
    return;
  }

  while(queue.size > 0) {
    TreeNode *currNode = deQueue(&queue);

    printf("Node value: %d\n", currNode->id);

    if(currNode->left != NULL) {
      enQueue(&queue, currNode->left);
    }

    if(currNode->right != NULL) {
      enQueue(&queue, currNode->right);
    }
  }

  freeQueue(&queue);
}

// in order traversal
void inOrderTraversal(TreeNode *root) {
  if(root == NULL)
      return;
  
  if(root->left != NULL)
    inOrderTraversal(root->left);
  
  printf("Node value: %d\n", root->id);

  if(root->right != NULL)
    inOrderTraversal(root->right);
}


// pre order traversal
void preOrderTraversal(TreeNode *root) {
  if (root == NULL)
    return;

  printf("Node value: %d\n", root->id);

  if(root->left != NULL)
    preOrderTraversal(root->left);

  if(root->right != NULL)
    preOrderTraversal(root->right);
}

// post order traversal
void postOrderTraversal(TreeNode *root) {
  if(root == NULL)
    return;

  if(root->left != NULL)
    postOrderTraversal(root->left);

  if(root->right != NULL)
    postOrderTraversal(root->right);

  printf("Node value: %d\n", root->id);
}



