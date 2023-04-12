// This includes #define for ace, 1, 2, ... king and for suits heart, club, diamond, spade.
#include "Card.h"
#include "LinkedList.h"
#include "View.h"
#include "DoublyLinkedList.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_COLUMNS 7
#define NUMBER_OF_FOUNDATIONS 4
#define DECK_SIZE 52
#define MIN_HEIGHT_MAIN_SECTION 7


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


void create_columns_arr_from_deck(Deck *deck, Column columns_arr[NUMBER_OF_COLUMNS]) {
    int col_sizes[] = {1, 6, 7, 8, 9, 10, 11};

    // We copy all the cards from deck to the linked lists, instead of just creating new pointers.
    // We don't want to risk that card orders gets changed and then later we need to save deck.
    // This way we can make sure deck stays intact.


    Card *deck_card_ptr = get_card_at_index(deck, 0);
    Card *col_card_ptr = create_card(deck_card_ptr->suit, deck_card_ptr->value, false);
    insert_at_head(&(columns_arr[0]), col_card_ptr);

    for (int i = 1; i < NUMBER_OF_COLUMNS; i++) {
        int size = col_sizes[i];
        for (int j = 0; j < size; j++) {
            // The five first cards in each column are shown when starting game.
//            bool is_hidden = j + 5 < size;
            bool is_hidden = false;
            deck_card_ptr = deck_card_ptr->next;

            col_card_ptr = create_card(deck_card_ptr->suit, deck_card_ptr->value, is_hidden);
            insert_at_head(&(columns_arr[i]), col_card_ptr);
        }
    }
}

int main() {
//    DoublyLinkedList *dll = create_doubly_linked_list();
//    int v1 = 7;
//    int v2 = 1;
//    int v3 = 3;
//    Node *n1 = create_node(&v1);
//    Node *n2 = create_node(&v2);
//    Node *n3 = create_node(&v3);
//    append_end(dll, n1);
//    append_end(dll, n2);
//    append_end(dll, n3);
//
//    Node *current = n1;
//    while (current->card_ptr != NULL) {
//        printf("i: %d\n", *current->card_ptr);
//        current = current->next;
//    }

    DoublyLinkedList *dll = create_doubly_linked_list();
//    Deck deck;


    create_unsorted_deck(dll);

    DoublyLinkedList *columns_arr[NUMBER_OF_COLUMNS];
    DoublyLinkedList *foundations_arr[NUMBER_OF_FOUNDATIONS];
    for (int i = 0; i < NUMBER_OF_COLUMNS; i++) {
        columns_arr[i] = create_doubly_linked_list();
    }

    for (int i = 0; i < NUMBER_OF_FOUNDATIONS; i++) {
        foundations_arr[i] = create_doubly_linked_list();
    }

    print_view(columns_arr, foundations_arr);
    create_columns_arr_from_deck(&dll, columns_arr);

    print_view(columns_arr, foundations_arr);
    return 0;
}


