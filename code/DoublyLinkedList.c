//
// Created by henrik on 4/12/23.
//

#include "DoublyLinkedList.h"
#include <stdlib.h>
#include <stdio.h>

void debug_print(DoublyLinkedList *dll) {
    Node *curr = dll->dummy_ptr->next;
    int i = 0;
    while (curr->card_ptr != NULL) {
        i++;
        printf("%2d%c", curr->card_ptr->value, curr->card_ptr->suit);
        curr = curr->next;
        if (i % 13 == 0) {
            printf("\n");
        } else {

            printf(", ");
        }
    }
    fflush(stdout);
}


void free_list_cards(DoublyLinkedList *dll) {
    Node *current = dll->dummy_ptr->next;
    while (current->card_ptr != NULL) {
        free(current->card_ptr);
        current = current->next;
    }
}

void free_list_nodes(DoublyLinkedList *dll) {
    Node *current = dll->dummy_ptr->next;
    while (current->card_ptr != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    dll->dummy_ptr->next = dll->dummy_ptr;
    dll->dummy_ptr->prev = dll->dummy_ptr;
    dll->length = 0;
}


void set_cards_are_hidden(DoublyLinkedList *dll, bool is_hidden) {
    Node *current = dll->dummy_ptr->next;
    while (current->card_ptr != NULL) {
        current->card_ptr->is_hidden = is_hidden;
        current = current->next;
    }
}

Node *create_node(Card *c_ptr) {
    Node *node = malloc(sizeof(Node));
    node->card_ptr = c_ptr;
    node->next = NULL;
    node->prev = NULL;
    return node;
}


/**
 * PRIVATE FUNCTION. Use move cards instead. This function does not, and SHOULD not free the pointer.
 * That is  done in move_cards.
 *
 * @param dll
 * @param c_ptr
 * @return
 */
Node *search_list_for_card(DoublyLinkedList *dll, Card *c_ptr) {
    Node *current = dll->dummy_ptr->next;
    // When we encounter a hidden card, or reach end of column, we stop searching.
    while (current != dll->dummy_ptr && !current->card_ptr->is_hidden) {
        if (current->card_ptr->suit == c_ptr->suit && current->card_ptr->value == c_ptr->value) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

Node *get_node_at(DoublyLinkedList *dll, int index) {
    Node *current = dll->dummy_ptr->next;
    while (index--) {
        current = current->next;
        if (current == dll->dummy_ptr) {
            printf("Index out of bounds in fn get_node_at. Index: %d, list length-1: %d", index, dll->length - 1);
            return NULL;
        }
    }
    return current;
}

Card *get_card_at(DoublyLinkedList *dll, int index) {
    return get_node_at(dll, index)->card_ptr;
}

void insert_node_between_these_two_nodes(Node *n_before, Node *n_after, Node *n) {
    n_before->next = n;
    n->prev = n_before;
    n->next = n_after;
    n_after->prev = n;
}

// Deletes node at index
void delete_node_at(DoublyLinkedList *dll, int i) {
    Node *n = get_node_at(dll, i);
    n->prev->next = n->next;
    n->next->prev = n->prev;
    dll->length--;
}

/**
 * insert at end of deck.
 * @param dll
 * @param n_ptr
 */
void append(DoublyLinkedList *dll, Node *n_ptr) {
    Node *dummy = dll->dummy_ptr;
    Node *last = dummy->prev;

    insert_node_between_these_two_nodes(last, dummy, n_ptr);

    Node *array[52] = {NULL};
    dll->length++;
}

// A general observation. Pointers vs pointer to pointers, when prepending.
//
// Double pointer so we don't need to assign value when changing value of head in function.
// Node* would mean that when we change value of head pointer, e.g. 0xff to 0xdd, the change would only persist inside the function.
// That is because we are changing the object given to the function not the value it is pointing to.
// Card** deck solves this. When we change what head, Card* head = *deck, points to we can access that outside the function.
//
// In shorter terms:
// If we modify a function pointer that is only valid in the local scope of the function.
// So if we want to modify what a pointer is pointing to, we need to first point at the pointer so we can keep the value outside the function.
//
// I think I understand now, but goddamn it is confusing.
//
// I solved this with a dummy node when making doubly linked list
//
// / Henrik
//

void prepend(DoublyLinkedList *dll, Node *n_ptr) {
    Node *dummy = dll->dummy_ptr;
    Node *first = dummy->next;
    insert_node_between_these_two_nodes(dummy, first, n_ptr);
    dll->length++;
}


void create_sorted_deck(DoublyLinkedList *dll) {
    Suit suits[] = {CLUB, DIAMOND, HEART, SPADE};
    for (int i = 0; i < 4; i++) {
        Suit suit = suits[i];
        for (Value v = ACE; v <= KING; v++) {
            Card *c = create_card(suit, v, true);
            Node *n = create_node(c);

            append(dll, n);
        }
    }
}


DoublyLinkedList *create_doubly_linked_list() {
    DoublyLinkedList *dll = malloc(sizeof(DoublyLinkedList));
    Node *dummy_ptr = create_node(NULL);
    dll->dummy_ptr = dummy_ptr;
    dll->length = 0;
    dll->dummy_ptr->next = dll->dummy_ptr;
    dll->dummy_ptr->prev = dll->dummy_ptr;
    return dll;
}

/**
 *
 * We move node at index n to different list.
 * This is when we want to move a card or several cards from on column to a different column or foundation.
 * The card c is not a card that is in the deck. It is a pointer to a temporary card that we use to find the card we want to move.
 * We create the temporary card when parsing the player input.
 * We need to free the card when it has been used.
 *
 * @param from list to move from
 * @param to list to move to
 * @param c a card with the same values as the one we want to move along with the ones below it. IS NOT SAME AS CARD TO MOVE, DIFFERENT POINTERS.
 *
 */
void move_cards(DoublyLinkedList *from, DoublyLinkedList *to, Card *c) {
    // TODO Implement
    Node *last_card_to_move = search_list_for_card(from, c);
    Node *first_card_to_move = from->dummy_ptr->next;

    Node *new_first_card = last_card_to_move->next;

    Node *n;
    int len = 1;
    while (n != last_card_to_move) {
        len++;
        n = first_card_to_move->next;
    }

    to->dummy_ptr->next->prev = last_card_to_move;
    last_card_to_move->next = to->dummy_ptr->next;
    first_card_to_move->prev = to->dummy_ptr;
    to->dummy_ptr->next = first_card_to_move;

    from->dummy_ptr->next = new_first_card;
    new_first_card->prev = from->dummy_ptr;

    from->length -= len;
    to->length += len;

}


//      B       X       A
// B-next = X
// A-prev = X
// B-next = A
// A-prev = B
Node *remove_at(DoublyLinkedList *dll, int index) {
    Node *n = get_node_at(dll, index);
    Node *n_before = n->prev;
    Node *n_after = n->next;
    n_before->next = n_after;
    n_after->prev = n_before;
    n->next = NULL;
    n->prev = NULL;
    dll->length--;
    return n;
}

void move_single_card(DoublyLinkedList *from, DoublyLinkedList *to) {
    Node *node_from = remove_at(from, 0);
    prepend(to, node_from);
}

Node *debug_to_array(DoublyLinkedList *dll, Node *arr[60]) {

    Node *curr = dll->dummy_ptr->next;
    int i = 1;
    arr[0] = NULL;
    while (curr->card_ptr != NULL) {
        arr[i] = curr;
        i++;
        curr = curr->next;
    }

}
