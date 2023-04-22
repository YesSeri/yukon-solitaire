//
// Created by henrik on 4/15/23.
//

#include "Actions.h"

void quit_game() {
}

void move_from_col() {
}


//DoublyLinkedList *shuffle_interleaved(DoublyLinkedList *deck, int split_size) {
//    Node *firstPile = deck->dummy_ptr;
//    firstPile->prev->next = NULL;
//    Node *secondPile = get_node_at(deck, split_size);
//    secondPile->prev->next = NULL;
//    DoublyLinkedList *start = create_doubly_linked_list();
//    while (true) {
//        if (firstPile->next != NULL) {
//            firstPile = firstPile->next;
//            append(start, firstPile);
//        }
//        if (secondPile->next != NULL) {
//            secondPile = secondPile->next;
//            append(start, secondPile);
//        }
//        if (firstPile->next == NULL && secondPile->next == NULL) {
//            break;
//        }
//    }
//}
//
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
    while (true) {
        int isFinished = 0;
        if (split_size > 0) {
            split_size--;
            head->next->prev = firstPile;
            // We use firstpile->prev as temp variable
            firstPile->prev = head->next;
            head->next = firstPile;
            firstPile = firstPile->next;
            head->next->next = head->next->prev;
            head->next->prev = head;
        } else {
            isFinished++;
        }
        if (secondPile != head) {
            head->next->prev = secondPile;
            // We use secondpile->prev as temp variable
            secondPile->prev = head->next;
            head->next = secondPile;
            secondPile = secondPile->next;
            head->next->next = head->next->prev;
            head->next->prev = head;
        } else {
            isFinished++;
        }
        if (isFinished == 2) {
            break;
        }
    }
}
