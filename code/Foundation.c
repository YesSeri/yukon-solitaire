#include "Foundation.h"

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
