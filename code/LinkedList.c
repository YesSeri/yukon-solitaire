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

void insert_at_head(LinkedList *list, Card *new_card) {
    new_card->next = list->head;
    list->head = new_card;
    list->length++;
}

void append_recursive(Card *current_card_ptr, Card *new_card_ptr) {
    if (current_card_ptr->next == NULL) {
        current_card_ptr->next = new_card_ptr;
    } else {
        append_recursive(current_card_ptr->next, new_card_ptr);
    }

}

void append(LinkedList *list, Card *new_card) {
    Card *last_card = get_card_at_index(list, list->length - 1);
    if (last_card == NULL) {
        list->head = new_card;
    } else {
        last_card->next = new_card;
    }

    list->length++;
//    Card *head = list->head;

//    if (head == NULL) {
//        list->head = new_card;
//    } else {
//        append_recursive(head, new_card);
//    }
}

// Get at index i
// Returns null if index if is bigger than list.
Card *get_card_at_index(LinkedList *list, int i) {
    Card *card_ptr = list->head;
    while (i) {
        if (card_ptr == NULL) {
            return NULL;
        }
        card_ptr = card_ptr->next;
        i--;
    }
    return card_ptr;
}

void debug_print_linked_list(LinkedList *list) {
    Card *current = list->head;

    while (current->next != NULL) {
        printf("%d%c -> ", current->value, current->suit);
        if (current->suit != current->next->suit) {
            printf("\n");
        }

        current = current->next;
    }
    printf("%d%c -> \n", current->value, current->suit);
    printf("length: %d", list->length);
    printf("\n");
}