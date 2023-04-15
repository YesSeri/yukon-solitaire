// This includes #define for ace, 1, 2, ... king and for suits heart, club, diamond, spade.
#include "Card.h"
#include "View.h"
#include "DoublyLinkedList.h"
#include "Foundation.h"
#include "Cli.h"
#include <stdbool.h>
#include <stdio.h>

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
    int col_sizes[] = {1, 6, 7, 8, 9, 10, 11};

    // We copy all the cards from deck to the linked lists, instead of just creating new pointers.
    // We don't want to risk that card orders gets changed and then later we need to save deck.
    // This way we can make sure deck stays intact.

    Node *deck_node_ptr = deck->dummy_ptr->next;
    Node *col_node_ptr;

    for (int height = 0; height < 12; height++) {
        for (int col = 0; col < NUMBER_OF_COLUMNS; col++) {
            if (
                    col == 0 && height < 1 ||
                    col == 1 && height < 6 ||
                    col == 2 && height < 7 ||
                    col == 3 && height < 8 ||
                    col == 4 && height < 9 ||
                    col == 5 && height < 10 ||
                    col == 6 && height < 11
                    ) {
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

    char input[16];
    int input_len = 0;
    ParsedData parsed_data;
    // Point this at the correct function depending on what action the player should take.
    // This is a function pointer.
    void (*actionFn)(DoublyLinkedList *column_arr[7], Foundation *f_arr[7], DoublyLinkedList *, void *parsedData);

    while (1) {
        print_view(columns_arr, foundations_arr);
        while (input_len == 0) {
            getPlayerInput(input, &input_len);
        }
        actionFn = parseInput(input, input_len, &parsed_data);
        if (actionFn == NULL) {
            printf("Invalid input try again.");
            continue;
        }
        actionFn(columns_arr, foundations_arr, deck, &parsed_data);
        input_len = 0;
        break;
    }
    return 0;
}
