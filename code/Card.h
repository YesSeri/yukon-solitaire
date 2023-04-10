#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED

#define CLUB 'C'
#define HEART 'H'
#define DIAMOND 'D'
#define SPADE 'S'
#define ACE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define FIVE 5
#define SIX 6
#define SEVEN 7
#define EIGHT 8
#define NINE 9
#define TEN 10
#define JACK 11
#define QUEEN 12
#define KING 13

typedef int Value;
typedef char Suit;

typedef struct card {
    Suit suit;
    Value value;
    struct card* next;
} Card;

Card* create_card(Suit suit, Value v);

#endif
