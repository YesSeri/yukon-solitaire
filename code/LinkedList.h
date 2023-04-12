#ifndef LINKED_LIST_H_INCLUDED
#define LINKED_LIST_H_INCLUDED

#include "Card.h"


typedef struct linkedList {
    int length;
    Card *head;
} LinkedList;

typedef LinkedList Deck;
typedef LinkedList Column;
typedef LinkedList Foundation;

void insert_at_head(LinkedList *, Card *);

void debug_print_linked_list(LinkedList *);

void append(LinkedList *, Card *);

Card *get_card_at_index(LinkedList *, int);

#endif
