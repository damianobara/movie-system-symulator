#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "tree.h"
#include "lists.h"
#include "parser.h"
#include "operations.h"

//Returns new operationParametres pointer.
operationParametres *newOp(operation x) {
    operationParametres *new = malloc(sizeof(operationParametres));
    new->myOperation = x;
    return new;
}

//Checks if the new operation is addUser or delUser.
void operation7(const char newOperation[], operationParametres *new) {
    char addUserArr[7] = {'a', 'd', 'd', 'U', 's', 'e', 'r'};
    char delUserArr[7] = {'d', 'e', 'l', 'U', 's', 'e', 'r'};
    int j, k;
    for (j = 0; j < 7 && newOperation[j] == addUserArr[j]; j++);
    for (k = 0; k < 7 && newOperation[k] == delUserArr[k]; k++);

    if (j == 7) new->myOperation = addUser;
    else if (k == 7) new->myOperation = delUser;
    else { new->myOperation = error; }
}

//Checks if the new operation is addMovie or delMovie or marathon.
void operation8(const char newOperation[], operationParametres *new) {
    char addMovieArr[8] = {'a', 'd', 'd', 'M', 'o', 'v', 'i', 'e'};
    char delMovieArr[8] = {'d', 'e', 'l', 'M', 'o', 'v', 'i', 'e'};
    char marathonArr[8] = {'m', 'a', 'r', 'a', 't', 'h', 'o', 'n'};

    int j, k, l;
    for (j = 0; j < 8 && newOperation[j] == addMovieArr[j]; j++);
    for (k = 0; k < 8 && newOperation[k] == delMovieArr[k]; k++);
    for (l = 0; l < 8 && newOperation[l] == marathonArr[l]; l++);

    if (j == 8) new->myOperation = addMovie;
    else if (k == 8) new->myOperation = delMovie;
    else if (l == 8) new->myOperation = marathon;
    else { new->myOperation = error; }
}

//Convert array into the unsigned short.
unsigned short toShort(const char *number) {
    int i, k = 0;
    unsigned short result;
    for (i = 0; i < 5 && ('0' <= number[i] && number[i] <= '9'); i++) k = 10 * k + (number[i] - '0');
    result = (unsigned short) k;
    return result;
}

//Convert array into the long.
long toLong(const char *number) {
    long i, k = 0;
    for (i = 0; i < 10 && ('0' <= number[i] && number[i] <= '9'); i++) k = 10 * k + number[i] - '0';
    return k;
}

//Check if the number from array can be stored in long size.
bool checkLong(char const number[]) {
    if ('2' < number[0]) return false;
    if ('2' > number[0]) return true;

    if ('1' < number[1]) return false;
    if ('1' > number[1]) return true;

    if ('4' < number[2]) return false;
    if ('4' > number[2]) return true;

    if ('7' < number[3]) return false;
    if ('7' > number[3]) return true;

    if ('4' < number[4]) return false;
    if ('4' > number[4]) return true;

    if ('8' < number[5]) return false;
    if ('8' > number[5]) return true;

    if ('3' < number[6]) return false;
    if ('3' > number[6]) return true;

    if ('6' < number[7]) return false;
    if ('6' > number[7]) return true;

    if ('4' < number[8]) return false;
    if ('4' > number[8]) return true;

    if ('7' < number[9]) return false;
    if ('7' > number[9]) return true;

    return true;
}

/*Reads data from stdin and converts it into long if it is possible.
 * If it is impossible sets new->myOperation on error.
 * If (wantSpace == true) we want space after this number, enter else. */
long readLongNumber(operationParametres *new, int *c, bool wantSpace) {
    int i;
    bool isLong;
    char number[10];
    for (i = 0; i < 10; i++) number[i] = '\0';

    long tem = 0;
    for (i = 0; i < 10 && (*c >= '0' && *c <= '9'); i++) {
        number[i] = (char) (*c);
        *c = getchar();
    }
    //Check if the number doesn't start with 0.
    if (i > 1 && number[0] == '0') {
        new->myOperation = error;
        return 0;
    }
    if (wantSpace && *c != SPACE) {
        new->myOperation = error;
    } else if (!wantSpace && *c != ENTER) {
        new->myOperation = error;
    } else if (i == 0) {
        new->myOperation = error;
    } else if (i == 10) {
        //Checks if the number fits into long size.
        isLong = checkLong(number);
        if (!isLong) new->myOperation = error;
    }
    //We do the conversion from array to long.
    tem = toLong(number);
    return tem;
}

//Check if the number from array can be stored in unsigned short size.
bool checkShort(char const number[]) {
    if ('6' < number[0]) return false;
    if ('6' > number[0]) return true;

    if ('5' < number[1]) return false;
    if ('5' > number[1]) return true;

    if ('5' < number[2]) return false;
    if ('5' > number[2]) return true;

    if ('3' < number[3]) return false;
    if ('3' > number[3]) return true;

    if ('5' < number[4]) return false;
    if ('5' > number[4]) return true;

    return true;
}

/*Reads data from stdin and converts it into unsigned short if it is possible.
 * If it is impossible sets new->myOperation on error.
 * If (wantSpace == true) we want space after this number, enter else. */
unsigned short readShortNumber(operationParametres *new, int *c, bool wantSpace) {
    int i = 0;
    bool isShort;
    char number[5];
    for (i = 0; i < 5; i++) number[i] = '\0';
    unsigned short tem = 0;

    for (i = 0; i < 5 && (*c >= '0' && *c <= '9'); i++) {
        number[i] = (char) (*c);
        *c = getchar();
    }
    //Check if the number doesn't start with 0.
    if (i > 1 && number[0] == '0') {
        new->myOperation = error;
        return 0;
    }
    if (wantSpace && *c != SPACE) {
        new->myOperation = error;
    } else if (!wantSpace && *c != ENTER) {
        new->myOperation = error;
    } else if (i == 0) {
        new->myOperation = error;
    } else if (i == 5) {
        //Checks if the number fits into short size.
        isShort = checkShort(number);
        if (!isShort) new->myOperation = error;
    }
    tem = toShort(number);
    return tem;
}

//Reads the arguments of program's operations.
void readNumbers(operationParametres *new, int *c) {
    switch (new->myOperation) {
        case addUser:
            if (*c != SPACE) break;
            *c = getchar();
            new->parentId = readShortNumber(new, c, true);
            if (*c != SPACE) break;
            *c = getchar();
            new->userId = readShortNumber(new, c, false);
            break;
        case delUser:
            if (*c != SPACE) break;
            *c = getchar();
            new->userId = readShortNumber(new, c, false);
            break;
        case addMovie:
            if (*c != SPACE) break;
            *c = getchar();
            new->userId = readShortNumber(new, c, true);
            if (*c != SPACE) break;
            *c = getchar();
            new->movieRating = readLongNumber(new, c, false);
            break;
        case delMovie:
            if (*c != SPACE) break;
            *c = getchar();
            new->userId = readShortNumber(new, c, true);
            if (*c != SPACE) break;
            *c = getchar();
            new->movieRating = readLongNumber(new, c, false);
            break;
        case marathon:
            if (*c != SPACE) break;
            *c = getchar();
            new->userId = readShortNumber(new, c, true);
            if (*c != SPACE) break;
            *c = getchar();
            new->k = readLongNumber(new, c, false);
            break;
        case error:
            break;
        case empty:
            break;
        case hash:
            break;
    }
}

//Reads instruction from stdin and checks if it is correct.
void loadInstruction(operationParametres *new, int *c) {
    char newOperation[8];
    int i;
    for (i = 0; i < 8; i++) newOperation[i] = '\0';
    for (i = 0; ((i < 8 && *c != ENTER) && *c != EOF) && *c != SPACE; i++) {
        newOperation[i] = (char) (*c);
        *c = getchar();
    }
    //Checking if the input is lexically correct.
    if (*c != SPACE) {
        new->myOperation = error;
    } else if (i == 7) {
        operation7(newOperation, new);
    } else if (i == 8) {
        operation8(newOperation, new);
    } else {
        new->myOperation = error;
    }

    //If input is lexically correct we read the arguments of the operation.
    readNumbers(new, c);
    if (*c != ENTER) new->myOperation = error;
}

/*Loads single row. Starts with first sign of new row.
 *EOF can be only at the begging of the empty line.
 *Ignores lines starting with #. */
void loadRow(operationParametres *new, int *c) {
    if (*c == HASH) {
        new->myOperation = hash;
    } else if (*c != EOF && *c != ENTER) {
        loadInstruction(new, c);
        if (*c != ENTER) new->myOperation = error;
    }
    while (*c != ENTER && *c != EOF) *c = getchar();
}

//Calls programms operations. Their arguments are lexically correct.
void startOperations(operationParametres *new, struct TNode *Pointers[]) {
    switch (new->myOperation) {
        case empty:
            break;
        case hash:
            break;
        case error:
            myError();
            break;
        case addUser:
            addUserOp(new->parentId, new->userId, Pointers);
            break;
        case delUser:
            delUserOp(new->userId, Pointers);
            break;
        case addMovie:
            addMovieOp(new->userId, new->movieRating, Pointers);
            break;
        case delMovie:
            delMovieOp(new->userId, new->movieRating, Pointers);
            break;
        case marathon:
            marathonOp(new->userId, new->k, Pointers);
            break;
    }
}

//Loads the input by rows until the EOF.
void read(struct TNode *Pointers[]) {
    operationParametres *new = newOp(empty);
    int c = getchar();
    while (c != EOF) {
        loadRow(new, &c);
        startOperations(new, Pointers);
        if (c == ENTER) c = getchar();
        new->myOperation = empty;
    }
    free(new);
}
