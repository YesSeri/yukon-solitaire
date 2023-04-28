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

void debug_print(DoublyLinkedList *);

Node *create_node(Card *);

Node *search_list_for_node(DoublyLinkedList *dll, Card *c_ptr);

Card *get_card_at(DoublyLinkedList *, int);

Node *get_node_at(DoublyLinkedList *, int);

void delete_node_at(DoublyLinkedList *dll, int i);

void append(DoublyLinkedList *, Node *);

void prepend(DoublyLinkedList *, Node *);

void create_sorted_deck(DoublyLinkedList *);

DoublyLinkedList *create_doubly_linked_list();

void move_cards(DoublyLinkedList *from, DoublyLinkedList *to, Card *c);

Node *remove_at(DoublyLinkedList *, int);

void move_single_card(DoublyLinkedList *, DoublyLinkedList *);

Node *debug_to_array(DoublyLinkedList *, Node *[60]);

#endif //CODE_DOUBLYLINKEDLIST_H
