#include <string.h>
#include "tile.h"

int has_wall(struct tile tile) {
    if (tile.base == WALL) {
        return 0;
    }
    return -1;
}

int has_storage(struct tile tile) {
    if (tile.base == STORAGE) {
        return 0;
    }
    return -1;
}

int has_player(struct tile tile) {
    if (tile.player == 1) {
        return 0;
    }
    return -1;
}

int has_box(struct tile tile) {
    if (tile.box == 1) {
        return 0;
    }
    return -1;
}

void set_wall(struct tile* tilePtr) {
    (*tilePtr).base = WALL;
    clear_box(tilePtr);
    clear_player(tilePtr);
}

void set_none(struct tile* tilePtr) {
    (*tilePtr).base = NONE;
}

void init_tile(struct tile* tilePtr) {
    (*tilePtr).base = NONE;
    (*tilePtr).box = 0;
    (*tilePtr).player = 0;
}

void set_storage(struct tile* tilePtr) {
    (*tilePtr).base = STORAGE;
}

void set_box(struct tile* tilePtr) {
    (*tilePtr).box = 1;
}

void set_player(struct tile* tilePtr) {
    (*tilePtr).player = 1;
}

void clear_wall(struct tile* tilePtr) {
    set_none(tilePtr);
}

void clear_storage(struct tile* tilePtr) {
    set_none(tilePtr);
}

void clear_box(struct tile* tilePtr) {
    (*tilePtr).box = 0;
}

void clear_player(struct tile* tilePtr) {
    (*tilePtr).player = 0;
}

void get_tile_string(struct tile tile, char* tileString) {
    if (tile.player == 1) {
        strcpy(tileString,"^_^");
        return;
    }
    if (tile.base == WALL) {
        strcpy(tileString, "===");
        return;
    }
    if (tile.box && tile.base == STORAGE) {
        strcpy(tileString, "[o]");
        return;
    }
    if (tile.box) {
        strcpy(tileString, "[ ]");
        return;
    }
    if (tile.base == STORAGE) {
        strcpy(tileString, " o ");
        return;
    }
    if (tile.base == NONE) {
        strcpy(tileString, "   ");
        return;
    }
}

void update_tile_from_type(struct tile* tilePtr, char type) {

    if (type == 'w' || type == 'W') {
        set_wall(tilePtr);
    }
    if (type == 'b') {
        set_box(tilePtr);
        if (has_wall(*tilePtr) == 0) {
            clear_wall(tilePtr);
        }
    }
    if (type == 's') {
        set_storage(tilePtr);
    }
}