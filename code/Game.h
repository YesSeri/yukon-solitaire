//
// Created by tobia on 17/04/2023.
//

#ifndef YUKON_SOLITAIRE_GAME_H
#define YUKON_SOLITAIRE_GAME_H

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "DoublyLinkedList.h"
#include "Card.h"
#include "View.h"
#include "DoublyLinkedList.h"
#include "Foundation.h"
#include "Cli.h"
#include "Game.h"
#include "Actions.h"

void initiate_columns_and_foundations(DoublyLinkedList **, Foundation **);

void show_action(char *input);

void load_action(char *input);

void quit_action(char *input);

void to_startup_action(char *input);

void to_play_action(char *input);

void move_action(Move *, DoublyLinkedList *, DoublyLinkedList *);

void error_action(char *input);

bool validate_to_foundation_move(Move *, DoublyLinkedList *, DoublyLinkedList *);

bool validate_from_foundation_move(Move *move, DoublyLinkedList *from, DoublyLinkedList *to);

void set_error_message();

void free_columns_foundations(DoublyLinkedList *[7], Foundation *[4]);

void set_correct_visibility_for_columns(DoublyLinkedList *, DoublyLinkedList **);

bool is_valid_move(Move *, DoublyLinkedList *, DoublyLinkedList *);


typedef enum {
    NO_ERROR,
    MOVE_ERR,
    CMD_ERR,
    WRITE_ERR,
    READ_ERR,
    PHASE_ERR,
    INVALID_DECK,
} ErrorEnum;

typedef struct {
    ErrorEnum error;
    char message[120];
} YukonError;

extern YukonError yukon_error;
#endif //YUKON_SOLITAIRE_GAME_H
