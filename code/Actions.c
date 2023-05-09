//
// Created by henrik on 4/15/23.
//

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Actions.h"

void write_card_to_file(FILE *file, char val, char suit);

void save_deck_to_file(DoublyLinkedList *deck, const char *filename) {

    char filepath[100] = "../decks/";
    strcat(filepath, filename);
    FILE *file = fopen(filepath, "w+");

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
    fclose(file);
}

void load_deck_file(DoublyLinkedList *deck, const char *filename) {
    free_list_cards(deck);
    free_list_nodes(deck);
    char filepath[100] = "../decks/";
    strcat(filepath, filename);
    FILE *file = fopen(filepath, "r");
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

/*
 * Save the current state of the game to a file.
 * we use x as delimiter
 */


void write_card_to_file(FILE *file, char val, char suit) {
    putc(val, file);
    putc(suit, file);
    putc('\n', file);
}

void load_state(DoublyLinkedList *deck, DoublyLinkedList **column_arr, DoublyLinkedList **foundation_arr,
                const char *filename) {

    free_list_cards(deck);
    free_list_cards(column_arr);
    free_list_cards(foundation_arr);

    free_list_nodes(deck);
    free_list_nodes(column_arr);
    free_list_nodes(foundation_arr);

    initiate_columns_and_foundations(column_arr, foundation_arr);

    char filepath[100] = "../save_state/";
    strcat(filepath, filename);
    FILE *file = fopen(filepath, "r");
    char line[16];
    if (file == NULL) {
        yukon_error.error = READ_ERR;
        return;
    }
    while (1) {
        fgets(line, sizeof(line), file);

        if (line[0] == 'C') {
            break;
        }
        bool isHidden = line[0] == '-';
        Value v = card_char_to_value(line[1]);
        Suit s = line[2];

        Card *c = create_card(s, v, isHidden);
        if (c == NULL) {
            yukon_error.error = INVALID_DECK;
            sprintf(yukon_error.message, "Invalid card in deck: %c%c - ", line[0], s);
            return;
        }
        Node *n = create_node(c);
        append(deck, n);

        if (deck->length > 52) {
            yukon_error.error = INVALID_DECK;
            sprintf(yukon_error.message, "Deck must contain 52 cards - ");
            return;
        }
    }

    if (deck->length < 52) {
        yukon_error.error = INVALID_DECK;
        sprintf(yukon_error.message, "Deck must contain 52 cards - ");
        return;
    }
    for (int i = 0; i < 7; ++i) {
        while (1) {
            fgets(line, sizeof(line), file);
            if (line[0] == '-') {
                break;
            }

            Value v = card_char_to_value(line[0]);
            Suit s = line[1];

            Node *node = search_deck_for_node_with_card_value_of(deck, v, s);

            if (node == NULL) {
                yukon_error.error = INVALID_DECK;
                strcpy(yukon_error.message, "The deck state is invalid in a column - ");
                return;
            } else {
                Node *n = create_node(node->card_ptr);
                append(column_arr[i], n);
            }
        }
    }
    fgets(line, sizeof(line), file);
    if (line[0] != 'F') {
        yukon_error.error = INVALID_DECK;
        strcpy(yukon_error.message, "The foundation delimiter is missing - ");
        return;
    }

    for (int i = 0; i < 4; ++i) {
        while (1) {
            fgets(line, sizeof(line), file);
            if (line[0] == '-') {
                break;
            }

            Value v = card_char_to_value(line[0]);
            Suit s = line[1];

            Node *node = search_deck_for_node_with_card_value_of(deck, v, s);

            if (node == NULL) {
                yukon_error.error = INVALID_DECK;
                strcpy(yukon_error.message, "The deck state is invalid in a column - ");
                return;
            } else {
                Node *n = create_node(node->card_ptr);
                append(foundation_arr[i], n);
            }
        }
    }

    /* may check feof here to make a difference between eof and io failure -- network
       timeout for instance */

    fclose(file);


}

void save_state(DoublyLinkedList *deck, DoublyLinkedList **column_arr, DoublyLinkedList **foundation_arr,
                const char *filename) {


    char filepath[100] = "../save_state/";
    strcat(filepath, filename);
    FILE *file = fopen(filepath, "w+");

    if (file == NULL) {
        yukon_error.error = WRITE_ERR;
        return;
    }

    Node *deck_ptr = deck->dummy_ptr->next;

    int line_number = 1;
    while (deck_ptr->card_ptr != NULL) {
        bool isHidden = deck_ptr->card_ptr->is_hidden;
        char visibilityIndicator = isHidden ? '-' : '+';
        putc(visibilityIndicator, file);
        char v = card_value_to_char(deck_ptr->card_ptr->value);
        Suit s = deck_ptr->card_ptr->suit;

        write_card_to_file(file, v, s);

        line_number++;
        deck_ptr = deck_ptr->next;
    }
    putc('C', file);
    putc('\n', file);


    for (int i = 0; i < NUMBER_OF_COLUMNS; ++i) {
        Node *col_ptr = column_arr[i]->dummy_ptr->next;
        while (col_ptr->card_ptr != NULL) {
            char v = card_value_to_char(col_ptr->card_ptr->value);
            Suit s = col_ptr->card_ptr->suit;

            write_card_to_file(file, v, s);
            col_ptr = col_ptr->next;
        }

        putc('-', file);
        putc('\n', file);
    }
    putc('F', file);
    putc('\n', file);
    for (int i = 0; i < NUMBER_OF_FOUNDATIONS; ++i) {
        Node *f_ptr = foundation_arr[i]->dummy_ptr->next;
        while (f_ptr->card_ptr != NULL) {
            char v = card_value_to_char(f_ptr->card_ptr->value);
            Suit s = f_ptr->card_ptr->suit;

            write_card_to_file(file, v, s);
            f_ptr = f_ptr->next;
        }

        putc('-', file);
        putc('\n', file);
    }
    fclose(file);
}

