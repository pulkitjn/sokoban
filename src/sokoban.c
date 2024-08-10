// sokoban.c
// Written by PULKIT JAIN (19110196),
// on 28-06-2024
// TODO: Program Description

#include "level_builder.h"
#include "play.h"

int main() {

    if (level_builder() == -1) {
        return 0;
    }
    if (start_game() == -1) {
        return 0;
    }
    return 0;
}
