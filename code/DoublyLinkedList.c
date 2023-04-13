//
// Created by henrik on 4/12/23.
//

#include "DoublyLinkedList.h"
#include <stdlib.h>

Node *create_node(Card *c_ptr) {
    Node *node = malloc(sizeof(Node));
    node->card_ptr = c_ptr;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

/**
 * insert at end of dll.
 * @param dll
 * @param i
 */
void append(DoublyLinkedList *dll, Node *n_ptr) {
    Node *sentinel = dll->dummy_ptr;
    Node *last = sentinel->prev;
    last->next = n_ptr;
    n_ptr->prev = last;
    n_ptr->next = sentinel;
    sentinel->prev = n_ptr;
    dll->length++;
}

void prepend(DoublyLinkedList *dll, Node *n_ptr) {

}

void create_unsorted_deck(DoublyLinkedList *dll) {
    Suit suits[] = {CLUB, DIAMOND, HEART, SPADE};
    for (int i = 0; i < 4; i++) {
        Suit suit = suits[i];
        for (Value v = ACE; v <= KING; v++) {
            Card *c = create_card(suit, v, false);
            Node *n = create_node(c);

            append(dll, n);
        }
    }
}

DoublyLinkedList *create_doubly_linked_list() {
    DoublyLinkedList *dll = malloc(sizeof(DoublyLinkedList));
    Node *dummy_ptr = create_node(NULL);
    dll->dummy_ptr = dummy_ptr;
    dll->length = 0;
    dll->dummy_ptr->next = dll->dummy_ptr;
    dll->dummy_ptr->prev = dll->dummy_ptr;
    return dll;
}
