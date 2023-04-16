#include "Card.h"
#include <stdlib.h>
#include <string.h>

Card* create_card(Suit suit, Value v, bool is_hidden)
{
    Card* c = malloc(sizeof(Card));
    c->value = v;
    c->suit = suit;
    c->is_hidden = is_hidden;
    return c;
}

char card_value_to_char(Card* c)
{
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

char suit_from_char(char c)
{
    switch (c) {
    case ACE:
        return 'C';
    case TEN:
        return 'T';
    case JACK:
        return 'J';
    case QUEEN:
        return 'Q';
    case KING:
        return 'K';
    default:
        return c - '0';
    }
}
Value card_char_to_value(char c)
{
    switch (c) {
    case 'A':
        return ACE;
    case 'T':
        return TEN;
    case 'J':
        return JACK;
    case 'Q':
        return QUEEN;
    case 'K':
        return KING;
    default:
        return c - '0';
    }
}

void get_card_string(Card* c, char* str)
{
    if (c == NULL || c->is_hidden) {
        strcpy(str, "[]");
        return;
    } else {
        char c_val = card_value_to_char(c);
        str[0] = c_val;
        str[1] = c->suit;
        str[2] = '\0';
        return;
    }
}
