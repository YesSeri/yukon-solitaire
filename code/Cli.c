//
// Created by henrik on 4/14/23.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Cli.h"

#define MAX_LEN_MOVE_FROM 6
#define MAX_LEN_MOVE_TO 3

//**ALl phases**
//
//| key  | result |
//|------|--------|
//| `QQ` | Quit   |
//
//**Startup**
//
//| key  | result              |
//|------|---------------------|
//| `LD` | load data           |
//| `SW` | show cards          |
//| `SI` | shuffle interleaved |
//| `SR` | shuffle random      |
//| `SD` | save data           |
//| `P`  | to play phase       |
//

//
// from can be either only column C3 or column plus card C3:4C, 4C=Four of Clubs
//
// If suit and/or value is -1, that means no suit/value was given, only column

//<from> -> <to>

/**
 * @brief Parses the user input and returns a move.
 *
 * A move is on the form <from>(:<value><suit) -> <to>.
 * The part in the parenthesis is optional, and used if the player wants to move multiple cards.
 *
 * @param user_input user input in move form. Example: C3 -> F1 or C3:4C -> C5
 * @return the move that the player has made.
 */
Move *parse_move(char *user_input) {
    //TODO Check if parsing is accurate, and make more error proof.

    Move *move = malloc(sizeof(Move));

    char from_col_or_foundation;
    int from_i;
    char to_col_or_foundation;
    int to_i;
    char value_c;
    char suit_c;

    // If the third char is a colon, then we have a move on the form C3:4C -> C5
    if (user_input[2] == ':') {
        move->card = malloc(sizeof(Card));
        sscanf(user_input, "%c%d:%c%c -> %c%d",
               &from_col_or_foundation,
               &from_i,
               &value_c,
               &suit_c,
               &to_col_or_foundation,
               &to_i);
    } else {
        move->card = NULL;

        sscanf(user_input, "%c%d -> %c%d",
               &from_col_or_foundation,
               &from_i,
               &to_col_or_foundation,
               &to_i);

    }
//    if (value_c != 0) {
    if (move->card != NULL) {
        move->card->value = card_char_to_value(value_c);
        move->card->suit = suit_c;
    }
    move->is_from_col = from_col_or_foundation == 'C';
    move->from = from_i - 1;
    move->is_to_col = to_col_or_foundation == 'C';
    move->to = to_i - 1;
    return move;
}

void get_player_input(char *str) {
//    HOW TO INPUT
//    Input have to include spaces. C6->C3 wont work...
//    C6 -> C3 works and with the new input method, it reads spaces also

    fgets(str, 2 + ARG_LENGTH - 1, stdin); // 20 = max length (change to the right max length)
    char *newline = strchr(str, '\n');
    if (newline != NULL) {
        *newline = '\0';
    }

}

void read_string_arg_or_default(char *input, Command *command) {
    if (strlen(input) > 3) {
        char c[15];
        command->has_arg = true;
        sscanf(input, "%s %s", &(*c), &(*command->arg.str));
    } else {
        strcpy(command->arg.str, "default arg");
    }
}

void parse_input_type(char *input, Command *command) {
    // TODO What is max input length?
    command->has_arg = false;
    if (input[0] == 'C' || input[0] == 'F') {
        command->type = MOVE;
    } else if (input[0] == 'Q' && input[1] == 'Q') {
        command->type = QUIT;
    } else if (input[0] == 'S' && input[1] == 'W') {
        command->type = SHOW_CARDS;
    } else if (input[0] == 'S' && input[1] == 'D') {
        read_string_arg_or_default(input, command);
        command->type = SAVE_DECK;
    } else if (input[0] == 'L' && input[1] == 'D') {
        read_string_arg_or_default(input, command);
        command->type = LOAD_DECK;
    } else if (input[0] == 'P') {
        command->type = TO_PLAY;
    } else if (input[0] == 'S' && input[1] == 'I') {
        command->has_arg = true;
        sscanf(input, "%*s %d", &(command->arg.val));
        command->type = SHUFFLE_INTERLEAVED;
    } else if (input[0] == 'S' && input[1] == 'R') {
        command->type = SHUFFLE_RANDOM;
    } else if (input[0] == 'Q') {
        command->type = TO_SETUP;
    } else if (input[0] == 'R') {
        command->type = REDO;
    } else if (input[0] == 'U') {
        command->type = UNDO;
    } else if (input[0] == 'S') {
        read_string_arg_or_default(input, command);
        command->type = SAVE_STATE;
    } else if (input[0] == 'L') {
        read_string_arg_or_default(input, command);
        command->type = LOAD_STATE;
    } else {
        command->type = UNKNOWN;
    }
}



//**Play**
//
//| key              | result           |
//|------------------|------------------|
//| `Q`              | to startup phase |
//| `<from> -> <to>` | make move        |

//| `QQ` | Quit   |

//| `Q`              | to startup phase |
//| `<from> -> <to>` | make move        |

//| `LD` | load data           |
//| `SW` | show cards          |
//| `SI` | shuffle interleaved |
//| `SR` | shuffle random      |
//| `SD` | save data           |
//| `P`  | to play phase       |
