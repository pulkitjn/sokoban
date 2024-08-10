#include "moves.h"
#include "location.h"
#include "board.h"

struct move {
    char cmd;
    int boxesMoved;
};

static int movesCounter;

static struct move moves[1024];

void reset_move(struct move* movePtr) {
    (*movePtr).cmd = '\0';
    (*movePtr).boxesMoved = 0;
}

void init_moves() {
    movesCounter = 0;
    for (int i = 0; i < 1024; i++) {
         reset_move(&moves[i]);
    }
}

static char get_opp_move(char cmd) {
    if (cmd == 'w') {
        return 's';
    }
    if (cmd == 's') {
        return 'w';
    }
    if (cmd == 'a') {
        return 'd';
    }
    if (cmd == 'd') {
        return 'a';
    }
    return '\0';
}

int get_moves_counter() {
    return movesCounter;
}

static int increment_moves_counter() {
    movesCounter++;
    return movesCounter;
}

static int decrement_moves_counter() {
    movesCounter--;
    return movesCounter;
}

static int push_move(char cmd, int boxesMoved) {
    struct move move = {cmd, boxesMoved};
    int movesCount = increment_moves_counter();
    moves[movesCount-1] = move;
    return movesCount;
}

static struct move pop_move() {
    int movesCount = get_moves_counter();
    if (movesCount == 0) {
        struct move move;
        reset_move(&move);
        return move;
    }
    struct move lastMove = moves[movesCount-1];
    reset_move(&moves[movesCount-1]);
    decrement_moves_counter();
    return lastMove;
}


static struct location get_player_current_location() {
    struct location currentLocation = {-1,-1};
    for (int row = 0; row < ROWS; row++) {
        currentLocation.row = row;
        for(int col = 0; col < COLS; col++) {
            currentLocation.col = col;
            if (has_player_at_location(currentLocation) == 0) {
                return currentLocation;
            }
        }
    }
    return currentLocation;
}

static struct location get_next_location(char cmd, struct location oldlocation, int distance) {
    struct location newLocation = oldlocation;
    if (cmd == 'w') {
        newLocation.row -= distance;
        if (newLocation.row < 0) {
            newLocation.row += ROWS;
        }
    }
    if (cmd == 's') {
        newLocation.row += distance;
        if (newLocation.row > ROWS - 1) {
            newLocation.row -= ROWS;
        }
    }
    if (cmd == 'a') {
        newLocation.col -= distance;
        if (newLocation.col < 0) {
            newLocation.col += COLS;
        }
    }
    if (cmd == 'd') {
        newLocation.col += distance;
        if (newLocation.col > COLS - 1) {
            newLocation.col -= COLS;
        }
    }
    return newLocation;
}

static int box_stack_move(struct location location, char cmd) {
    if (has_box_at_location(location) != 0) {
        return 0;
    }
    int boxesMoved = 0;
    struct location oldlocation = location;
    do {
        struct location newLocation = get_next_location(cmd, oldlocation, 1);
        print_location(newLocation);
        if (has_wall_at_location(newLocation) == 0) {
            return -1;
        }
        oldlocation = newLocation;
        boxesMoved++;
    } while (has_box_at_location(oldlocation) == 0);
    clear_box_at_location(location);
    set_box_at_location(oldlocation);
    return boxesMoved;
}

static void clear_player_previous_location() {
    for (int row = 0; row < ROWS; row++) {
        for(int col = 0; col < COLS; col++) {
            struct location location = {row, col};
            if (has_player_at_location(location) == 0) {
                clear_player_at_location(location);
            }
        }
    }
}

static void update_player_location(struct location location) {
    clear_player_previous_location();
    set_player_at_location(location);
}

int move_player(char cmd) {
    struct location oldlocation = get_player_current_location();
    struct location newLocation = get_next_location(cmd, oldlocation, 1);
    print_location(newLocation);
    if (has_wall_at_location(newLocation) == 0) {
        return -1;
    }
    int boxesMoved = box_stack_move(newLocation, cmd);
    if (boxesMoved == -1) {
        return -1;
    }
    update_player_location(newLocation);
    push_move(cmd, boxesMoved);
    return 0;
}

int undo_move() {
    if (get_moves_counter() == 0) {
        return -1;
    }
    struct move lastMove = pop_move();
    char cmd = get_opp_move(lastMove.cmd);
    struct location playerOldLocation = get_player_current_location();
    struct location playerNewLocation = get_next_location(cmd, playerOldLocation, 1);
    struct location lastBoxLocation = get_next_location(lastMove.cmd, playerOldLocation, lastMove.boxesMoved);
    clear_box_at_location(lastBoxLocation);
    update_player_location(playerNewLocation);
    set_box_at_location(playerOldLocation);
    return get_moves_counter();
}
