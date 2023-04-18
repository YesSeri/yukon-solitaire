//
// Created by tobia on 17/04/2023.
//

#ifndef YUKON_SOLITAIRE_GAME_H
#define YUKON_SOLITAIRE_GAME_H

#include "DoublyLinkedList.h"

void show_action(char *input);
void load_action(char *input);
void quit_action(char *input);
void to_startup_action(char *input);
void to_play_action(char *input);
void move_action(char *input);
void error_action(char *input);
DoublyLinkedList *columns_arr[];
#endif //YUKON_SOLITAIRE_GAME_H