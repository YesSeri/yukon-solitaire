// This includes #define for ace, 1, 2, ... king and for suits heart, club, diamond, spade.
#include "LinkedList.h"
#include "Card.h"
#include <stdio.h>

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

    printf("HEAD -> \n");
    while (current->next != NULL) {
        printf("%d%c -> ", current->value, current->suit);
        if (current->suit != current->next->suit) {
            printf("\n");
        }

        current = current->next;
    }
    printf("%d%c -> ", current->value, current->suit);
    printf("\n");
}
