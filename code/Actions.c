//
// Created by henrik on 4/15/23.
//

#include <stdlib.h>
#include "Actions.h"

void quit_game() {
}

void move_from_col() {
}


// We need double pointer to pile
// because we change the value of the pointer itself here:
// (*pile) = (*pile)->next;
void shuffle_interleaved_insert_card(Node *head, Node **pile) {

    head->next->prev = (*pile);
    // We use (*pile)->prev as temp variable
    (*pile)->prev = head->next;
    head->next = (*pile);
    (*pile) = (*pile)->next;
    head->next->next = head->next->prev;
    head->next->prev = head;
}

DoublyLinkedList *shuffle_interleaved(DoublyLinkedList *deck, int split_size) {
    // If no argument, or no legal argument is given, we split the deck in the middle.
    if (split_size < 1 || split_size > 51) {
        split_size = 26;
    }
    Node *firstPile = deck->dummy_ptr->next;
    Node *secondPile = get_node_at(deck, split_size);
    Node *head = deck->dummy_ptr;
    head->next = head;
    head->prev = head;
    deck->length = 0;

    bool firstFinished = false;
    bool secondFinished = false;
    while (true) {
        if (split_size > 0) {
            split_size--;
            shuffle_interleaved_insert_card(head, &firstPile);
        } else {
            firstFinished = true;
        }
        if (secondPile != head) {
            shuffle_interleaved_insert_card(head, &secondPile);
        } else {
            secondFinished = true;
        }
        if (firstFinished || secondFinished) {
            break;
        }
    }
    if (firstFinished) {
        Node *last_first_pile = firstPile;
        head->prev->next = secondPile;
        secondPile->prev = head->prev;

        while (secondPile->next != head) {
            secondPile = secondPile->next;
        }
        secondPile->next = head;
        head->prev = secondPile;

    }
    // TODO if(secondFinished)
}


// SR
void shuffle_random(DoublyLinkedList *deck) {
    int cards_left = 53;
    while (--cards_left) {
//         This makes random more random. It is initiated with a random seed. If this is not run, seed is always 1.
        int i = rand() % cards_left;
        Node *n = get_node_at(deck, i);
        delete_node_at(deck, i);
        append(deck, n);

    }
}