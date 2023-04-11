// This includes #define for ace, 1, 2, ... king and for suits heart, club, diamond, spade.
#include "Card.h"
#include "LinkedList.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void create_unsorted_deck(){

    for (int i = 0; i < 4; i++) {
        Suit suit = suits[i];
        for (Value v = ACE; v <= KING; v++) {
            Card* c = create_card(suit, v);
            insert_at_head(&head, c);
        }
    }
}

int main()
{
    Suit suits[] = { CLUB, HEART, DIAMOND, SPADE };

    Card* head = NULL;

    print_linked_list(head);
    return 0;
}