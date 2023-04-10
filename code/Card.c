#include "Card.h"
#include <stdio.h>
#include <stdlib.h>

Card* create_card(Suit suit, Value v)
{
    Card* c = malloc(sizeof(Card));
    c->value = v;
    c->suit = suit;
    c->next = NULL;
    return c;
}

char card_value_to_char(Value v)
{
    // if (v < 1 || v > 12) {
    //     printf("Illegal conversion value in card_value_to_char: %d", v);
    //     exit(-1);
    // }
    switch (v) {
    case 1:
        return 'A';
    case 10:
        return 'J';
    case 11:
        return 'Q';
    case 12:
        return 'K';
    default:
        return v + '0';
    }
}