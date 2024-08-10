#include "board.h"
#include <stdio.h>
#include <string.h>

struct tile board[ROWS][COLS];

static struct tile* get_tile_ptr(struct location location) {
    return (&board[location.row][location.col]);
}

static struct tile get_tile(struct location location) {
    return (board[location.row][location.col]);
}

int has_wall_at_location(struct location location) {
    struct tile tile = get_tile(location);
    return (has_wall(tile));
}

int has_storage_at_location(struct location location) {
    struct tile tile = get_tile(location);
    return (has_storage(tile));
}

int has_box_at_location(struct location location) {
    struct tile tile = get_tile(location);
    return (has_box(tile));
}

int has_player_at_location(struct location location) {
    struct tile tile = get_tile(location);
    return (has_player(tile));
}

void clear_wall_at_location(struct location location) {
    struct tile* tilePtr = get_tile_ptr(location);
    clear_wall(tilePtr);
}

void clear_storage_at_location(struct location location) {
    struct tile* tilePtr = get_tile_ptr(location);
    clear_storage(tilePtr);
}

void clear_box_at_location(struct location location) {
    struct tile* tilePtr = get_tile_ptr(location);
    clear_box(tilePtr);
}

void clear_player_at_location(struct location location) {
    struct tile* tilePtr = get_tile_ptr(location);
    clear_player(tilePtr);
}

void set_player_at_location(struct location location) {
    struct tile* tilePtr = get_tile_ptr(location);
    set_player(tilePtr);
}

void set_box_at_location(struct location location) {
    struct tile* tilePtr = get_tile_ptr(location);
    set_box(tilePtr);
}

void update_board(struct location location, char type) {
    struct tile* tilePtr = get_tile_ptr(location);
    update_tile_from_type(tilePtr, type);
}

int is_board_won() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            struct location location = {i,j};
            if (has_box_at_location(location) == 0 
                && has_storage_at_location(location) != 0) {
                return -1;
            }
        }
    }
    return 0;
}

// initialises the board to default values.
void init_board() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            struct location location = {i,j};
            struct tile* tilePtr = get_tile_ptr(location);
            init_tile(tilePtr);
        }
    }
}

// Helper function for print_board().
// Prints a line the width of the sokoban board.
static void print_line(void) {
    for (int i = 0; i < COLS * 4 + 1; i++) {
        printf("-");
    }
    printf("\n");
}

// Helper function for print_board().
// Prints out the title for above the sokoban board.
static void print_title(void) {
    print_line();
    char *title = "S O K O B A N";
    int len = COLS * 4 + 1;
    int n_white = len - strlen(title) - 2;
    printf("|");
    for (int i = 0; i < n_white / 2; i++) {
        printf(" ");
    }
    printf("%s", title);
    for (int i = 0; i < (n_white + 1) / 2; i++) {
        printf(" ");
    }
    printf("|\n");
}

// Prints out the current state of the sokoban board.
// It will place the player on the board at position player_row, player_col.
// If player position is out of bounds, it won't place a player anywhere.
void print_board() {
    print_title();
    for (int i = 0; i < ROWS; i++) {
        print_line();
        for (int j = 0; j < COLS; j++) {
            printf("|");
            struct location location = {i,j};
            struct tile tile = get_tile(location);
            char tileString[4];
            get_tile_string(tile, tileString);
            printf("%s",tileString);
        }
        printf("|\n");
    }
    print_line();
    printf("\n");
}
