#include "Card.h"
#include <stdio.h>
#include <stdlib.h>

Card *create_card(Suit suit, Value v, bool is_hidden) {
    Card *c = malloc(sizeof(Card));
    c->value = v;
    c->suit = suit;
    c->is_hidden = is_hidden;
    c->next = NULL;
    return c;
}

char card_value_to_char(Card *c) {
    switch (c->value) {
        case ACE:
            return 'A';
        case TEN:
            return 'T';
        case JACK:
            return 'J';
        case QUEEN:
            return 'Q';
        case KING:
            return 'K';
        default:
            return c->value + '0';
    }
}

void print_card(Card *c) {
    if (c == NULL) {
        printf("NULL\t");
        return;
    }
    char c_val = card_value_to_char(c);
    if (c->is_hidden) {
        printf("[]\t");
    } else {
        printf("%c%c\t", c_val, c->suit);
    }
}
