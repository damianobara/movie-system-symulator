#ifndef OPERATIONS_H
#define OPERATIONS_H

#define USERS 65535

#include "tree.h"
#include "lists.h"

void myError(void);
void addUserOp(unsigned short parentUserId, unsigned short userId, struct TNode *Pointers[]);
void addMovieOp(unsigned short userId, long movieRating, struct TNode *Pointers[]);
void delMovieOp(unsigned short userId, long movieRating, struct TNode *Pointers[]);
void delUserOp(unsigned short userId, struct TNode *Pointers[]);
void marathonOp(unsigned short userId, long k, struct TNode *Pointers[]);


#endif 