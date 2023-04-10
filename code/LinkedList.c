// This includes #define for ace, 1, 2, ... king and for suits heart, club, diamond, spade.
#include "Types.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int Value;
typedef char Suit;

typedef struct card {
    Suit suit;
    Value value;
    struct card* next;
} Card;

// Double pointer so we don't need to assign value when changing value of head in function.
// Card* would mean that when we change value of head pointer, e.g. 0xff to 0xdd, the change would only persist inside the function.
// That is because we are changing the object given to the function not the value it is pointing to.
// Card** deck solves this. When we change what head, Card* head = *deck, points to we can access that outside the function.
//
// In shorter terms:
// If we modify a function pointer that is only valid in the local scope of the function.
// So if we want to modify what a pointer is pointing to, we need to first point at the pointer so we can keep the value outside the function.
//
// I think I understand now, but goddamn it is confusing.
//
// / Henrik
//
void insert_at_head(Card** head_ptr, Card* new_card)
{
    new_card->next = (*head_ptr);
    (*head_ptr) = new_card;
}

void print_linked_list(Card* deck)
{
    Card* current = deck;

    printf("HEAD -> ");
    while (current != NULL) {
        printf("%d -> ", current->value);
        current = current->next;
    }
    printf("\n");
}

Card* create_card(Suit suit, Value v)
{
    Card* c = malloc(sizeof(Card));
    c->value = v;
    c->suit = suit;
    c->next = NULL;
    return c;
}
int main()
{
    Suit suits[] = { CLUB, HEART, DIAMOND, SPADE };

    Card* head = NULL;

    for (int i = 0; i < 4; i++) {
        Suit suit = suits[i];
        for (Value v = ACE; v <= KING; v++) {
            Card* c = create_card(suit, v);
            insert_at_head(&head, c);
        }
    }
    print_linked_list(head);
    return 0;
}