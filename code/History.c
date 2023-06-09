//
// Created by henrik on 5/5/23.
//

#include <malloc.h>
#include <stdlib.h>
#include "History.h"

struct history_node *create_history_node(Move *move_ptr) {
    struct history_node *node = malloc(sizeof(struct history_node));
    node->move_ptr = move_ptr;
    node->next = NULL;
    node->prev = NULL;
    return node;
}


void add_move_to_history(Move *move, struct history_node **current_ptr) {
    struct history_node *current = *current_ptr;
    struct history_node *to_delete = current->next;

    // Delete, and free, from current to last, to delete future history.
    while (to_delete->move_ptr != NULL) {
        free(to_delete->move_ptr->card);
        free(to_delete->move_ptr);
        to_delete->prev->next = to_delete->next;
        to_delete->next->prev = to_delete->prev;
        to_delete = to_delete->next;
//        free(to_delete->prev);
    }
    struct history_node *node = create_history_node(move);
    node->next = current->next;
    node->prev = current;
    node->next->prev = node;
    node->prev->next = node;
    *current_ptr = node;
}

void
undo_move(DoublyLinkedList **columns_arr, Foundation **foundations_arr, struct history_node **currentMoveInHistory) {
    struct history_node *undoHistNode = *currentMoveInHistory;
    if (undoHistNode->move_ptr == NULL) {
        yukon_error.error = UNDO_REDO_ERROR;
        strcpy(yukon_error.message, "Could not undo, since you are at move 0 - ");
    } else {
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
}

void
redo_move(DoublyLinkedList **columns_arr, Foundation **foundations_arr, struct history_node **currentMoveInHistory) {
    struct history_node *undoHistNode = *currentMoveInHistory;
    Move *redoMove = undoHistNode->next->move_ptr;

    if (redoMove == NULL) {
        yukon_error.error = UNDO_REDO_ERROR;
        strcpy(yukon_error.message, "Could not redo, since you are at last move - ");
    } else {
        *currentMoveInHistory = undoHistNode->next;
        DoublyLinkedList *from = redoMove->is_from_col ? columns_arr[redoMove->from] : foundations_arr[redoMove->from];
        DoublyLinkedList *to = redoMove->is_to_col ? columns_arr[redoMove->to] : foundations_arr[redoMove->to];
        if (redoMove->card == NULL) {
            move_single_card(from, to);
        } else {
            move_cards(from, to, redoMove->card);
        }
    }

}

void debug_print_history(struct history_node **currentMoveInHistory) {
    struct history_node *curr_f = *(currentMoveInHistory);
    printf(" curr move: ");
    printf("%d->%d ", curr_f->move_ptr->from, curr_f->move_ptr->to);
    struct history_node *curr_p = curr_f->prev;
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