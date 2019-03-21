#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"
#include "lists.h"

//A utility function to create a new node.
struct TNode *newTNode(unsigned short newId) {
    struct TNode *new = malloc(sizeof(struct TNode));
    if (!new) return NULL;
    new->userId = newId;
    new->preferences = NULL;
    new->rightSib = NULL;
    new->leftSib = NULL;
    new->leftChild = NULL;
    new->rightChild = NULL;
    return new;
}