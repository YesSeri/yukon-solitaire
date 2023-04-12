#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED

#include <stdbool.h>

typedef enum suit {
    CLUB = 'C',
    DIAMOND = 'H',
    HEART = 'D',
    SPADE = 'S'
} Suit;
typedef enum value {
    ACE = 1,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING
} Value;


typedef struct card {
    Suit suit;
    Value value;
    bool is_hidden;
    struct card *next;
} Card;

Card *create_card(Suit, Value, bool);

void get_card_string(Card *, char *);

void print_card(Card *c);

#endif
