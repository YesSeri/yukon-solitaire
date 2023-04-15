//
// Created by henrik on 4/14/23.
//

#include <stdio.h>
#include <string.h>
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

Move *parse_move(char *str, char *from, char *to) {
//    char from[8];
//    char to[8];
    do {
        *from++ = *str++;
    } while (str[0] != '-' && str[1] != '>');

    // Move past delimiter ->
    str = str + 2;

    do {
        *to++ = *str++;
    } while (*str != '\0');
    *from++ = '\0';
    *to++ = '\0';

    return NULL;
}


char *getPlayerInput(char str[], int *len_ptr) {
//    scanf("%s", str);
//    str[0] = 'a';
//    str[1] = 'a';
//    str[2] = '-';
//    str[3] = '>';
//    str[4] = 'b';
//    str[5] = 'b';

    str[0] = 'Q';
    str[1] = 'Q';
    *len_ptr = strlen(str);

}

Command parseInput(char *input, int input_len, void (**actionFn)()) {
// TODO What is max input length?

    if (input_len > 3) {
        char from[8];
        char to[8];
        parse_move(input, from, to);
        *actionFn = &make_player_move;
        return MOVE;
    };
    if (input_len = 2) {
        if (input[0] == 'Q' && input[1] == 'Q') {
            printf("QUIT");
            *actionFn = &quit_game;
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

