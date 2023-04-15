//
// Created by henrik on 4/12/23.
//

#ifndef CODE_CLI_H
#define CODE_CLI_H

#include "Card.h"
#include "Actions.h"

// If we have a move, we get move data
// With quit we get no extra data.
enum data_type {
    NO_EXTRA_DATA,
    MOVE,
    ERROR,
    NUMBER,
    FILENAME,
    LOAD,
    QUIT,
    TO_STARTUP,
    TO_PLAY,
};

union data {
    Move move;
    int argument;
    char filename[32];
};

typedef struct {
    union data data;
    enum data_type type;
} ParsedData;

// Columns, foundations, deck.
typedef void (*fn_ptr)(ParsedData *, DoublyLinkedList *[], Foundation *[], DoublyLinkedList *);

Move *parse_move(char *, int input_len, char *, char *);

fn_ptr parseInput(char *input, int input_len, ParsedData *parsed_data);

char *getPlayerInput(char [], int *);

#endif //CODE_CLI_H
