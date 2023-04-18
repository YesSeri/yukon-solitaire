//
// Created by henrik on 4/14/23.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Cli.h"
#include <malloc.h>
#include <string.h>

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

Move *parse_move(char *str) {
    //TODO Check if parsing is accurate
    Move *move = malloc(sizeof(Move));

    char from_col_or_foundation;
    int from_i;
    char to_col_or_foundation;
    int to_i;

    if (str[2] == ':') {
        move->card = malloc(sizeof(Card));
        sscanf(str, "%c%d:%d%c -> %c%d",
               &from_col_or_foundation,
               &from_i,
               &move->card->value,
               &move->card->suit,
               &to_col_or_foundation,
               &to_i);
    } else {
        move->card = NULL;

        sscanf(str, "%c%d -> %c%d",
               &from_col_or_foundation,
               &from_i,
               &to_col_or_foundation,
               &to_i);
    }
    move->is_from_col = from_col_or_foundation == 'C';
    move->from = from_i - 1;
    move->is_to_col = to_col_or_foundation == 'C';
    move->to = to_i - 1;
    return move;
}

int col_index_to_int(char *col_str) {
    char col = col_str[0];
    char col_index = col_str[1];
    if (col == 'C') {
        return col_index - '0';
    } else if (col == 'F') {
        return col_index - '0' + 7;
    } else {
        return -1;
    }
}

void get_player_input(char *str, int *len_ptr) {
//     TODO USE THIS IN FINAL PRODUCT
//    scanf("%s", str);

//    For testing
//    strcpy(str, "C3 -> C2");
    strcpy(str, "C3:7H -> C1");
//    strcpy(str, "C3 -> F1");
//    strcpy(str, "QQ");

    *len_ptr = strlen(str);
}

// We return a pointer, pointing to the fn that corresponds to the parsed input.
CommandType parse_input_type(char *input, int input_len) {
    // TODO What is max input length?
    if (input_len == 2) {
        if (input[0] == 'Q' && input[1] == 'Q') {
            return QUIT;
//            parsed_data->commandType = QUIT;
        }
    };
    if (input[0] == 'S' && input[1] == 'W') {
        return SAVE_DECK;
    }
    if (input[0] == 'L' && input[1] == 'W') {
        return LOAD_DECK;
    }
    if (input[0] == 'P') {
        return TO_PLAY;
    }
    if (input[0] == 'Q') {
        return TO_STARTUP;
    }

    if (input_len > 3) {
//        return parse_move(input, input_len);
        return MOVE;
    };

    // If there is no matching command there must be an error.
    return ERROR;
    //    SW
    //    LD
    //    P
    //    Q
    //    MOVE
    //    ERROR
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
