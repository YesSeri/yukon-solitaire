//
// Created by henrik on 5/5/23.
//

#ifndef YUKON_SOLITAIRE_HISTORY_H
#define YUKON_SOLITAIRE_HISTORY_H

#include "Cli.h"
#include "DoublyLinkedList.h"
#include "Foundation.h"
#include "Game.h"


/**
 * We have a pointer to a history_node pointer to see where we are in the history currently
 * When redoing a move we just move pointer one forward and move cards correspondingly on the board.
 * Same is done with undo.
 * When we add_move_to_history we first must check if there is redo history.
 * If there is redo_history, we first delete the redo history and then we add the move to history and move our .
 */

typedef struct history_node {
    struct history_node *next;
    struct history_node *prev;
    Move *move_ptr;
} HistNode;

HistNode *create_history_node(Move *);

void debug_print_history(HistNode **);

void add_move_to_history(Move *, HistNode **);

//void undo_move(DoublyLinkedList **, Foundation **, HistoryList *);
void undo_move(DoublyLinkedList **, Foundation **, HistNode **);

void redo_move(DoublyLinkedList **, Foundation **, HistNode **);

#endif //YUKON_SOLITAIRE_HISTORY_H
