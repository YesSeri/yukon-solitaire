//
// Created by henrik on 4/14/23.
//

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "Cli.h"

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

ParsedInputData parse_move(char *input, int input_len, char *from, char *to) {
// Add to from char array until we reach `->`
    int i = 0;
    while (input[0] != '-' && input[1] != '>' && input_len) {
        from[i] = input[i];
        i++;
        input_len--;
    }
    from[i] = '\0';
    // Move past delimiter ->
    i += 2;
    input_len -= 2;

// Add to `to` char array until we reach `\0`, null char.
    while (*input != '\0' && input_len) {
        to[i] = input[i];
        i++;
        input_len--;
    }
    to[i] = '\0';

    Move *move = malloc(sizeof(Move));
    Card *card = NULL;
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
    ParsedInputData parsedInputData;
    Data data;
    data.move = *move;
    parsedInputData.data = data;
    parsedInputData.command = MOVE;
    return parsedInputData;

}


char *get_player_input(char *str, int *len_ptr) {
//    scanf("%s", str);
//    str[0] = 'a';
//    str[1] = 'a';
//    str[2] = '-';
//    str[3] = '>';
//    str[4] = 'b';
//    str[5] = 'b';

    str[0] = 'Q';
    str[1] = 'Q';
    str[3] = '\0';
    *len_ptr = strlen(str);

}

// We return a pointer, pointing to the fn that corresponds to the parsed input.
ParsedInputData *parse_input(char *input, int input_len, ParsedInputData *parsed_data) {
// TODO What is max input length?
    if (input_len > 3) {
        char from[8];
        char to[8];
        parse_move(input, input_len, from, to);
    };
    if (input_len = 2) {
        if (input[0] == 'Q' && input[1] == 'Q') {
            return quit_game;
        }
    };
    if (input[0] == 'S') {

    }
    if (input[0] == 'L') {

    }
    if (input[0] == 'P') {
//        return TO_PLAY;
    }
    if (input[0] == 'Q') {
//        return TO_STARTUP;
    }
//    return ERROR;
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

