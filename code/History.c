//
// Created by henrik on 5/5/23.
//

#include <malloc.h>
#include <stdlib.h>
#include "History.h"

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
    historyList->current = &dummy_ptr;
    dummy_ptr->next = dummy_ptr;
    dummy_ptr->prev = dummy_ptr;
}


void add_move_to_history(Move *move, HistNode **current_ptr) {
    HistNode *current = *current_ptr;
    if (current->next->move_ptr != NULL) {
        // If there is future history when we try to add new history we need to delete it and replace it with new history
        exit(1);
    }
    HistNode *node = create_history_node(move);
    node->next = current->next;
    node->prev = current;
    node->next->prev = node;
    node->prev->next = node;
    *current_ptr = node;
}

void undo_move(DoublyLinkedList **columns_arr, Foundation **foundations_arr, HistNode **currentMoveInHistory) {
    HistNode *undoHistNode = *currentMoveInHistory;
    if (undoHistNode->move_ptr == NULL) {
        yukon_error.error = UNDO_REDO_ERROR;
        strcpy(yukon_error.message, "Could not undo, since you are at move 0 - ");
    }
    Move *undoMove = undoHistNode->move_ptr;
    *currentMoveInHistory = undoHistNode->prev;


    DoublyLinkedList *to = undoMove->is_from_col ? columns_arr[undoMove->from] : foundations_arr[undoMove->from];
    DoublyLinkedList *from = undoMove->is_to_col ? columns_arr[undoMove->to] : foundations_arr[undoMove->to];
    if (undoMove->card == NULL) {
        move_single_card(from, to);
    } else {
        move_cards(from, to, undoMove->card);
    }
}

void redo_move(DoublyLinkedList **columns_arr, Foundation **foundations_arr, HistNode **currentMoveInHistory) {
    HistNode *undoHistNode = *currentMoveInHistory;
    Move *redoMove = undoHistNode->next->move_ptr;

    if (redoMove == NULL) {
        yukon_error.error = UNDO_REDO_ERROR;
        strcpy(yukon_error.message, "Could not redo, since you are at last move - ");
    }

    *currentMoveInHistory = undoHistNode->next;


    DoublyLinkedList *from = redoMove->is_from_col ? columns_arr[redoMove->from] : foundations_arr[redoMove->from];
    DoublyLinkedList *to = redoMove->is_to_col ? columns_arr[redoMove->to] : foundations_arr[redoMove->to];
    if (redoMove->card == NULL) {
        move_single_card(from, to);
    } else {
        move_cards(from, to, redoMove->card);
    }

}

void debug_print_history(HistNode **currentMoveInHistory) {
    HistNode *curr_f = *(currentMoveInHistory);
    printf(" curr move: ");
    printf("%d->%d ", curr_f->move_ptr->from, curr_f->move_ptr->to);
    HistNode *curr_p = curr_f->prev;
    curr_f = curr_f->next;
    printf("\nredo moves: ");
    while (curr_f->move_ptr != NULL) {
        printf("%d->%d ", curr_f->move_ptr->from, curr_f->move_ptr->to);
        curr_f = curr_f->next;
    }
    printf("\nundo moves: ");
    while (curr_p->move_ptr != NULL) {
        printf("%d->%d ", curr_p->move_ptr->from, curr_p->move_ptr->to);
        curr_p = curr_p->prev;
    }
    printf("\n");
    fflush(stdout);
}
