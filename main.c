#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "parser.h"
#include "operations.h"

#define USERS 65535

//Main function of program.
int main(void) {
    int i;
    struct TNode *Pointers[USERS + 1]; //The array of pointers for all users.

    for (i = 0; i < USERS + 1; i++) {
        Pointers[i] = NULL;
    }

    Pointers[0] = newTNode(0);
    if (!Pointers[0]) exit(1);
    //Reading input and carring operations.
    read(Pointers);

    //Freeing the memory.
    for (i = 0; i < USERS + 1; i++) {
        if (Pointers[i] != NULL) {
            deleteList(&((Pointers[i])->preferences));
            free(Pointers[i]);
        }
    }
    return 0;
}