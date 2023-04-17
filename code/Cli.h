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
    int to;
    int from_col;
    Suit suit;
    Value value;
} Move;

Move *parse_move(char *, char *, char *);

typedef void (*actionFn)(char*);

actionFn parseInput(char *input, int input_len);

char *getPlayerInput(char [], int *);

#endif //CODE_CLI_H
