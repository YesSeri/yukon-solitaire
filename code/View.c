//
// Created by henrik on 4/12/23.
//
#include <stdio.h>
#include "View.h"

#define NUMBER_OF_COLUMNS 7
#define NUMBER_OF_FOUNDATIONS 4
#define MIN_HEIGHT_MAIN_SECTION 7


void print_header() {
    for (int i = 1; i < 8; i++) {
        printf("C%d\t", i);
    }
    printf("\n");
}

void print_main_section(DoublyLinkedList *columns_arr[NUMBER_OF_COLUMNS],
                        Foundation *foundations_arr[NUMBER_OF_FOUNDATIONS]) {
    int max_size = 0;
    for (int i = 0; i < NUMBER_OF_COLUMNS; i++) {
        if (columns_arr[i]->length > max_size) {
            max_size = columns_arr[i]->length;
        }
    }
    // We need minimum 7 rows to render all 4 foundations, at row 0, 2, 4 and 6.
    int height = max_size < MIN_HEIGHT_MAIN_SECTION ? MIN_HEIGHT_MAIN_SECTION : max_size;
    char card_string[3];
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < NUMBER_OF_COLUMNS; col++) {
            int col_length = columns_arr[col]->length;
            if (row < col_length) {
                Node *current = get_node_at(columns_arr[col], col_length - row - 1);
                get_card_string(current->card_ptr, card_string);
                printf("%s", card_string);
            }
            printf("\t");
        }
        if (row % 2 == 0 && row < MIN_HEIGHT_MAIN_SECTION) {
            Foundation *foundation = foundations_arr[row / 2];
            Card *current = peek(foundation);
            get_card_string(current, card_string);
            printf("\t%s\tF%d", card_string, row / 2 + 1);
        }
        printf("\n");
    }
}

void print_footer(char *prev_command) {
    printf("LAST Command: %s\n", prev_command);
    printf("Message: %s\n", yukon_error.message);
    if (yukon_error.error != GAME_OVER) {
        printf("INPUT > ");
    }

}

void print_view(DoublyLinkedList *columns_arr[NUMBER_OF_COLUMNS], Foundation *foundations_arr[NUMBER_OF_FOUNDATIONS],
                char *prev_command) {
    // Clears screen, so only the current view is shown.
    printf("\e[1;1H\e[2J");
    printf("\n");
    print_header();
    printf("\n");
    print_main_section(columns_arr, foundations_arr);
    printf("\n");
    print_footer(prev_command);
    fflush(stdout);
}
