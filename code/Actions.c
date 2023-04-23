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

void shuffle_interleaved(DoublyLinkedList *deck, int split_size) {
    // If no argument, or no legal argument is given, we split the deck in the middle.
    if (split_size < 1 || split_size > 51) {
        split_size = 26;
    }
    Node *first_pile = deck->dummy_ptr->next;
    Node *second_pile = get_node_at(deck, split_size);
    Node *first_pile_last_card = second_pile->prev;

    Node *head = deck->dummy_ptr;
    head->next = head;
    head->prev = head;

    bool firstFinished = false;
    bool secondFinished = false;
    while (true) {
        if (split_size > 0) {
            split_size--;
            shuffle_interleaved_insert_card(head, &first_pile);
        } else {
            firstFinished = true;
            break;
        }
        if (second_pile != head) {
            shuffle_interleaved_insert_card(head, &second_pile);
        } else {
            secondFinished = true;
            break;
        }
    }
    if (firstFinished) {
        head->prev->next = second_pile;
        second_pile->prev = head->prev;

        while (second_pile->next != head) {
            second_pile = second_pile->next;
        }
        second_pile->next = head;
        head->prev = second_pile;
    }
    if (secondFinished) {
        head->prev->next = first_pile;
        first_pile->prev = head->prev;

        while (first_pile != first_pile_last_card) {
            first_pile = first_pile->next;
        }
        first_pile->next = head;
        head->prev = first_pile;
    }
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