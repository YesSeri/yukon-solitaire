#ifndef ACTIONS_H_INCLUDED
#define ACTIONS_H_INCLUDED

#include <stdio.h>
#include "DoublyLinkedList.h"
#include "Foundation.h"
#include "Cli.h"

// Card is null if there is none.
//
// from and to explanation
// 0 = col_1
// 1 = col_2
// ...
// 6 = col_7
// 7 = foundation_1
// ...
// 10 = foundation_10

typedef struct {
    int from;
    int to;
    Card *card;
} Move;

void make_player_move(ParsedData *parsedData, DoublyLinkedList *column_arr[7], Foundation *f_arr[7], DoublyLinkedList *);

void quit_game();

typedef enum phase {
    Setup,
    Play,
} Phase;

#endif
