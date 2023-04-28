// This includes #define for ace, 1, 2, ... king and for suits heart, club, diamond, spade.
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Game.h"


// TODO come up with more

// Global variable. We set this to error if we encounter one, and then we handle error after switch case in main game loop.
YukonError yukon_error = {NO_ERROR, "OK"};


bool is_valid_move(Move *, DoublyLinkedList *, DoublyLinkedList *);


void save_deck_to_file(DoublyLinkedList *deck, union argument *pArgument);

// This adds all the cards from the deck to the columns.
// The cards are copied,
// because we need to keep a copy of the deck in case the player wants to return to the startup phase and save deck.
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
        printf("Moving top card, from: %d, To: %d\n", move->from + 1, move->to + 1);
        move_single_card(from_list, to_list);

        free(move);
    } else {
        printf("From: %d, To: %d, Card: %c%d\n", move->from, move->to, move->card->suit, move->card->value);
        fflush(stdout);
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

        Card *card_from = NULL;
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
        if (!(card_from->value == card_to->value - 1 || card_from->suit == card_to->suit)) {
            return false;
        }
    } else {
        return validate_to_foundation_move();
    }
    // TODO empty columns can only be filled with a king
    return true;
}

void initiate_columns_and_foundations(DoublyLinkedList **columns_arr, Foundation **foundations_arr) {
    // Creates empty linked lists for all columns and foundations
    for (int i = 0; i < NUMBER_OF_COLUMNS; i++) {
        columns_arr[i] = create_doubly_linked_list();
    }

    for (int i = 0; i < NUMBER_OF_FOUNDATIONS; i++) {
        foundations_arr[i] = create_stack();
    }
}


bool validate_to_foundation_move() {
    return false;
}


int run_game() {
    // srand makes sure the random shuffle is always different each time.
    // Without this, the random shuffle always uses the same seed,
    // meaning the shuffling will be exactly the same each time.
    srand(time(NULL));
    DoublyLinkedList *deck = create_doubly_linked_list();
    DoublyLinkedList *columns_arr[NUMBER_OF_COLUMNS];
    Foundation *foundations_arr[NUMBER_OF_FOUNDATIONS];
    initiate_columns_and_foundations(columns_arr, foundations_arr);
//    create_columns_arr_from_deck(deck, columns_arr);
//    create_unsorted_deck(deck);


    /*
     * Tobs btw
     * I imagine the flow going like this//        Card *c = create_card(s, v, false);
//        if (c == NULL) {
//            yukon_error.error = INVALID_DECK;
//            sprintf(yukon_error.message, "Invalid card in deck: %c%c at line %d", line[0], s, line_number);
//            return;
//        }
//        Node *n = create_node(c);
//        append(deck, n);
:
     * get input
     * figure out type of input in parseInput
     * This function then returns the way to show results in the form of printFn
     * do what you need to do to the type of input, by first parsing the command, and then running the corresponding function
     * print the output by calling the printFn
     *
     */

    char last_command[2 + ARG_LENGTH + 1] = "";
    Command command;
    while (1) {
        char input[2 + ARG_LENGTH + 1];
        input[0] = '\0';
        print_view(columns_arr, foundations_arr, last_command);
        yukon_error.error = NO_ERROR;
        if (strlen(input) != 0) {
            exit(0);
        }
        while (strlen(input) == 0) {
            get_player_input(input);
        }
        strcpy(last_command, input);
        parse_input_type(input, &command);
        fflush(stdout);
        switch (command.type) {
            case MOVE: {
                Move *move = parse_move(input);
                DoublyLinkedList *from = move->is_from_col ? columns_arr[move->from] : foundations_arr[move->from];
                DoublyLinkedList *to = move->is_to_col ? columns_arr[move->to] : foundations_arr[move->to];
                bool isValid = is_valid_move(move, from, to);
                if (isValid) {
                    move_action(move, from, to);
                } else {
                    yukon_error.error = MOVE_ERR;
                }
            }
                break;
            case QUIT:
                printf("Quitting game...");
                exit(0);
            case SAVE_DECK:
                if (command.has_arg) {
                    save_deck_to_file(deck, command.arg.str);
                } else {
                    save_deck_to_file(deck, "deck.txt");
                }
                break;
            case LOAD_DECK:
                if (command.has_arg) {
                    read_file_to_deck(deck, &command.arg);
                } else {
                    create_sorted_deck(deck);
                }
                break;
            case TO_PLAY:
                break;
            case TO_STARTUP:
                break;
            case UNKNOWN:
                yukon_error.error = CMD_ERR;

        }
        set_error_message();
        input[0] = '\0';

    }
    return 0;
}


void set_error_message() {
    switch (yukon_error.error) {
        case NO_ERROR:
            strcpy(yukon_error.message, "OK");
            break;
        case MOVE_ERR:
            strcpy(yukon_error.message, "Illegal move");
            break;
        case CMD_ERR:
            strcpy(yukon_error.message, "Illegal command.");
            break;
        case WRITE_ERR:
            strcpy(yukon_error.message, "Could not write deck to file.");
            break;
        case INVALID_DECK:

            strcat(yukon_error.message, " - This is not a valid deck.");
            break;
        default:
            strcpy(yukon_error.message, "Unknown error.");
            break;
    }
}

void debug_game() {
    DoublyLinkedList *deck = create_doubly_linked_list();
    create_sorted_deck(deck);
    save_deck_to_file(deck, "deck.txt");
}

int main() {
//    debug_game();
    run_game();
}
