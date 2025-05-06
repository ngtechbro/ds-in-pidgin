/**
* binary_tree.h 
*
* Header file for binary tree data structure.
*
* Wetin be tree?
* Tree na type of non linear data structure wey them dey use represent hierarchical relationship between elements. 
* Trees dey made up of nodes wey dey connected to each other by edges, and these nodes fit still individually become parent or child to another node.
* So just like the way normal tree dey take get branches, and those branches fit still individually get other branches and so on...,
* na exactly the same way tree data structure take dey with nodes.
* To sabi fully wetin trees be, their attribute and how to use them, you must sabi these concepts:
* - Node: This na the single unit of the tree data structure and the basic things e go hold na the data wey that node go hold, and reference(s) or pointer(s) to child(ren) node(s).
* - Root node: This na the first node to enter the tree, and the overall parent to all other nodes wey dey the tree(ie: if the tree get other nodes). Root node no dey get any parent node.
* - Leaf node: This na the last decendant node, that means; na node wey no dey point to any other node or you fit see am as any node wey no get child.
* - Edge: This na the line wey connect one node to another. you fit still see am as the reference or pointer between two nodes.
* - Degree: The degree of any node na the number of children that node get.
* - Height Of Tree: The height of any tree na the number of edges wey dey from the root node to any connected leaf node.
* - Height Of Node: The height of any node na the number of edges wey dey from that node to any connected leaf node.
* - Depth Of Node: The depth of any node na the number of edges wey dey from the root node of that tree to the node in question
* - Level Of Node: The level of any node na like the hierarchy of that node starting from root node wey dey at the top most level, level 1
*
* BINARY TREE:
* Binary tree na type of tree wey im nodes just like the name binary imply, no fit ever dey more than 2 degrees.
* Mean say binary tree na type of tree wey im containing nodes individually no fit get more than 2 children.
* One of the child of any node wey dey binary tree dey considered as the left node, while the other na the right node.
*
* Author: NULL
* Date: 08/04/2025
**/

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

typedef struct TreeNode {
  /*int id;*/
  /*Contact *contact;*/
  char *name;
  char *email;
  char *number;
  struct TreeNode *left;
  struct TreeNode *right;
} TreeNode;

// create a unit node
TreeNode *createTNode(char *name);

// insert node to tree
TreeNode *insertNode(TreeNode *root, TreeNode *node);

// delete node from a tree
TreeNode *deleteNode(TreeNode *root, char *name);

// search for node inside tree
TreeNode *search(TreeNode *root, char *name);

#endif

