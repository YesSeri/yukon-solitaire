// This includes #define for ace, 1, 2, ... king and for suits heart, club, diamond, spade.
#include "Foundation.h"

// Foundation is a stack. We can only access top element.
// It is only a typedef for DoublyLinkedList.

Card *peek(Foundation *stack) {
    return get_card_at(stack, 0);
}


Foundation *create_stack() {
    return create_doubly_linked_list();
}

bool is_gameover(Foundation **foundation_arr) {
    for (int i = 0; i < 4; ++i) {
        if (foundation_arr[i]->length != 13) {
            return false;
        }
    }
    return true;
}
