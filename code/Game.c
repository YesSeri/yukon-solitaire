// This includes #define for ace, 1, 2, ... king and for suits heart, club, diamond, spade.
#include "Card.h"
#include "View.h"
#include "DoublyLinkedList.h"
#include "Foundation.h"
#include "Cli.h"
#include "Game.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
// TODO error handling with global variable.

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

bool is_valid_move(Move *, DoublyLinkedList *, DoublyLinkedList *);

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

void move_action(Move *move, DoublyLinkedList *from_list, DoublyLinkedList *to_list) {
// TODO move multiple cards
// TODO move to and from foundations
    printf("Move to make: ");
    if (move->card == NULL) {
        printf("Moving top card, from: %d, To: %d\n", move->from, move->to);
        move_single_card(from_list, to_list);

        free(move);
    } else {
        printf("From: %d, To: %d, Card: %c%d\n", move->from, move->to, move->card->suit, move->card->value);
        move_cards(from_list, to_list, move->card);
        free(move->card);
        free(move);
    }
    // Once we have moved cards we make top card in from list visible.
    Card *c = get_card_at(from_list, 0);
    if (c) {
        c->is_hidden = false;
    }


    // Free pointers after move


}

bool is_valid_move(Move *move, DoublyLinkedList *from, DoublyLinkedList *to) {

    // Move multiple cards
    // You can never move several cards to a column.
    if (move->is_to_col) {
        // Move one card

        Card *card_from;
        Card *card_to = get_node_at(to, 0)->card_ptr;
        if (move->card == NULL) {
            card_from = get_node_at(from, 0)->card_ptr;
            // If card_ptr is empty the dummy ptr points to itself, meaning there are no cards in this column or foundation.
        } else {
            card_from = search_list_for_node(from, move->card)->card_ptr;
        }
        // Card must exist in column
        if (card_from == NULL) {
            return false;
        }
        // Card must be one lower than the col it is moving to and of a different suit
        if (!(card_from->value == card_to->value - 1 || card_from->suit != card_to->suit)) {
            return false;
        }
    } else {
        return validate_to_foundation_move();
    }
    // TODO empty columns can only be filled with a king
    return true;
}

bool validate_to_foundation_move() {
    return false;
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
    while (1) {
        char input[16];
        int input_len = 0;
        print_view(columns_arr, foundations_arr);
        while (input_len == 0) {
            get_player_input(input, &input_len);
        }

        CommandType command = parse_input_type(input, input_len);
        switch (command) {
            case MOVE: {
                Move *move = parse_move(input);
                DoublyLinkedList *from = move->is_from_col ? columns_arr[move->from] : foundations_arr[move->from];
                DoublyLinkedList *to = move->is_to_col ? columns_arr[move->to] : foundations_arr[move->to];
                bool isValid = is_valid_move(move, from, to);
                if (isValid) {
                    move_action(move, from, to);
                } else {
                    goto HANDLE_ERROR;
                }
            }
            case QUIT:
                printf("Quitting game...");
                break;
            case ERROR:
            default:
            HANDLE_ERROR:
                printf("Invalid input, try again.");
                continue;
        }

    }
    return 0;
}


