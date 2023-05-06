//
// Created by henrik on 5/5/23.
//

#ifndef YUKON_SOLITAIRE_HISTORY_H
#define YUKON_SOLITAIRE_HISTORY_H

struct History {
    char *command;
    struct History *next;
    struct History *prev;
};

#endif //YUKON_SOLITAIRE_HISTORY_H
