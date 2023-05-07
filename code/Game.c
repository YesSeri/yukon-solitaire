// This includes #define for ace, 1, 2, ... king and for suits heart, club, diamond, spade.
#include "Game.h"
#include "Tests.h"
#include "History.h"

int col_heights_startup[NUMBER_OF_COLUMNS] = {8, 8, 8, 7, 7, 7, 7};
int col_heights_play[NUMBER_OF_COLUMNS] = {1, 6, 7, 8, 9, 10, 11};

// TODO Biggest thing left is validations of moves to and from columns and foundations, especially from foundation to column.
// TODO Game over check
// TODO go through REQUIREMENTS.md and see what is left to do.

// Global variable. We set this to error if we encounter one, and then we handle error after switch case in main game loop.
// We use this so we can easily set the errors anywhere they occur.
YukonError yukon_error = {NO_ERROR, "OK"};


void free_columns_foundations(DoublyLinkedList **columns_arr, Foundation **foundations_arr) {
    for (int i = 0; i < NUMBER_OF_COLUMNS; i++) {
        free_list_nodes(columns_arr[i]);
    }
    for (int i = 0; i < NUMBER_OF_FOUNDATIONS; i++) {
        free_list_nodes(foundations_arr[i]);
    }
}

void create_columns_from_deck(DoublyLinkedList *deck, DoublyLinkedList *columns_arr[7], int col_heights[7]) {
    // This adds all the cards from the deck to the columns.
    // We create pointers to cards in deck from the linked lists in the columns.
    // The linked lists in the columns and the linked list in the deck share the same cards.
    // Depending on if we are in setup phase or in play phase we use different column heights.

    Node *deck_node_ptr = deck->dummy_ptr->next;
    Node *col_node_ptr;

    for (int height = 0; height < 20; height++) {
        for (int col = 0; col < NUMBER_OF_COLUMNS; col++) {
            if (col_heights[col] - height > 0) {
                col_node_ptr = create_node(deck_node_ptr->card_ptr);
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

bool is_valid_move(Move *move, DoublyLinkedList *from, DoublyLinkedList *to) {

    if (move->is_to_col == move->is_from_col) {
        if (move->from == move->to) {
            return false;
        }
    }

    Card *card_from = NULL;
    Card *card_to = get_node_at(to, 0)->card_ptr;
    if (move->card == NULL) {
        card_from = get_node_at(from, 0)->card_ptr;
        // If card_ptr is empty the dummy ptr points to itself, meaning there are no cards in this column or foundation.
    } else {
        card_from = search_list_for_card(from, move->card)->card_ptr;
    }
    // Move multiple cards
    // You can never move several cards to a column.
    if (move->is_to_col) {
        // Move one card
        // Card must exist in column
        if (card_from == NULL) {
            return false;
        }

        // King can be moved to empty column
        if (card_from->value == KING && card_to == NULL) {
            return true;
        } else if (card_from->value != KING && card_to == NULL) {
            return false;
        }
        // Card must be one lower than the col it is moving to and of a different suit
        if (!(card_from->value == card_to->value - 1 || card_from->suit == card_to->suit)) {
            return false;
        }


    } else if (!move->is_to_col && move->card == NULL) {
        return validate_to_foundation_move(move, from, to);
    }
    return true;
}

// Sets correct visibility for columns in play phase.
// First hide all in deck, then show top card in all columns.
void set_correct_visibility_for_columns(DoublyLinkedList *deck, DoublyLinkedList **columns_arr) {
    set_cards_are_hidden(deck, true);
    columns_arr[0]->dummy_ptr->next->card_ptr->is_hidden = false;
    for (int i = 1; i < NUMBER_OF_COLUMNS; i++) {
        for (int j = 0; j < 5; j++) {
            Card *c = get_card_at(columns_arr[i], j);
            if (c) {
                c->is_hidden = false;
            }
        }
    }

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


bool validate_to_foundation_move(Move *move, DoublyLinkedList *from, DoublyLinkedList *to) {

    Card *from_card = from->dummy_ptr->next->card_ptr;
    Card *to_card = to->dummy_ptr->next->card_ptr;
    // If trying to move several cards at once to foundation it fails.
    if (move->card != NULL) return false;
    // If foundation is empty and card is ace it is a valid move.
    if (to->length == 0) {
        return from_card->value == ACE;
    }
    // If foundation is not empty and card is one higher than top card in foundation and of same suit it is a valid move.
    if (from_card->value - 1 == to_card->value && from_card->suit == to_card->suit) {
        return true;
    }
    return false;
}

void setup_startup_phase_deck(DoublyLinkedList *deck, DoublyLinkedList **columns_arr, Foundation **foundations_arr,
                              Command *command) {

    free_columns_foundations(columns_arr, foundations_arr);
    free_list_cards(deck);
    free_list_nodes(deck);
    if (command->has_arg) {
        read_file_to_deck(deck, command->arg.str);
    } else {
        create_sorted_deck(deck);
    }
    create_columns_from_deck(deck, columns_arr, col_heights_startup);
}

void run_command(Command *command, char *input, DoublyLinkedList *deck, DoublyLinkedList **columns_arr,
                 Foundation **foundations_arr, Phase *phase,
                 char string[67]) {
    switch (command->type) {
        case MOVE: {
            // wrong phase
            if (*phase != PLAY) {
                yukon_error.error = PHASE_ERR;
                return;
            }
            Move *move = parse_move(input);
            move_action(move, columns_arr, foundations_arr);
        }
            break;
        case QUIT:
            printf("Quitting game...");
            exit(0);

        case SHOW_CARDS:
            if (*phase != STARTUP) {
                yukon_error.error = PHASE_ERR;
                return;
            }
            set_cards_are_hidden(deck, false);

            break;
        case SHUFFLE_INTERLEAVED:
            if (*phase != STARTUP) {
                yukon_error.error = PHASE_ERR;
                return;
            }
            int split_size = command->arg.val;
            shuffle_interleaved(deck, split_size);
            free_columns_foundations(columns_arr, foundations_arr);
            create_columns_from_deck(deck, columns_arr, col_heights_startup);

            break;
        case SHUFFLE_RANDOM:
            if (*phase != STARTUP) {
                yukon_error.error = PHASE_ERR;
                return;
            }
            shuffle_random(deck);
            free_columns_foundations(columns_arr, foundations_arr);
            create_columns_from_deck(deck, columns_arr, col_heights_startup);
            break;

        case SAVE_DECK:
            if (*phase != STARTUP) {
                yukon_error.error = PHASE_ERR;
                return;
            }
            if (command->has_arg) {
                save_deck_to_file(deck, command->arg.str);
            } else {
                save_deck_to_file(deck, "deck.txt");
            }
            break;
        case LOAD_DECK: {
            if (*phase != STARTUP) {
                yukon_error.error = PHASE_ERR;
                return;
            }
            setup_startup_phase_deck(deck, columns_arr, foundations_arr, command);
            break;
        }
        case TO_PLAY: {
            if (deck->length != 52) {
                yukon_error.error = INVALID_DECK;
                strcpy(yukon_error.message, "Please pick a deck before starting - ");
                return;
            }
            if (*phase == PLAY) {
                yukon_error.error = PHASE_ERR;
                return;
            }
            strcpy(yukon_error.message, "Play Phase entered - ");
            free_columns_foundations(columns_arr, foundations_arr);
            create_columns_from_deck(deck, columns_arr, col_heights_play);
            set_correct_visibility_for_columns(deck, columns_arr);
            *phase = PLAY;
            break;

        }
        case TO_SETUP:
            if (*phase == STARTUP) {
                yukon_error.error = PHASE_ERR;
                return;
            }
            strcpy(yukon_error.message, "Setup Phase entered - ");
            *phase = STARTUP;
            setup_startup_phase_deck(deck, columns_arr, foundations_arr, command);
            break;
        case UNKNOWN:
        default:
            yukon_error.error = CMD_ERR;

    }
}

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
int run_game() {
    // srand makes sure the random shuffle is always different each time.
    // Without this, the random shuffle always uses the same seed,
    // meaning the shuffling will be exactly the same each time.
    srand(time(NULL));
    DoublyLinkedList *deck = create_doubly_linked_list();
    DoublyLinkedList *columns_arr[NUMBER_OF_COLUMNS];
    Foundation *foundations_arr[NUMBER_OF_FOUNDATIONS];
    initiate_columns_and_foundations(columns_arr, foundations_arr);

    char last_command[2 + ARG_LENGTH + 1] = "";
    Command command;
    Phase phase = STARTUP;
    while (!is_gameover(foundations_arr)) {
        char input[2 + ARG_LENGTH + 1];
        input[0] = '\0';
        print_view(columns_arr, foundations_arr, last_command);
        yukon_error.error = NO_ERROR;
        strcpy(yukon_error.message, "");
        while (strlen(input) == 0) {
            get_player_input(input);
        }
        strcpy(last_command, input);
        parse_input_type(input, &command);
        run_command(&command, input, deck, columns_arr, foundations_arr, &phase, input);
        set_error_message();
    }
    print_view(columns_arr, foundations_arr, last_command);
    return 0;
}


void set_error_message() {
    switch (yukon_error.error) {
        // We use strcat when we have a custom error message in the error enum.
        case NO_ERROR:
            strcat(yukon_error.message, "OK");
            break;
        case MOVE_ERR:
            strcat(yukon_error.message, "Illegal move");
            break;
        case CMD_ERR:
            strcat(yukon_error.message, "Illegal command.");
            break;
        case WRITE_ERR:
            strcat(yukon_error.message, "Could not write deck to file.");
            break;
        case INVALID_DECK:
            // We set the message to a custom error depending on the deck error and append the default message
            strcat(yukon_error.message, "This is not a valid deck.");
            break;
        case READ_ERR:
            strcat(yukon_error.message, "Could not read file.");
            break;
        case PHASE_ERR:
            strcat(yukon_error.message, "You must switch phase for this command.");
            break;
        default:
            strcat(yukon_error.message, "Unknown error.");
            break;
    }
}

void debug_game() {
    srand(time(NULL));

    DoublyLinkedList *deck = create_doubly_linked_list();
    create_sorted_deck(deck);
    DoublyLinkedList *columns_arr[NUMBER_OF_COLUMNS];
    Foundation *foundations_arr[NUMBER_OF_FOUNDATIONS];
    initiate_columns_and_foundations(columns_arr, foundations_arr);
    free_columns_foundations(columns_arr, foundations_arr);
    create_columns_from_deck(deck, columns_arr, col_heights_play);
    set_correct_visibility_for_columns(deck, columns_arr);

    char last_command[2 + ARG_LENGTH + 1] = "";
    Command command;
    Phase phase = PLAY;
//    Historylist *historylist = create_history_list();

    HistNode **currentMoveInHistory;
    HistNode *dummy_ptr = create_history_node(NULL);
    currentMoveInHistory = &dummy_ptr;
    dummy_ptr->next = dummy_ptr;
    dummy_ptr->prev = dummy_ptr;

    char *input[3] = {"C1 -> F3", "C2:7D -> C5", "C7 -> C1"};
    Move *move[3];
    move[0] = parse_move(input[0]);
    move[1] = parse_move(input[1]);
    move[2] = parse_move(input[2]);
    move_action(move[0], columns_arr, foundations_arr);
    add_move_to_history(move[0], currentMoveInHistory);
    undo_move(columns_arr,foundations_arr, currentMoveInHistory);
    redo_move(columns_arr,foundations_arr, currentMoveInHistory);

    for (int i = 0; i < 7; ++i) {
        printf("\n%d - len %d\n", i, columns_arr[i]->length);
        debug_print(columns_arr[i]);
    }
//    printf("\n----------\n");
//    move_action(move[1], columns_arr, foundations_arr);
//    add_move_to_history(move[1], currentMoveInHistory);
//    for (int i = 0; i < 7; ++i) {
//        printf("\n%d - len %d\n", i, columns_arr[i]->length);
//        debug_print(columns_arr[i]);
//    }
//
//    printf("\n----------\n");
//    move_action(move[2], columns_arr, foundations_arr);
//    add_move_to_history(move[2], currentMoveInHistory);
//    undo_move(columns_arr,foundations_arr, currentMoveInHistory);
//
//    for (int i = 0; i < 7; ++i) {
//        printf("\n%d - len %d\n", i, columns_arr[i]->length);
//        debug_print(columns_arr[i]);
//    }
//    char *input = "C1 -> C3";
//    Move *move = parse_move(input);
//    move_action(move, columns_arr, foundations_arr);
//    add_move_to_history(move, historyList);
//
//
    printf("done");
//

}


int main() {
    debug_game();
//    run_tests();
//    run_game();
}

void init_default_deck_and_columns(DoublyLinkedList *deck, DoublyLinkedList **columns_arr, Foundation **foundations_arr,
                                   int *col_heights) {
    create_sorted_deck(deck);
    initiate_columns_and_foundations(columns_arr, foundations_arr);
    create_columns_from_deck(deck, columns_arr, col_heights);
    set_correct_visibility_for_columns(deck, columns_arr);
}
