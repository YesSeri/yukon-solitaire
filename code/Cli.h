//
// Created by henrik on 4/12/23.
//

#ifndef CODE_CLI_H
#define CODE_CLI_H

#include "Card.h"

typedef enum command {
    SHOW,
    LOAD,
    QUIT,
    TO_STARTUP,
    TO_PLAY,
    MOVE,
    ERROR
} Command;

typedef struct {
    int from_col;
    Suit from_suit;
    Value from_value;
    int to_col;
    Suit to_suit;
    Value to_value;
} Move;

Move *parse_move(char *);
typedef void (*actionFn)(char*);
Command parseInput(char *input, int input_len, actionFn *inputFn);

char *getPlayerInput(char [], int *);

#endif //CODE_CLI_H
