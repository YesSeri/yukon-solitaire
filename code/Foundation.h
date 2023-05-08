#ifndef LINKED_LIST_H_INCLUDED
#define LINKED_LIST_H_INCLUDED

#include "Card.h"
#include "DoublyLinkedList.h"

typedef DoublyLinkedList Foundation;

Card *peek(Foundation *stack);

Foundation *create_stack();

bool is_gameover(Foundation **);

#endif
