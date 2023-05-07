//
// Created by henrik on 5/5/23.
//

#ifndef YUKON_SOLITAIRE_HISTORY_H
#define YUKON_SOLITAIRE_HISTORY_H

#include "Cli.h"
#include "DoublyLinkedList.h"
#include "Foundation.h"
#include "Game.h"


typedef struct history_node {
    struct history_node *next;
    struct history_node *prev;
    Move *move_ptr;
} HistNode;

typedef struct {
    HistNode **current;
} HistoryList;


HistNode *create_history_node(Move *);

HistoryList *create_history_list();


void debug_print_history(HistNode **);

void add_move_to_history(Move *, HistNode **);

//void undo_move(DoublyLinkedList **, Foundation **, HistoryList *);
void undo_move(DoublyLinkedList **, Foundation **, HistNode **);

void redo_move(DoublyLinkedList **, Foundation **, HistNode **);

#endif //YUKON_SOLITAIRE_HISTORY_H
