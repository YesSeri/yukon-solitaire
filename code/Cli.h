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
    int is_from_col;
    int to;
    Card *card;
} Move;
typedef union data {
    Move move;
    int argument;
    char filename[32];
} Data;

typedef struct {
    union data data;
    enum commandType command;
} ParsedInputData;

ParsedInputData *parse_move(char *, int);

CommandType parse_input_type(char *, int);

void get_player_input(char *, int *);

int col_index_to_int(char *col_str);

#endif // CODE_CLI_H
