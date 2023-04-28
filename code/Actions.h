#ifndef ACTIONS_H_INCLUDED
#define ACTIONS_H_INCLUDED

#include "Cli.h"
#include "DoublyLinkedList.h"
#include "Foundation.h"
#include "Game.h"
#include <stdio.h>

// Card is null if there is none.
//
// from and to explanation

// is_from_col is true if we are moving from column, else we are moving from foundation


void quit_game();

typedef enum phase {
    Setup,
    Play,
} Phase;

void read_file_to_deck(DoublyLinkedList *, const char *);

void shuffle_interleaved(DoublyLinkedList *, int);

void shuffle_random(DoublyLinkedList *);

#endif
