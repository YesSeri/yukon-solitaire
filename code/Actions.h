#ifndef ACTIONS_H_INCLUDED
#define ACTIONS_H_INCLUDED

#include "Cli.h"
#include "DoublyLinkedList.h"
#include "Foundation.h"
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

DoublyLinkedList *shuffle_interleaved(DoublyLinkedList *, int);

void shuffle_random(DoublyLinkedList *);

#endif
