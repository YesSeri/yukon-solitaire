//
// Created by henrik on 5/5/23.
//

#include "Tests.h"

// TODO write tests for relevant functions. Almost everything in Actions.c and DoublyLinkedList.c should be tested.


void test_random_shuffling() {
    printf("Testing random shuffling\n");
    DoublyLinkedList *deck = create_doubly_linked_list();
    create_sorted_deck(deck);
    printf("Before shuffling.\n");
    debug_print(deck);
    printf("Shuffled:\n");
    shuffle_random(deck);
    debug_print(deck);
    printf("\n\n");
}

void test_interleaved_shuffling() {
    printf("Testing interleaved shuffling\n");
    DoublyLinkedList *deck = create_doubly_linked_list();
    create_sorted_deck(deck);
    printf("Before shuffling.\n");
    debug_print(deck);
    printf("Shuffling with arg 13.\n");
    shuffle_interleaved(deck, 13);
    debug_print(deck);
    printf("\n\n");
}

void run_tests() {
    test_interleaved_shuffling();
    test_random_shuffling();
}
