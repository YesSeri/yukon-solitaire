//
// Created by henrik on 4/14/23.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

void make_player_move() {
    printf("PLAYER MAKING MOVE");
}

void quit_game() {
    printf("Quitting game");
}

typedef enum phase {
    Setup,
    Play,
} Phase;

//
// from can be either only column C3 or column plus card C3:4C, 4C=Four of Clubs
//
// If suit and/or value is -1, that means no suit/value was given, only column

//<from> -> <to>

Move *parse_move(char *str) {
    //TODO Check if parsing is accurate
    Move *move = (Move *)malloc(sizeof(Move));
    sscanf(str, "C%d:%c%d->C%d:%c%d",
           &move->from_col,
           (char *)&move->from_suit,
           (int *)&move->from_value,
           &move->to_col,
           (char *)&move->to_suit,
           (int *)&move->to_value);

    return move;
}



char *getPlayerInput(char str[], int *len_ptr) {
    scanf("%s", str);
//    str[0] = 'a';
//    str[1] = 'a';
//    str[2] = '-';
//    str[3] = '>';
//    str[4] = 'b';
//    str[5] = 'b';

//    str[0] = 'Q';
  //  str[1] = 'Q';
    *len_ptr = strlen(str);

}

Command parseInput(char *input, int input_len, actionFn *printFn) {
// TODO What is max input length?

    if (input_len > 3) {
        char from[8];
        char to[8];
        parse_move(input, from, to);
        *printFn = &make_player_move;
        return MOVE;
    };
    if (input_len == 2) {
        if (input[0] == 'Q' && input[1] == 'Q') {
            printf("QUIT");
            *printFn = &quit_game;
            return QUIT;
        }
    };
    if (input[0] == 'S') {

    }
    if (input[0] == 'L') {

    }
    if (input[0] == 'P') {
        return TO_PLAY;
    }
    if (input[0] == 'Q') {
        return TO_STARTUP;
    }
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

