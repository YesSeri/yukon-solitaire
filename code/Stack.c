// This includes #define for ace, 1, 2, ... king and for suits heart, club, diamond, spade.
#include "Stack.h"
#include "Card.h"
#include <stdio.h>
#include <malloc.h>

// Double pointer so we don't need to assign value when changing value of head in function.
// Card* would mean that when we change value of head pointer, e.g. 0xff to 0xdd, the change would only persist inside the function.
// That is because we are changing the object given to the function not the value it is pointing to.
// Card** deck solves this. When we change what head, Card* head = *deck, points to we can access that outside the function.
//
// In shorter terms:
// If we modify a function pointer that is only valid in the local scope of the function.
// So if we want to modify what a pointer is pointing to, we need to first point at the pointer so we can keep the value outside the function.
//
// I think I understand now, but goddamn it is confusing.
//
// / Henrik
//


StackNode *create_stack_node(Card *c_ptr) {
    StackNode *node = malloc(sizeof(StackNode));
    node->card_ptr = c_ptr;
    return node;
}

void push(Stack *stack, Card *c_ptr) {
    StackNode *n = create_stack_node(c_ptr);
    if (stack->head != NULL) {
        n->next = stack->head;
    }
    stack->head = n;
}

// Get at index i
// Returns null if index if is bigger than list.
Card *peek(Stack *stack) {
    return stack->head;
}

bool *is_empty(Stack *stack) {
    return (bool *) (stack->head == NULL);
}

Card *pop(Stack *stack) {
    Card *element = stack->head;
    stack->head = stack->head->next;
}


Stack *create_stack() {
    Stack *dll = malloc(sizeof(Stack));
    dll->head = NULL;
    return dll;
}

/**
 * Moves n cards from one linked list to the other.
 * @param from
 * @param to
 * @param n
 */
//void move_cards(Stack *from, Stack *to, int n) {
//    Card *card_ptr = get_node_at_index(from, n - 1);
//    if (card_ptr == NULL) {
//        return;
//    }
//    Card *next_card_ptr = card_ptr->next;
//    card_ptr->next = NULL;
//    append(to, from->head);
//    from->head = next_card_ptr;
//    from->length -= n;
//    to->length += n;
//}