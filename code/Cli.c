//
// Created by henrik on 4/14/23.
//

#include <stdio.h>
#include <string.h>

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
typedef enum command {
    SHOW,
    LOAD,
    QUIT,
    TO_STARTUP,
    TO_PLAY,
    MOVE,
    ERROR
} Command;

typedef enum phase {
    Setup,
    Play,
} Phase;
//typedef struct {
//
//} CliState;



Command promptPlayer() {
//    void (*fun_ptr)(int) = &fun;

// TODO What is max input length?
    char input[16] = "P";
    scanf("%s", input);
    int input_len = strlen(input);

    if (input_len > 3) {
        printf("MOVE");
        parse_move();
        return MOVE;
    };
    if (input_len > 2) {
        if (input[0] == 'Q' && input[1] == 'Q') {
            printf("QUIT");
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

typedef struct {
    int to;
    int from;
} Move;

Move *parse_move(char *str) {

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