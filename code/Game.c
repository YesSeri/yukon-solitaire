// This includes #define for ace, 1, 2, ... king and for suits heart, club, diamond, spade.
#include "Card.h"
#include "View.h"
#include "DoublyLinkedList.h"
#include "Foundation.h"
#include "Cli.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//void create_unsorted_deck(Deck *list) {
//    Suit suits[] = {CLUB, DIAMOND, HEART, SPADE};
//    for (int i = 0; i < 4; i++) {
//        Suit suit = suits[i];
//        for (Value v = ACE; v <= KING; v++) {
//            Card *c = create_card(suit, v, false);
//            append(list, c);
//        }
//    }
//}

void create_columns_arr_from_deck(DoublyLinkedList *deck, DoublyLinkedList *columns_arr[NUMBER_OF_COLUMNS]) {
    int col_heights[] = {1, 6, 7, 8, 9, 10, 11};

    // We copy all the cards from deck to the linked lists, instead of just creating new pointers.
    // We don't want to risk that card orders gets changed and then later we need to save deck.
    // This way we can make sure deck stays intact.

    Node *deck_node_ptr = deck->dummy_ptr->next;
    Node *col_node_ptr;

    for (int height = 0; height < 20; height++) {
        for (int col = 0; col < NUMBER_OF_COLUMNS; col++) {
            if (col_heights[col] - height > 0) {
                // TODO Hide cards from player
                bool is_hidden;
                if (col == 1 && height < 1 || col == 2 && height < 2 || col == 3 && height < 3 ||
                    col == 4 && height < 4 || col == 5 && height < 5 || col == 6 && height < 6)
                    is_hidden = true;
                else {
                    is_hidden = false;
                }

                Card *c = create_card(deck_node_ptr->card_ptr->suit, deck_node_ptr->card_ptr->value, is_hidden);
                col_node_ptr = create_node(c);
                prepend(columns_arr[col], col_node_ptr);
                deck_node_ptr = deck_node_ptr->next;
            }
        }
    }
}

int main() {
    DoublyLinkedList *deck = create_doubly_linked_list();
    create_unsorted_deck(deck);
    DoublyLinkedList *columns_arr[NUMBER_OF_COLUMNS];
    Foundation *foundations_arr[NUMBER_OF_FOUNDATIONS];

    for (int i = 0; i < NUMBER_OF_COLUMNS; i++) {
        columns_arr[i] = create_doubly_linked_list();
    }

    for (int i = 0; i < NUMBER_OF_FOUNDATIONS; i++) {
        foundations_arr[i] = create_stack();
    }

    create_columns_arr_from_deck(deck, columns_arr);

    // Point this at the correct function depending on what action the player should take.
    // This is a function pointer.

    while (1) {
        char input[16];
        int input_len = 0;
        print_view(columns_arr, foundations_arr);
        while (input_len == 0) {
            get_player_input(input, &input_len);
        }

        /*
         * Tobs btw
         * I imagine the flow going like this:
         * get input
         * figure out type of input in parseInput
         * This function then returns the way to show results in the form of printFn
         * do what you need to do to the type of input, by first parsing the command, and then running the corresponding function
         * print the output by calling the printFn
         *
         */
        CommandType command = parse_input_type(input, input_len);
        switch (command) {
            case MOVE: {

                int from = col_index_to_int(&input[0]);
                Card *c;
                int to;
                int offset = input[2] == ':' ? 9 : 7;
                if (input[2] == ':' && from < 8) {
                    Suit s = input[3];
                    Value v = input[4] - '0';
                    c = create_card(s, v, false);
                    to = col_index_to_int(&input[9]);
                } else {
                    c = NULL;
                    to = col_index_to_int(&input[6]);
                }
                if (from == -1 || to == -1) {
                    goto INPUT_ERROR;
                }
                printf("from: %d, to: %d");
                break;
            }
            case QUIT:
                printf("Quitting game...");
                fflush(stdout);
                exit(0);
            case ERROR:
            default:
            INPUT_ERROR:
                printf("Invalid input, try again.");
                continue;
        }

    }
    return 0;
}


void show_action(char *input) {
    printf("Showing cards...\n");
}

void load_action(char *input) {
    printf("Loading data...\n");
}

void quit_action(char *input) {
    printf("Quitting game...\n");
}

void to_startup_action(char *input) {
    printf("Switching to startup phase...\n");
}

void to_play_action(char *input) {
    printf("Switching to play phase...\n");
}

void move_action(char *input) {
    Move *move = parse_move(input);
//TODO figure out how to parse the move to the move cards function
    //move_cards()
}

void error_action(char *input) {
    printf("Error: %s is not a valid input.\n", input);
}

