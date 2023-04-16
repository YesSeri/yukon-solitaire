#ifndef ACTIONS_H_INCLUDED
#define ACTIONS_H_INCLUDED

#include <stdio.h>
#include "DoublyLinkedList.h"
#include "Foundation.h"
#include "Cli.h"

// Card is null if there is none.
//
// from and to explanation

// is_from_col is true if we are moving from column, else we are moving from foundation
typedef struct {
    int from;
    int is_from_col;
    int to;
    Card *card;
} Move;

void
make_player_move(ParsedInputData *parsedData, DoublyLinkedList *column_arr[7], Foundation *f_arr[7],
                 DoublyLinkedList *);

void quit_game();

typedef enum phase {
    Setup,
    Play,
} Phase;

#endif
