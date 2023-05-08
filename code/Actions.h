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

void save_game_to_file(DoublyLinkedList *, Foundation **, struct history_node **, DoublyLinkedList **, const char *);

void read_file_to_deck(DoublyLinkedList *, const char *);

void shuffle_interleaved(DoublyLinkedList *, int);

void shuffle_random(DoublyLinkedList *);

void move_action(Move *, DoublyLinkedList *[7], DoublyLinkedList *[4], struct history_node**);

#endif
