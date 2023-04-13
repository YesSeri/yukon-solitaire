#ifndef LINKED_LIST_H_INCLUDED
#define LINKED_LIST_H_INCLUDED

#include "Card.h"
#include "DoublyLinkedList.h"

typedef DoublyLinkedList Stack;

void push(Stack *stack, Card *c_ptr);

Card *peek(Stack *stack);

Card *pop(Stack *);

Stack *create_stack();

#endif
