#ifndef TREE_H
#define TREE_H

#include <stdbool.h>
#include "lists.h"

//The node of a tree which represents a user.
struct TNode {
    unsigned short userId;      //User Id.
    struct Node *preferences;   //Pointer on linked list of preferences.
    struct TNode *rightSib;     //If TNode is the rightmost child of its parent it points on its parent.
    struct TNode *leftSib;      //If TNode is the leftmost child of its parent it points on its parent.
    struct TNode *leftChild;    //If TNode has no children it's NULL.
    struct TNode *rightChild;   //If TNode has no children it's NULL.
};

struct TNode *newTNode(unsigned short newId);

#endif