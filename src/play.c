#include "board.h"
#include "location.h"
#include "play.h"
#include "input_helper.h"
#include "moves.h"
#include <stdio.h>

static int check_if_player_movement_cmd(char cmd) {
    if (cmd == 'w' || cmd == 'a' || cmd == 's' || cmd == 'd') {
        return 0;
    }
    return -1;
}

static int check_if_moves_count_cmd(char cmd) {
    if (cmd == 'c') {
        return 0;
    }
    return -1;
}

static int check_if_game_reset_cmd(char cmd) {
    if (cmd == 'r') {
        return 0;
    }
    return -1;
}

static int check_if_undo_move_cmd(char cmd) {
    if (cmd == 'u') {
        return 0;
    }
    return -1;
}

static int validate_player_start_location(struct location location) {
    if (validate_location(location) == -1) {
        return -1;
    }
    if (has_wall_at_location(location) == 0 || has_box_at_location(location) == 0) {
        return -1;
    }
    return 0;
}

static struct location get_player_start_position() {
    int res = -1;
    struct location invalidLocation = {-1, -1};
    struct location startLocation = invalidLocation;
    while (res == -1) {
        printf("Enter player starting position: ");
        char inp[1024];
        int res = get_line_input(inp);
        if (res != 0) {
            return invalidLocation;
        }
        res = sscanf(inp, "%d %d", &startLocation.row, &startLocation.col);
        if (res != 2) {
            res = -1;
            continue;
        }
        res = validate_player_start_location(startLocation);
        if (res == -1) {
            printf("Position (%d, %d) is invalid\n", startLocation.row, startLocation.col);
        } else {
            return startLocation;
        }
    }
    return invalidLocation;
}

static int is_game_won() {
    int res = is_board_won();
    return res;
}

static void reset_game() {
    printf("=== Resetting Game ===\n");
    while(get_moves_counter()) {
        undo_move();
    }
}

static int play() {
    while (1) {
        int res = is_game_won();
        if (res == 0) {
            printf("=== Level Solved in %d Move", get_moves_counter());
            if (get_moves_counter()>1) {
                printf("s");
            }
            printf("! ===\n");
            return 0;
        }
        char inp[1024];
        res = get_line_input(inp);
        if (res != 0) {
            return -1;
        }
        char cmd;
        res = sscanf(inp, "%c", &cmd);
        if (res != 1) {
            res = -1;
            continue;
        }
        if (cmd == 'q') {
            return 0;
        } 
        res = check_if_player_movement_cmd(cmd);
        if (res == 0) {
            move_player(cmd);
        }
        res = check_if_moves_count_cmd(cmd);
        if (res == 0) {
            printf("Number of moves so far: %d\n", get_moves_counter());
        }
        res = check_if_game_reset_cmd(cmd);
        if (res == 0) {
            reset_game();
        }

        res = check_if_undo_move_cmd(cmd);
        if (res == 0) {
            undo_move();
        }
        print_board();
    }
    return -1;
}

int start_game() {
    struct location location = get_player_start_position();
    if (location.row == -1 || location.col == -1) {
        return -1;
    }
    set_player_at_location(location);
    printf("\n=== Starting Sokoban! ===\n");
    print_board();
    init_moves();
    play();
    return 0;
}