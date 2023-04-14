#ifndef LINKED_LIST_H_INCLUDED
#define LINKED_LIST_H_INCLUDED

#include "Card.h"
#include "DoublyLinkedList.h"

typedef DoublyLinkedList Foundation;

void push(Foundation *, Node *);

Card *peek(Foundation *stack);

Card *pop(Foundation *);

Foundation *create_stack();

#endif
