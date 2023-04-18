//
// Created by henrik on 4/14/23.
//

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

void parse_move_into_data_struct(char *from, char *to);

ParsedInputData *parse_move(char *input, int input_len) {
    char from[MAX_LEN_MOVE_FROM] = "";
    char to[MAX_LEN_MOVE_TO] = "";
    // Add to the from char array until we reach `->`
    int i = 0;
    while (!(input[i] == ' ' || input[i] == '-') && i < input_len) {
        from[i] = input[i];
        i++;
    }
    from[i] = '\0';
    // Move past delimiter and spaces " -> "
    i += 4;

    int j = 0;
    // Add to `to` char array until we reach `\0`, null char.
    while (input[i] != '\0' && i < input_len) {
        to[j++] = input[i++];
    }
    to[i] = '\0';

    Move *move = malloc(sizeof(Move));
    Card *card = NULL;
    move->card = card;
    //   FROM C3:4C
    //   TO F2
    move->is_from_col = from[0] == 'C';
    move->from = from[1] - '0';

    if (from[2] == ':') {
        Value v = card_char_to_value(from[3]);
        // TODO error checking;
        Suit s = from[4];
        card = create_card(s, v, false);
        move->card = card;
    }
    ParsedInputData *parsedInputData = malloc(sizeof(ParsedInputData));
    Data data;
    data.move = *move;
    parsedInputData->data = data;
    parsedInputData->command = MOVE;
    return parsedInputData;
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
    scanf("%16s", str);

//    For testing
//    strcpy(str, "C3 -> C2");
//    strcpy(str, "C3:H5 -> C1");
//    strcpy(str, "C3 -> F1");
//    strcpy(str, "QQ");

    *len_ptr = strlen(str);
}

// We return a pointer, pointing to the fn that corresponds to the parsed input.
CommandType parse_input_type(char *input, int input_len) {
    // TODO What is max input length?
    if (input_len > 3) {
//        return parse_move(input, input_len);
        return MOVE;
    };
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

    // If there is no matching command there must be an error.
    return ERROR;
    //    SW
    //    LD
    //    P
    //    Q
    //    MOVE
    //    ERROR
}

void parse_move_into_data_struct(char *from, char *to) {
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