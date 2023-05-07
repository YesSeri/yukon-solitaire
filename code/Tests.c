//
// Created by henrik on 5/5/23.
//

#include "Tests.h"

// TODO write tests for relevant functions. Almost everything in Actions.c and DoublyLinkedList.c should be tested.


// TODO create if statement that actually tests if things are working. Now I am just looking at it manually.
void test_random_shuffling() {

    /*printf("Testing saving deck to file:\n");
    DoublyLinkedList *deck = create_doubly_linked_list();
    create_sorted_deck(deck);
    const char *temp_savename = "test_deck.txt";
    save_deck_to_file(deck, temp_savename);

    char expected_output[1000];
    char temp_output[1000];

    FILE *expected_file = fopen("../decks/sorted_deck.txt", "r");
    FILE *temp_file = fopen("../decks/test_deck.txt", "r");
    int i = 0;
    while((fgets(expected_output, 1000, expected_file) != NULL) && (fgets(temp_output, 1000, temp_file) != NULL)) {

        if(strcmp(expected_output, temp_output) == 0) {
            i++;
            if(i == 52) {
                printf("Saving deck test passed!\n");
            }
        } else {
            printf("Saving deck test failed!\n");
            break;
        }
    }
    fclose(temp_file);
    fclose(expected_file);
    remove("../decks/test_deck.txt");*/


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

// TODO create if statement that actually tests if things are working. Now I am just looking at it manually.
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

void test_game_over() {
    printf("Testing game-over\n");
    DoublyLinkedList *deck = create_doubly_linked_list();

    DoublyLinkedList *_throwaway[NUMBER_OF_COLUMNS];
    Foundation *foundations_arr[NUMBER_OF_FOUNDATIONS];

    initiate_columns_and_foundations(_throwaway, foundations_arr);

    create_sorted_deck(deck);

    printf("deck before adding to foundations\n");
    debug_print(deck);

    for (int i = 0; i < 13; ++i) {
        move_single_card(deck, foundations_arr[0]);
    }
    for (int i = 0; i < 13; ++i) {
        move_single_card(deck, foundations_arr[1]);
    }

    for (int i = 0; i < 13; ++i) {
        move_single_card(deck, foundations_arr[2]);
    }

    for (int i = 0; i < 13; ++i) {
        move_single_card(deck, foundations_arr[3]);
    }

    for (int i = 0; i < 4; ++i) {
        printf("Foundation %d:\n", i);
        debug_print(foundations_arr[i]);
    }
    if (is_gameover(foundations_arr)) {
        printf("SUCCESS: Game over!\n");
    } else {
        printf("ERROR!!! Game not over!\n");
    }
    printf("\n\n");
}

void test_save_deck_to_file() {
    printf("Testing saving deck to file:\n");
    DoublyLinkedList *deck = create_doubly_linked_list();
    create_sorted_deck(deck);
    const char *temp_savename = "test_deck_for_saving_to_file.txt";
    save_deck_to_file(deck, temp_savename);

    char expected_output[1000];
    char temp_output[1000];

    FILE *expected_file = fopen("../decks/sorted_deck.txt", "r");
    FILE *temp_file = fopen("../decks/test_deck_for_saving_to_file.txt", "r");
    int i = 0;
    while((fgets(expected_output, 1000, expected_file) != NULL) && (fgets(temp_output, 1000, temp_file) != NULL)) {

        if(strcmp(expected_output, temp_output) == 0) {
            i++;
            if(i == 52) {
                printf("Saving deck test passed!\n");
            }
        } else {
            printf("Saving deck test failed!\n");
            break;
        }
    }
    fclose(temp_file);
    fclose(expected_file);
    remove("../decks/test_deck.txt");
}

void run_tests() {
    test_interleaved_shuffling();
    test_random_shuffling();
    test_game_over();
    test_save_deck_to_file();
}


void debug_print(DoublyLinkedList *dll) {
    Node *curr = dll->dummy_ptr->next;
    int i = 0;
    while (curr->card_ptr != NULL) {
        i++;
        printf("%2d%c", curr->card_ptr->value, curr->card_ptr->suit);
        curr = curr->next;
        if (i % 13 == 0) {
            printf("\n");
        } else {

            printf(", ");
        }
    }
    fflush(stdout);
}
