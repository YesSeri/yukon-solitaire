//
// Created by henrik on 4/12/23.
//

#ifndef CODE_VIEW_H
#define CODE_VIEW_H

#include "Game.h"
#include "Foundation.h"

#define NUMBER_OF_CARDS 52
#define NUMBER_OF_COLUMNS 7
#define NUMBER_OF_FOUNDATIONS 4

void print_view(DoublyLinkedList *[NUMBER_OF_COLUMNS], Foundation *[NUMBER_OF_FOUNDATIONS], char *);

void print_main_section(DoublyLinkedList *[NUMBER_OF_COLUMNS], Foundation *[NUMBER_OF_FOUNDATIONS]);

#endif // CODE_VIEW_H
