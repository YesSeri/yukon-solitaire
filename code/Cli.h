//
// Created by henrik on 4/12/23.
//

#ifndef CODE_CLI_H
#define CODE_CLI_H

#include "Card.h"
#include "Actions.h"

// If we have a move, we get move data
// With quit we get no extra data.
enum command {
    QUIT,
    MOVE,
    SAVE,
    LOAD
};

typedef union data {
    Move move;
    int argument;
    char filename[32];
} Data;

typedef struct {
    union data data;
    enum command command;
} ParsedInputData;

// Columns, foundations, deck.
typedef void (*fn_ptr)(ParsedInputData *, DoublyLinkedList *[], Foundation *[], DoublyLinkedList *);

ParsedInputData parse_move(char *, int, char *, char *);

ParsedInputData *parse_input(char *, int, ParsedInputData *);

char *get_player_input(char *, int *);

#endif //CODE_CLI_H
