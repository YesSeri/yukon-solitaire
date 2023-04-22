//
// Created by henrik on 4/15/23.
//

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
        if (firstFinished && secondFinished) {
            break;
        }
    }
}
