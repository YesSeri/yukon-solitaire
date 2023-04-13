#ifndef LINKED_LIST_H_INCLUDED
#define LINKED_LIST_H_INCLUDED

#include "Card.h"

typedef struct stack_node {
    struct stack_node *next;
    Card *card_ptr;
} StackNode;


typedef struct {
    StackNode *head;
} Stack;

void push(Stack *stack, Card *c_ptr);

Card *peek(Stack *stack);

Card *pop(Stack *);

Stack *create_stack();

#endif
