// This includes #define for ace, 1, 2, ... king and for suits heart, club, diamond, spade.
#include "Card.h"
#include "LinkedList.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_COLUMNS 7
#define NUMBER_OF_FOUNDATIONS 4
#define DECK_SIZE 52

typedef LinkedList Deck;
typedef LinkedList Column;
typedef LinkedList Foundation;

void create_unsorted_deck(Deck *list) {
    Suit suits[] = {CLUB, DIAMOND, HEART, SPADE};
    // Suit suits[] = { CLUB, DIAMOND };
    for (int i = 0; i < 4; i++) {
        Suit suit = suits[i];
        for (Value v = ACE; v <= KING; v++) {
            Card *c = create_card(suit, v, false);
            insert_at_head(list, c);
        }
    }
}

void print_header() {
    for (int i = 1; i < 8; i++) {
        printf("C%d\t", i);
    }
    printf("\n");
}


void print_main_section(Column *columns_arr, Foundation *foundations_arr) {
    int max_size = 0;
    Card *col_ptr_arr[NUMBER_OF_COLUMNS];
    for (int i = 0; i < NUMBER_OF_COLUMNS; i++) {
        col_ptr_arr[i] = columns_arr[i].head;
        if (columns_arr[i].length > max_size) {
            max_size = columns_arr[i].length;
        }
    }

    for (int row = 0; row < max_size; row++) {
        for (int col = 0; col < NUMBER_OF_COLUMNS; col++) {
            Card *current = col_ptr_arr[col];
            if (current == NULL) {
                printf("\t");
            } else {
                print_card(current);
                col_ptr_arr[col] = current->next;
            }
        }
        printf("\n");
    }

}

void print_view(Column columns_arr[NUMBER_OF_COLUMNS], Foundation foundations_arr[NUMBER_OF_FOUNDATIONS]) {
    print_header();
    printf("\n");
    print_main_section(columns_arr);
}

void create_columns_arr_from_deck(Deck *deck, Column columns_arr[NUMBER_OF_COLUMNS]) {
    int col_sizes[] = {1, 6, 7, 8, 9, 10, 11};

    // We copy all the cards from deck to the linked lists, instead of just creating new pointers.
    // We don't want to risk that card orders gets changed and then later we need to save deck.
    // This way we can make sure deck stays intact.
    Card *deck_card_ptr = deck->head;
    Card *col_card_ptr = create_card(deck_card_ptr->suit, deck_card_ptr->value, false);
    insert_at_head(&(columns_arr[0]), col_card_ptr);

    for (int i = 1; i < NUMBER_OF_COLUMNS; i++) {
        int size = col_sizes[i];
        for (int j = 0; j < size; j++) {
            // The five first cards in each column are shown when starting game.
            bool is_hidden = j - 5 >= 0;

            deck_card_ptr = deck_card_ptr->next;
            col_card_ptr = create_card(deck_card_ptr->suit, deck_card_ptr->value, is_hidden);
            insert_at_head(&(columns_arr[i]), col_card_ptr);
        }
    }
}

int main() {
    Deck deck;
    deck.head = NULL;
    deck.length = 0;


    Card *c_ptr1 = deck.head;
    c_ptr1 = get(c_ptr1, 2);
    print_card(c_ptr1);

    create_unsorted_deck(&deck);

    Column columns_arr[NUMBER_OF_COLUMNS];
    Foundation foundations_arr[NUMBER_OF_FOUNDATIONS];
    for (int i = 0; i < NUMBER_OF_COLUMNS; i++) {
        columns_arr[i].head = NULL;
        columns_arr[i].length = 0;
    }

    Card *c_ptr = deck.head;
    c_ptr = get(c_ptr, 2);
    print_card(c_ptr);

    create_columns_arr_from_deck(&deck, columns_arr);

    print_view(columns_arr, foundations_arr);
    return 0;
}