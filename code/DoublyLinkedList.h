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
    int length;
} DoublyLinkedList;

Node *create_node(Card *);

Node *search_list_for_card(DoublyLinkedList *dll, Card c_ptr);

Card *get_card_at(DoublyLinkedList *, int);

Node *get_node_at(DoublyLinkedList *, int);

void append(DoublyLinkedList *, Node *);

void prepend(DoublyLinkedList *, Node *);

void create_unsorted_deck(DoublyLinkedList *);

DoublyLinkedList *create_doubly_linked_list();

#endif //CODE_DOUBLYLINKEDLIST_H
