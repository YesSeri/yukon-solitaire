// This includes #define for ace, 1, 2, ... king and for suits heart, club, diamond, spade.
#include "Foundation.h"

// Foundation is a stack. We can only access top element.
// It is only a typedef for DoublyLinkedList.

void push(Foundation *stack, Node *n_ptr) {
    prepend(stack, n_ptr);
}

Card *peek(Foundation *stack) {
    return get_card_at(stack, 0);
}


Foundation *create_stack() {
    return create_doubly_linked_list();
}
