//
// Created by tobia on 17/04/2023.
//

#ifndef YUKON_SOLITAIRE_GAME_H
#define YUKON_SOLITAIRE_GAME_H

#include <stdlib.h>
#include <stdio.h>
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


void initiate_columns_and_foundations(DoublyLinkedList *[7], Foundation *[4]);

bool validate_to_foundation_move(Move *, DoublyLinkedList *, DoublyLinkedList *);

bool validate_from_foundation_move(Move *move, DoublyLinkedList *from, DoublyLinkedList *to);

void set_error_message();

void free_columns_foundations(DoublyLinkedList *[7], Foundation *[4]);

void set_correct_visibility_for_columns(DoublyLinkedList *, DoublyLinkedList *[7]);

bool is_valid_move(Move *, DoublyLinkedList *, DoublyLinkedList *);

void create_columns_from_deck(DoublyLinkedList *, DoublyLinkedList *[7], int [7]);

typedef enum {
    NO_ERROR,
    UNDO_REDO_ERROR,
    MOVE_ERR,
    CMD_ERR,
    WRITE_ERR,
    READ_ERR,
    PHASE_ERR,
    INVALID_DECK,
    GAME_OVER
} ErrorEnum;

typedef struct {
    ErrorEnum error;
    char message[120];
} YukonError;

extern YukonError yukon_error;

#endif //YUKON_SOLITAIRE_GAME_H
