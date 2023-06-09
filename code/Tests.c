//
// Created by henrik on 5/5/23.
//

#include "Tests.h"

// TODO write tests for relevant functions. Almost everything in Actions.c and DoublyLinkedList.c should be tested.

/**
 * Makes two moves and the undos them.
 */
void test_undo() {
    printf("Test 'undo' command:\n");
    DoublyLinkedList *deck = create_doubly_linked_list();
    create_sorted_deck(deck);
    DoublyLinkedList *column_arr[NUMBER_OF_COLUMNS];
    Foundation *foundation_arr[NUMBER_OF_FOUNDATIONS];
    initiate_columns_and_foundations(column_arr, foundation_arr);

    struct history_node **currentMoveInHistory;
    struct history_node *dummy_ptr = create_history_node(NULL);
    currentMoveInHistory = &dummy_ptr;
    dummy_ptr->next = dummy_ptr;
    dummy_ptr->prev = dummy_ptr;

    Phase phase = STARTUP;

    to_play_phase(column_arr, foundation_arr, deck, &phase);

    printf("Before move.\n");
    print_main_section(column_arr, foundation_arr);
    printf("Move: C1 -> F1\n");
    Move *move = parse_move("C1 -> F1");
    move_action(move, column_arr, foundation_arr, currentMoveInHistory);

    printf("Move: C3:7H -> C2\n");
    move = parse_move("C3:7H -> C2");
    move_action(move, column_arr, foundation_arr, currentMoveInHistory);

    print_main_section(column_arr, foundation_arr);

    printf("1st undo\n");
    undo_move(column_arr, foundation_arr, currentMoveInHistory);
    print_main_section(column_arr, foundation_arr);

    printf("2nd undo\n");
    undo_move(column_arr, foundation_arr, currentMoveInHistory);
    print_main_section(column_arr, foundation_arr);

}

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

    printf("Testing random shuffling:\n");

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
    printf("Testing interleaved shuffling:\n");
    DoublyLinkedList *deck = create_doubly_linked_list();
    create_sorted_deck(deck);
    printf("Before shuffling.\n");
    debug_print(deck);
    printf("Shuffling with arg 13.\n");
    shuffle_interleaved(deck, 13);
    debug_print(deck);

    save_deck_to_file(deck, "interleaved_deck_test.txt");
    char expected_output[1000];
    char temp_output[1000];

    FILE *expected_file = fopen("../decks/interleaved_deck.txt", "r");
    FILE *temp_file = fopen("../decks/interleaved_deck_test.txt", "r");
    int i = 0;
    while ((fgets(expected_output, 1000, expected_file) != NULL) && (fgets(temp_output, 1000, temp_file) != NULL)) {

        if (strcmp(expected_output, temp_output) == 0) {
            i++;
            if (i == 52) {
                printf("Interleaved shuffling test PASSED!\n\n");
            }
        } else {
            printf("Interleaved shuffling test FAILED!\n\n");
            break;
        }
    }
    fclose(temp_file);
    fclose(expected_file);
    remove("../decks/interleaved_deck_test.txt");
    printf("\n");
}


void test_game_over() {
    printf("Testing game-over:\n");
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
    while ((fgets(expected_output, 1000, expected_file) != NULL) && (fgets(temp_output, 1000, temp_file) != NULL)) {

        if (strcmp(expected_output, temp_output) == 0) {
            i++;
            if (i == 52) {
                printf("Saving deck test passed!\n");
            }
        } else {
            printf("Saving deck test failed!\n");
            break;
        }
    }
    fclose(temp_file);
    fclose(expected_file);
    remove("../decks/test_deck_for_saving_to_file.txt");
    printf("\n");
}

void test_read_file_to_deck() {
    printf("Testing loading deck from file:\n");
    DoublyLinkedList *deck1 = create_doubly_linked_list();
    load_deck_file(deck1, "sorted_deck.txt");
    DoublyLinkedList *deck2 = create_doubly_linked_list();
    create_sorted_deck(deck2);

    Node *curr1 = deck1->dummy_ptr->next;
    Node *curr2 = deck2->dummy_ptr->next;
    int i = 0;
    while (curr1 != NULL && curr2 != NULL && i < deck1->length) {
        Card *card1 = curr1->card_ptr;
        Card *card2 = curr2->card_ptr;
        if (card1->value != card2->value || card1->suit != card2->suit) {
            printf("Read from file to deck test failed!");
            break;
        }
        curr1 = curr1->next;
        curr2 = curr2->next;
        i++;
    }
    if (i == deck1->length) {
        printf("Read from file to deck test passed!\n");
    } else {
        printf("TEST FAILED: Read from file deck was not same length as default deck.!\n");

    }



/*
    char expected_output[1000];
    char temp_output[1000];

    FILE *expected_file = fopen("../decks/sorted_deck.txt", "r");
    FILE *temp_file = fopen("../decks/test_deck_for_saving_to_file.txt", "r");
    int i = 0;
    while ((fgets(expected_output, 1000, expected_file) != NULL) && (fgets(temp_output, 1000, temp_file) != NULL)) {

        if (strcmp(expected_output, temp_output) == 0) {
            i++;
            if (i == 52) {
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
}


void run_tests() {

    test_interleaved_shuffling();
    test_random_shuffling();
    test_game_over();
    test_undo();
    test_save_deck_to_file();
    test_read_file_to_deck();

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
