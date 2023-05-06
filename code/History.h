//
// Created by henrik on 5/5/23.
//

#ifndef YUKON_SOLITAIRE_HISTORY_H
#define YUKON_SOLITAIRE_HISTORY_H

#include "Cli.h"

typedef struct history_node {
    struct history_node *next;
    struct history_node *prev;
    Move *move_ptr;
} HistNode;

typedef struct {
    HistNode *current;
} HistoryList;


HistNode *create_history_node(Move *);

HistoryList *create_history_list();

void add_move_to_history(Move *move, HistoryList *historyList);

#endif //YUKON_SOLITAIRE_HISTORY_H
