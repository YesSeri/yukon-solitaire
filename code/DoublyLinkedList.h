//
// Created by henrik on 4/12/23.
//

#ifndef CODE_DOUBLYLINKEDLIST_H
#define CODE_DOUBLYLINKEDLIST_H

#include "Card.h"

typedef struct node {
    struct node *next;
    struct node *prev;
    Card *card_ptr;
} Node;

typedef struct {
    Node *dummy_ptr;
} DoublyLinkedList;

Node *create_node(Card *);

void append_end(DoublyLinkedList *, Node *);

void create_unsorted_deck(DoublyLinkedList *);

DoublyLinkedList *create_doubly_linked_list();

#endif //CODE_DOUBLYLINKEDLIST_H
