// This includes #define for ace, 1, 2, ... king and for suits heart, club, diamond, spade.
#include "Foundation.h"
#include "Card.h"
#include "DoublyLinkedList.h"
#include <stdio.h>
#include <malloc.h>


// Foundation is a stack. We can only access top element.
// It is only a typedef for DoublyLinkedList.

void push(Stack *stack, Card *c_ptr) {
    prepend(stack, c_ptr);
}

Card *peek(Stack *stack) {
    return get_card_at(stack, 0);
}


Stack *create_stack() {

}
