#ifndef ACTIONS_H_INCLUDED
#define ACTIONS_H_INCLUDED


// Card is null if there is none.
//
// from and to explanation

// is_from_col is true if we are moving from column, else we are moving from foundation


#include "History.h"

void quit_game();

typedef enum phase {
    STARTUP,
    PLAY,
} Phase;

void save_deck_to_file(DoublyLinkedList *, const char *);

void save_state(DoublyLinkedList *, DoublyLinkedList **, DoublyLinkedList **, const char *);

void load_state(DoublyLinkedList *, DoublyLinkedList **, DoublyLinkedList **, const char *);

void load_deck_file(DoublyLinkedList *deck, const char *filename);

void shuffle_interleaved(DoublyLinkedList *, int);

void shuffle_random(DoublyLinkedList *);

void move_action(Move *, DoublyLinkedList *[7], DoublyLinkedList *[4], struct history_node **);

void to_play_phase(DoublyLinkedList *[7], Foundation *[4], DoublyLinkedList *, Phase *);

#endif
