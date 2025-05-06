/**
* binary_tree_traversal.h
*
* Header file for binary tree data structure traversal.
* Traversal na english word, and wetin e mean na to go through every node wey dey present inside tree.
* They get 4 most common methods of traversing tree wey i know about viz;
* - Level Order Traversal: For this type of traversal, you go go through the tree level by level, ie: from the root node(level 1) down to level n, provided say n na the number of levels wey dey the tree.
*                          For each level you enter, you go go through the nodes wey dey that level from left to right, provided say nodes wey dey that level dey more than 2.
*                          The pattern for this type of traversal na TOP level -> BOTTOM level -> LEFT child node -> RIGHT child node.
* - In Order Traversal: For this type of traversal, you go first go through the left subtree, the through the root node, and then the right subtree.
*                       In other words, e dey follow the pattern LEFT child node -> ROOT node -> RIGHT child node.
* - Pre Order Traversal: For this type of traversal, you go first start from the root node, then to the left node, and then to the right node.
*                        The pattern for this type of traversal na ROOT node -> LEFT child node -> RIGHT child node.
* - Post Order Traversal: For this type of traversal, you go first go through the children of the node(left to right), before going through the node itself.
*                         The pattern for this type of traversal na LEFT child node -> RIGHT child node -> ROOT node.
*
* Author: NULL
* Date: 08/04/2025
**/

#ifndef TREE_TRAVERSAL_H
#define TREE_TRAVERSAL_H

// tree node struct
typedef struct TreeNode TreeNode;

// level order traversal
void levelOrderTraversal(TreeNode *root);

// in order traversal
void inOrderTraversal(TreeNode *root);

// pre order traversal
void preOrderTraversal(TreeNode *root);

// post order traversal
void postOrderTraversal(TreeNode *root);

#endif


