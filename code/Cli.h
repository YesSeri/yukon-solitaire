//
// Created by henrik on 4/12/23.
//

#ifndef CODE_CLI_H
#define CODE_CLI_H

#include "Card.h"

// If we have a move, we get move data
// With quit we get no extra data.

typedef enum commandType {
    QUIT,
    MOVE,
    SAVE_DECK,
    LOAD_DECK,
    TO_PLAY,
    TO_STARTUP,
    ERROR,
    // TODO add all commands
} CommandType;

typedef struct {
    int from;
    bool is_from_col;
    int to;
    bool is_to_col;
    Card *card;
} Move;

Move *parse_move(char *);

CommandType parse_input_type(char *, int);

void get_player_input(char *, int *);

int col_index_to_int(char *col_str);

#endif // CODE_CLI_H
