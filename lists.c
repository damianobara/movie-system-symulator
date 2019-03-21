#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"
#include "lists.h"

// An utility function to create a new Node.
struct Node *newNode(long newValue) {
    struct Node *new = malloc(sizeof(struct Node));
    if (!new) return NULL;
    new->value = newValue;
    new->next = NULL;
    return new;
}

// A function to insert a node with the new value into sorted linked list.
void sortedInsert(struct Node **head, long newValue) {
    struct Node *current;
    struct Node *new = newNode(newValue);
    if (new) {
        //Case when we add the node at the beginning of the list.
        if (*head == NULL || (*head)->value <= newValue) {
            new->next = *head;
            *head = new;
        }
            //Case when we add the node in the further part of the list.
        else {
            current = *head;
            while (current->next != NULL && (current->next)->value > newValue) {
                current = current->next;
            }
            new->next = current->next;
            current->next = new;
        }
    }
}

// Writes values of linked list into stdin.
void printList(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        if (current->next != NULL) printf("%ld ", current->value);
        else printf("%ld", current->value);
        current = current->next;
    }
}

//Deletes the node after the current node.
void deleteBehind(struct Node *current) {
    struct Node *delete = current->next;
    current->next = delete->next;
    free(delete);
}

//Deletes the Node with value dValue from linked list.
void deleteNode(struct Node **head, long dValue) {
    struct Node *current = *head;
    if (current != NULL) {
        if (current->next == NULL) {
            free(current);
            *head = NULL;
        } else if (current->value == dValue) {
            *head = current->next;
            free(current);
        } else {
            while (current->next && (current->next)->value != dValue) {
                current = current->next;
            }
            deleteBehind(current);
        }
    }
}

// Deletes entire linked list.
void deleteList(struct Node **head) {
    struct Node *current = *head;
    struct Node *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

//Copy k first nodes from original list.
struct Node *kaCopy(struct Node *original, long k) {
    struct Node *mock = newNode(-1);
    if (!mock) return NULL;
    struct Node *copy = mock;
    long i = 1;
    while (i <= k && original != NULL) {
        copy->next = newNode(original->value);
        if (!(copy->next)){
            deleteList(&mock);
            return NULL;
        }
        copy = copy->next;
        original = original->next;
        i++;
    }
    copy = mock->next;
    free(mock);
    return copy;
}

//Merge 2 sorted lists into 1 sorted list.
struct Node *mergeSorted(struct Node *l1, struct Node *l2) {
    struct Node *mock = newNode(-1);
    if (!mock) return NULL;
    struct Node *act = mock;
    while (l1 != NULL && l2 != NULL) {
        if (l1->value > l2->value) {
            act->next = l1;
            act = act->next;
            l1 = l1->next;
        } else if (l1->value < l2->value) {
            act->next = l2;
            act = act->next;
            l2 = l2->next;
        } else {
            act->next = l1;
            act = act->next;
            l1 = l1->next;
            act->next = l2;
            act = act->next;
            l2 = l2->next;
        }
    }
    if (l1 == NULL) act->next = l2;
    else act->next = l1;

    struct Node *merge = mock->next;
    free(mock);
    return merge;
}

//Delete all nodes of linked lists apart from the first k ones.
void kaFirst(struct Node *head, long k) {
    long i = 1;
    struct Node *help = head;
    while (i < k && help != NULL) {
        help = help->next;
        i++;
    }
    if (i == k && help != NULL) deleteList(&(help->next));
}

/*Merge two sorted lists and returns sorted merged list with nodes from the second list,
 *which values are bigger than the value of the first node of first list.*/
struct Node *marathonMerge(struct Node *parent, struct Node *children) {
    if (parent == NULL) {
        return children;
    } else if (children == NULL) {
        return parent;
    } else {
        struct Node *tail = children;
        long x = parent->value;
        while (tail->next != NULL && (tail->next)->value > x) {
            tail = tail->next;
        }
        if (tail == children && tail->value < x) {
            deleteList(&children);
            return parent;
        } else {
            deleteList(&(tail->next));
            tail->next = parent;
            return children;
        }
    }
}

//Writes the solution of Marathon operation.
void writeMarathon(struct Node *head) {
    if (head == NULL) printf("NONE\n");
    else {
        printList(head);
        printf("\n");
    }
}

//Removes repetitions from linked list.
void removeDuplicates(struct Node *head) {
    struct Node *current = head;
    struct Node *after;

    if (current != NULL) {
        while (current->next != NULL) {
            if (current->value == (current->next)->value) {
                after = (current->next)->next;
                free(current->next);
                current->next = after;
            } else current = current->next;
        }
    }
}

//Checks if the value x is in list.
bool isNode(struct Node *head, long x) {
    struct Node *current = head;
    while (current != NULL) {
        if (current->value == x) return true;
        current = current->next;
    }
    return false;
}