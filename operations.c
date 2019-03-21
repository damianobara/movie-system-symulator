#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "operations.h"
#include "tree.h"
#include "lists.h"

//Every function ending with Op is making one operation on tree.

//Writes Error on stderr.
void myError(void) {
    fprintf(stderr, "ERROR\n");
}

//Carries addUser operation. Memorise the pointer for new user if operation was succesful.
void addUserOp(unsigned short parentUserId, unsigned short userId, struct TNode *Pointers[]) {
    struct TNode *parent = Pointers[parentUserId];
    struct TNode *child = Pointers[userId];

    //Checks if the userId and parentId are correct
    if (parent == NULL || child != NULL) {
        myError();
    } else {
        //Mallocs the memory for new user.
        child = newTNode(userId);
        if (child) {
            //Adds new user to the tree of users.
            if (parent->leftChild == NULL) {
                parent->leftChild = child;
                parent->rightChild = child;
                child->leftSib = parent;
                child->rightSib = parent;
            } else {
                child->rightSib = parent->leftChild;
                (parent->leftChild)->leftSib = child;
                parent->leftChild = child;
                child->leftSib = parent;
            }
            Pointers[userId] = child;
            printf("OK\n");
        }
    }
}

//Carries addMovie operation.
void addMovieOp(unsigned short userId, long movieRating, struct TNode *Pointers[]) {
    struct TNode *user = Pointers[userId];
    //If there is no user with userId it writes Error into stderr.
    if (user == NULL) {
        myError();
    }
    //If the user has already movieRating in its preferences it writes Error into stderr.
    else if (isNode(user->preferences, movieRating)) {
        myError();
    }
    else {
        sortedInsert(&(user->preferences), movieRating);
        printf("OK\n");
    }
}

//Carries delMovie operation.
void delMovieOp(unsigned short userId, long movieRating, struct TNode *Pointers[]) {
    struct TNode *del = Pointers[userId];
    //If there is no user with userId it writes Error into stderr.
    if (del == NULL) {
        myError();
    }
    //If the user hasn't movieRating in its preferences it writes Error into stderr.
    else if (!isNode(del->preferences, movieRating)) {
        myError();
    }
    else {
        deleteNode(&(del->preferences), movieRating);
        printf("OK\n");
    }
}

//Check if the node in the tree is the rightmost child of its parent.
bool isRightMost(struct TNode *x, unsigned short userId) {
    if ((x->rightSib)->rightChild == NULL) return false;
    else return (((x->rightSib)->rightChild)->userId == userId);
}

//Checks if the Node in the tree is the leftmost child of its parent.
bool isLeftMost(struct TNode *x, unsigned short userId) {
    if ((x->leftSib)->leftChild == NULL) return false;
    else return (((x->leftSib)->leftChild)->userId == userId);
}

//Carries delUser operation.
void delUserOp(unsigned short userId, struct TNode *Pointers[]) {
    if (userId == 0) {
        myError();
    }
    //If there is no user with userId it writes Error into stderr.
    else if (Pointers[userId] == NULL) {
        myError();
    }
    else {
        struct TNode *x = Pointers[userId];
        deleteList(&(x->preferences));

        bool haveChildren = (x->leftChild != NULL);
        bool rightMost = isRightMost(x, userId);
        bool leftMost = isLeftMost(x, userId);

        assert (x->leftSib != NULL);
        assert (x->rightSib != NULL);

        //Deleting user from the tree and ensuring the structure will remain cohorent and correct.
        if (rightMost && leftMost) {

            (x->leftSib)->leftChild = x->leftChild;
            (x->rightSib)->rightChild = x->rightChild;

            if (haveChildren) {
                (x->leftChild)->leftSib = x->leftSib;
                (x->rightChild)->rightSib = x->rightSib;
            }
        } else if (rightMost) {
            if (haveChildren) {
                (x->leftSib)->rightSib = x->leftChild;
                (x->leftChild)->leftSib = x->leftSib;
                (x->rightSib)->rightChild = x->rightChild;
                (x->rightChild)->rightSib = x->rightSib;
            } else {
                (x->rightSib)->rightChild = x->leftSib;
                (x->leftSib)->rightSib = x->rightSib;
            }
        } else if (leftMost) {
            if (haveChildren) {
                (x->leftSib)->leftChild = x->leftChild;
                (x->leftChild)->leftSib = x->leftSib;
                (x->rightSib)->leftSib = x->rightChild;
                (x->rightChild)->rightSib = x->rightSib;
            } else {
                (x->leftSib)->leftChild = x->rightSib;
                (x->rightSib)->leftSib = x->leftSib;
            }
        } else {
            if (haveChildren) {
                (x->leftSib)->rightSib = x->leftChild;
                (x->leftChild)->leftSib = x->leftSib;
                (x->rightSib)->leftSib = x->rightChild;
                (x->rightChild)->rightSib = x->rightSib;
            } else {
                (x->leftSib)->rightSib = x->rightSib;
                (x->rightSib)->leftSib = x->leftSib;
            }
        }
        //Forgeting the pointer for deleted user.
        free(x);
        Pointers[userId] = NULL;
        printf("OK\n");
    }
}

/*Recursive helper function for marathon operation which returns marathon result list
* if the argument was parent.*/
struct Node *mara(struct TNode *parent, long k) {
    if (parent != NULL) {
        //Coping first k preferences of the user.
        struct Node *kaParent = kaCopy(parent->preferences, k);
        struct TNode *child = parent->leftChild;
        if (child != NULL) {
            //Carring mara() on all the children of the user.
            struct Node *kaOld = mara(child, k);
            struct Node *kaNew;
            child = child->rightSib;
            while (child != parent) {
                kaNew = mara(child, k);
                kaNew = mergeSorted(kaNew, kaOld);
                removeDuplicates(kaNew);
                kaFirst(kaNew, k);
                kaOld = kaNew;
                child = child->rightSib;
            }
            //Returning the result of maraton for actual user.
            kaNew = marathonMerge(kaParent, kaOld);
            removeDuplicates(kaNew);
            kaFirst(kaNew, k);
            return kaNew;
        } else {
            return kaParent;
        }
    } else return NULL;
}

//Carries marathon operation.
void marathonOp(unsigned short userId, long k, struct TNode *Pointers[]) {
    struct TNode *parent = Pointers[userId];
    //If there is no user with userId it writes Error into stderr.
    if (parent == NULL) {
        myError();
    }
    else if (k == 0) {
        printf("NONE\n");
    }
    else {
        struct Node *result = mara(parent, k);
        writeMarathon(result);
        deleteList(&result);
    }
}