#ifndef TILE_H
#define TILE_H

// Every tile on the map has to be one of the following values.
enum base { 
    NONE,
    WALL,
    STORAGE
};

// A single tile of our board.
// box should only contain the value:
// - true (1): there exists a box here
// - false (0): there doesn't exist a box here
struct tile {
    enum base base;
    int box;
    int player;
};

void init_tile(struct tile* tilePtr);

int has_wall(struct tile tile);

int has_storage(struct tile tile);

int has_player(struct tile tile);

int has_box(struct tile tile);

void set_wall(struct tile* tilePtr);
void clear_wall(struct tile* tilePtr);

void set_storage(struct tile* tilePtr);
void clear_storage(struct tile* tilePtr);

void set_box(struct tile* tilePtr);
void clear_box(struct tile* tilePtr);

void set_player(struct tile* tilePtr);
void clear_player(struct tile* tilePtr);

void get_tile_string(struct tile tile, char* s);

void update_tile_from_type(struct tile* tilePtr, char type);

#endif /* TILE_H */
