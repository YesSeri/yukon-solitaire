//
// Created by henrik on 5/5/23.
//

#include <malloc.h>
#include "History.h"
#include "Cli.h"


HistNode *create_history_node(Move *move_ptr) {
    HistNode *node = malloc(sizeof(HistNode));
    node->move_ptr = move_ptr;
    node->next = NULL;
    node->prev = NULL;
    return node;
}


HistoryList *create_history_list() {
    HistoryList *historyList = malloc(sizeof(HistoryList));
    HistNode *dummy_ptr = create_history_node(NULL);
    historyList->current = dummy_ptr;
    historyList->current->next = historyList->current;
    historyList->current->prev = historyList->current;
}


void add_move_to_history(Move *move, HistoryList *historyList) {
    if (historyList->current->next->move_ptr != NULL) {
        // If there is future history when we try to add new history we need to delete it and replace it with new history
        exit(1);
    }
    HistNode *node = create_history_node(move);
    node->next = historyList->current->next;
    historyList->current->next->prev = node;
    historyList->current->next = node;
    node->prev = historyList->current;
    historyList->current = node;
}

void undo_move(DoublyLinkedList **columns_arr, Foundation **foundations_arr) {

}

void redo_move(DoublyLinkedList **columns_arr, Foundation **foundations_arr) {

}
