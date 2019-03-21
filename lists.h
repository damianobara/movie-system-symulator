#ifndef LISTS_H
#define LISTS_H

#include <stdbool.h>

//Node of linked list representing preferences of user.
struct Node {
    long value;
    struct Node *next;
};

void sortedInsert(struct Node **head, long newValue);
void printList(struct Node *head);
void deleteNode(struct Node **head, long dValue);
void deleteList(struct Node **head);
struct Node *kaCopy(struct Node *original, long k);
struct Node *mergeSorted(struct Node *l1, struct Node *l2);
void kaFirst(struct Node *l, long k);
struct Node *marathonMerge(struct Node *parent, struct Node *children);
void writeMarathon(struct Node *x);
void removeDuplicates(struct Node *head);
bool isNode(struct Node* head, long x);

#endif 