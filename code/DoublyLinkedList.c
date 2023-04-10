// This includes #define for ace, 1, 2, ... king and for suits heart, club, diamond, spade.
#include "Types.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int Value;
typedef char Suit;

typedef struct node {
    int data;
    struct node* next;
    struct node* prev;
} Node;

void insert_at_head(Node** head_ptr, Node* node_ptr)
{
    node_ptr->next = (*head_ptr);
    (*head_ptr) = node_ptr;
}

void print_linked_list(Node* deck)
{
    Node* current = deck;

    printf("HEAD -> ");
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main()
{
    Node* head = NULL;

    for (int i = 0; i < 20; i++) {
        Node* n = malloc(sizeof(Node));
        n->next = NULL;
        n->data = i;
        insert_at_head(&head, n);
    }

    print_linked_list(head);
    return 0;
}