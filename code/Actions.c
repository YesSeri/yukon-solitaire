//
// Created by henrik on 4/15/23.
//

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Actions.h"


void save_deck_to_file(DoublyLinkedList *deck, const char *filename) {

    char filepath[100] = "../decks/";
    strcat(filepath, filename);
    FILE *file = fopen(filepath, "w+"); /* should check the result */

    if (file == NULL) {
        yukon_error.error = WRITE_ERR;
        return;
    }

    Node *current = deck->dummy_ptr->next;

    int line_number = 1;
    while (current->card_ptr != NULL) {
        char v = card_value_to_char(current->card_ptr->value);
        Suit s = current->card_ptr->suit;

        putc(v, file);
        putc(s, file);
        putc('\n', file);

        line_number++;
        current = current->next;
    }
//    fprintf(fp, "This is testing for fprintf...\n");
//    fputs("This is testing for fputs...\n", fp);
    fclose(file);
}

void read_file_to_deck(DoublyLinkedList *deck, const char *filename) {
    free_list_cards(deck);
    free_list_nodes(deck);
    char filepath[100] = "../decks/";
    strcat(filepath, filename);
    FILE *file = fopen(filepath, "r"); /* should check the result */
    char line[256];
    if (file == NULL) {
        yukon_error.error = READ_ERR;
        return;
    }
    int line_number = 1;
    while (fgets(line, sizeof(line), file)) {
        Value v = card_char_to_value(line[0]);
        Suit s = line[1];

        Card *c = create_card(s, v, true);
        if (c == NULL) {
            yukon_error.error = INVALID_DECK;
            sprintf(yukon_error.message, "Invalid card in deck: %c%c at line %d - ", line[0], s, line_number);
            return;
        }
        Node *n = create_node(c);
        append(deck, n);
        line_number++;
    }
    if (deck->length != 52) {
        yukon_error.error = INVALID_DECK;
        sprintf(yukon_error.message, "Deck must contain 52 cards - ");
        return;
    }
    /* may check feof here to make a difference between eof and io failure -- network
       timeout for instance */

    fclose(file);

}


// We need double pointer to pile
// because we change the value of the pointer itself here:
// (*pile) = (*pile)->next;
void shuffle_interleaved_insert_card(Node *head, Node **pile) {
    head->next->prev = (*pile);
    // We use (*pile)->prev as temp variable
    (*pile)->prev = head->next;
    head->next = (*pile);
    (*pile) = (*pile)->next;
    head->next->next = head->next->prev;
    head->next->prev = head;
}

void shuffle_interleaved(DoublyLinkedList *deck, int split_size) {
    // If no argument, or no legal argument is given, we split the deck in the middle.
    if (split_size < 1 || split_size > 51) {
        split_size = 26;
    }
    Node *first_pile = deck->dummy_ptr->next;
    Node *second_pile = get_node_at(deck, split_size);
    Node *first_pile_last_card = second_pile->prev;

    Node *head = deck->dummy_ptr;
    head->next = head;
    head->prev = head;

    bool firstFinished = false;
    bool secondFinished = false;
    while (true) {
        if (split_size > 0) {
            split_size--;
            shuffle_interleaved_insert_card(head, &first_pile);
        } else {
            firstFinished = true;
            break;
        }
        if (second_pile != head) {
            shuffle_interleaved_insert_card(head, &second_pile);
        } else {
            secondFinished = true;
            break;
        }
    }
    if (firstFinished) {
        head->prev->next = second_pile;
        second_pile->prev = head->prev;

        while (second_pile->next != head) {
            second_pile = second_pile->next;
        }
        second_pile->next = head;
        head->prev = second_pile;
    }
    if (secondFinished) {
        head->prev->next = first_pile;
        first_pile->prev = head->prev;

        while (first_pile != first_pile_last_card) {
            first_pile = first_pile->next;
        }
        first_pile->next = head;
        head->prev = first_pile;
    }
}


// SR
// initiate srand in main function to make sure the shuffling is random.
void shuffle_random(DoublyLinkedList *deck) {
    int cards_left = 53;
    while (--cards_left) {
        int i = rand() % cards_left;
        Node *n = get_node_at(deck, i);
        delete_node_at(deck, i);
        append(deck, n);
    }
}


/**
 * Make a move on the board and add that move to the history.
 * @param move move we want to make
 * @param column_arr game columns
 * @param foundation_arr foundations
 * @param currentMoveInHistory a pointer to current History Node. Move is added to history if it is valid.
 */

void move_action(Move *move, DoublyLinkedList *column_arr[NUMBER_OF_COLUMNS],
                 DoublyLinkedList *foundation_arr[NUMBER_OF_FOUNDATIONS], struct history_node **currentMoveInHistory) {
    DoublyLinkedList *from = move->is_from_col ? column_arr[move->from] : foundation_arr[move->from];
    DoublyLinkedList *to = move->is_to_col ? column_arr[move->to] : foundation_arr[move->to];
    bool isValid = is_valid_move(move, from, to);
    if (isValid) {
        if (move->card == NULL) {
            move_single_card(from, to);
        } else {
            move_cards(from, to, move->card);
        }
        add_move_to_history(move, currentMoveInHistory);
        // Once we have moved cards we make top card in from list visible.
        Card *c = get_card_at(from, 0);
        if (c) {
            c->is_hidden = false;
        }
    } else {
        yukon_error.error = MOVE_ERR;
    }
}
