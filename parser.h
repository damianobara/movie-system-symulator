#ifndef PARSER_H
#define PARSER_H

#define ENTER '\n'
#define HASH '#'
#define SPACE ' '

//Type to handle all possible input.
typedef enum {
    empty, hash, error, addUser, delUser, addMovie, delMovie, marathon
} operation;

//Struct to remember information about new operation.
typedef struct {
    operation myOperation;
    short unsigned int parentId;
    short unsigned int userId;
    long movieRating;
    long k;
} operationParametres;

void read(struct TNode *Pointers[]);

#endif