#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED

typedef struct card {
    Suit suit;
    Value value;
    struct card* next;
} Card;

#endif
