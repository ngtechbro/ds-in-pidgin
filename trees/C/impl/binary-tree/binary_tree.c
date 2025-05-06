/**
 * binary_tree.c 
 *
 * Implementation of binary tree in C.
 *
 * I don talk about binary tree for the header file(see: binary_tree.h).
 * COMMON TYPES OF BINARY TREE: i go try list some common types(structural xtics) of binary trees. Other types dey, but you fit follow up read on them yourself.
 * - Perfect Binary Tree: This type of binary tree na the one wey all nodes on all levels dey completly filled except all the leaf nodes(all leaf node must dey same level).
 *                      This mean say all nodes wey no be leaf node get degree of 2, and all leaf nodes get degree of 0.
 * - Complete Binary Tree: This na type of binary tree wey dey try become perfect binary tree, but leaf nodes dey filled from left to right.
 *                       This mean say any level wey leaf nodes dey, them dey fill them up from left to right, wether all leaf nodes dey filled or not, we fit call am a complete binary tree.
 * - Full Binary Tree: This na type of binary tree where all the nodes either get degree of zero(leaf node) or they get degree of two.
 * - Balanced Binary Tree: This na type of tree where the absolute difference between the left and right subtree of any containing node no dey greater than 1.
 *                         This type of binary tree na to ensure balance so nodes no go dey more on one side and less on the other side.
 *                         Some special types of balanced trees dey wey carry this balance matter for head, so them dey self balance themselves(during insertion/deletion). I go do implementations for them as well, but e no go be for here.
 * - Binary Search Tree: Remember say each node of a binary tree dey hold value, and pointer(s) to child node if any. Binary search tree dey work with those value wey each node dey hold. The logic behind am na say;
 *                       Value wey dey the left child node of any node must dey less than the value of the parent node, and the value wey dey the parent node must in turn dey less than the value wey dey the right child node.
 *
 * The Implementation wey i go do inside this file go be for Binary Search Tree(BST).
 *
 * Operations:
 * - Insertion: If e dey balanced: O(log n), else: O(n)
 * - Deletion: If e dey balanced: O(log n), else: O(n)
 * - Search: O(log n)
 *
 * Author: NULL
 * Date: 08/04/2025
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_tree.h"


/**
  * This function na to create unit node of a tree.
  *
  * @param char *name The name value wey the node go hold.
  * @return TreeNode* Pointer to the new node wey we just create.
  */
TreeNode *createTNode(char *name) {
  TreeNode *node = (TreeNode *) malloc(sizeof(TreeNode));
  if(node == NULL) {
    printf("Memory alloc no gree work\n");
    return NULL;
  }

  node->name = (char *) malloc(strlen(name) + 1);
  node->email = (char *) malloc(sizeof(char));
  node->number = (char *) malloc(sizeof(char));

  if(node->name == NULL || node->email == NULL || node->number == NULL) {
    if(node->name) free(node->name);
    if(node->email) free(node->email);
    if(node->number)  free(node->number);
    free(node);

    printf("Memory alloc for node members no gree work\n");

    return NULL;
  }

  snprintf(node->name, strlen(name) + 1, "%s", name);
  node->left = NULL;
  node->right = NULL;

  return node;
}


/**
  * This function na to insert node inside the tree.
  *
  * @param TreeNode *root Pointer to the root node of the tree we wan add to.
  * @param TreeNode *node Pointer to the node we wan add.
  *
  * @return TreeNode* Pointer to the tree root node.
  */
TreeNode *insertNode(TreeNode *root, TreeNode *node) {
  if(root == NULL) {
    TreeNode *newNode = createTNode(node->name);
    snprintf(newNode->email, strlen(node->email) + 1, "%s", node->email);
    snprintf(newNode->number, strlen(node->number) + 1, "%s", node->number);

    return newNode;
  }

  if (strcmp(root->name, node->name) > 0) // if true, follow the left child node
    root->left = insertNode(root->left, node);
  else if(strcmp(root->name, node->name) < 0) // follow the right child node.
    root->right = insertNode(root->right, node);
  else 
    printf("duplicate node id.\n");

  return root;
}


/**
  * This function na to get the child node with the lowest value from a root node.
  *
  * @param TreeNode *root Pointer to the root node of the tree we wan add to.
  *
  * @return *TreeNode Pointer to the node with the least value.
  */
TreeNode *minValNode(TreeNode *root) {
  while (root && root->left != NULL)
    root = root->left;

  return root;
}


/**
  * This function na to delete node komot from a tree.
  *
  * @param TreeNode *root Pointer to the root node of a tree.
  * @param char *name the name wey the node we wan delete dey hold.
  *
  * return *TreeNode Pointer to the root node
  */
TreeNode *deleteNode(TreeNode *root, char *name) {
  if(root == NULL)
    return root;

  if(strcmp(root->name, name) > 0)  // left child node
    root->left = deleteNode(root->left, name);
  else if(strcmp(root->name, name) < 0)   // right child node
    root->right = deleteNode(root->right, name);
  else {  // the node we wan delete from
    // if the node get one child
    if(root->left == NULL) {
      TreeNode *tmpNode = root->right;

      free(root->name);
      free(root->email);
      free(root->number);
      free(root);

      return tmpNode;
    }
    else if(root->right == NULL) {
      TreeNode *tmpNode = root->left;

      free(root->name);
      free(root->email);
      free(root->number);
      free(root);

      return tmpNode;
    }

    // if the node get two children
    TreeNode *tmpNode = minValNode(root->right);

    //pass data
    snprintf(root->name, strlen(tmpNode->name) + 1, "%s", tmpNode->name);
    snprintf(root->email, strlen(tmpNode->email) + 1, "%s", tmpNode->email);
    snprintf(root->number, strlen(tmpNode->number) + 1, "%s", tmpNode->number);

    root->right = deleteNode(root->right, tmpNode->name);
  }

  return root;
}


/**
  * This function na to search for a particular node from the tree.
  *
  * @param TreeNode *root Pointer to the root node of the tree.
  * @param char *name name member value of node we wan search for.
  */
TreeNode *search(TreeNode *root, char *name) {
  if (root == NULL || (strcmp(root->name, name) == 0))
    return root;

  if(strcmp(root->name, name) > 0)  // left child node
    return search(root->left, name);  // Go left
  else
    return search(root->right, name); // Go right
}
