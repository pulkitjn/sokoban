#ifndef BOARD_H
#define BOARD_H

#include "constants.h"
#include "tile.h"
#include "location.h"

int has_wall_at_location(struct location location);

int has_storage_at_location(struct location location);

int has_box_at_location(struct location location);

int has_player_at_location(struct location location);

void clear_wall_at_location(struct location location);

void clear_storage_at_location(struct location location);

void clear_box_at_location(struct location location);

void clear_player_at_location(struct location location);

void set_player_at_location(struct location location);

void set_box_at_location(struct location location);

void update_board(struct location location, char type);

void init_board();

int is_board_won();

void print_board();

#endif /* BOARD_H */