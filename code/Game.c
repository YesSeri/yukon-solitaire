// This includes #define for ace, 1, 2, ... king and for suits heart, club, diamond, spade.
#include "Card.h"
#include "Cli.h"
#include "DoublyLinkedList.h"
#include "Foundation.h"
#include "View.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// void create_unsorted_deck(Deck *list) {
//     Suit suits[] = {CLUB, DIAMOND, HEART, SPADE};
//     for (int i = 0; i < 4; i++) {
//         Suit suit = suits[i];
//         for (Value v = ACE; v <= KING; v++) {
//             Card *c = create_card(suit, v, false);
//             append(list, c);
//         }
//     }
// }

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
                bool is_hidden = false;
                Card *c = create_card(deck_node_ptr->card_ptr->suit, deck_node_ptr->card_ptr->value, is_hidden);
                col_node_ptr = create_node(c);
                prepend(columns_arr[col], col_node_ptr);
                deck_node_ptr = deck_node_ptr->next;
            }
        }
    }
}

int main() {
    // DoublyLinkedList* deck = create_doubly_linked_list();
    // create_unsorted_deck(deck);
    // DoublyLinkedList* columns_arr[NUMBER_OF_COLUMNS];
    // Foundation* foundations_arr[NUMBER_OF_FOUNDATIONS];

    // for (int i = 0; i < NUMBER_OF_COLUMNS; i++) {
    //     columns_arr[i] = create_doubly_linked_list();
    // }

    // for (int i = 0; i < NUMBER_OF_FOUNDATIONS; i++) {
    //     foundations_arr[i] = create_stack();
    // }

    // create_columns_arr_from_deck(deck, columns_arr);

//    ParsedInputData *parsed_data;

    while (1) {
        // print_view(columns_arr, foundations_arr);
        char input[16] = "";
        int input_len = 0;
        while (input_len == 0) {
            get_player_input(input, &input_len);
        }
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
