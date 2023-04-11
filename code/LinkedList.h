#ifndef LINKED_LIST_H_INCLUDED
#define LINKED_LIST_H_INCLUDED

#include "Card.h"

typedef struct linkedList {
    int length;
    Card *head;
} LinkedList;

void insert_at_head(LinkedList *, Card *);

void debug_print_linked_list(LinkedList *);

Card *get(Card *, int);

#endif
