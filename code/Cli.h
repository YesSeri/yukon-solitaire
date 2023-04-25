//
// Created by henrik on 4/12/23.
//

#ifndef CODE_CLI_H
#define CODE_CLI_H
#define ARG_LENGTH 64

#include "Card.h"

// If we have a move, we get move data
// With quit we get no extra data.

enum commandType {
    QUIT,
    MOVE,
    SAVE_DECK,
    LOAD_DECK,
    TO_PLAY,
    TO_STARTUP,
    UNKNOWN,
    // TODO add all commands
};

union argument {
    char str[ARG_LENGTH];
    int val;
};
typedef struct command {
    enum commandType type;
    union argument arg;
} Command;


typedef struct {
    int from;
    bool is_from_col;
    int to;
    bool is_to_col;
    Card *card;
} Move;

Move *parse_move(char *);

void parse_input_type(char *, Command *);

void get_player_input(char *);

int col_index_to_int(char *col_str);

#endif // CODE_CLI_H
