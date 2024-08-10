#include "level_builder.h"
#include "constants.h"
#include "board.h"
#include "location.h"
#include "math.h"
#include "input_helper.h"

#include <stdio.h>

static int check_type1(char type) {
    if (type != 'w' && type != 's' && type != 'b') {
        return -1;
    }
    return 0;
}

static int check_type2(char type) {
    if (type != 'W') {
        return -1;
    }
    return 0;
}

static int find_cmd_type(char* cmd) {
    if (check_type1(cmd[0]) != -1) {
        //printf("DBG: Cmd type 1\n");
        return 1;
    }
    if (check_type2(cmd[0]) != -1) {
        //printf("DBG: Cmd type 2\n");
        return 2;
    }
    //printf("DBG: Invalid cmd type:%c\n", cmd[0]);
    return -1;
}

static int validate_type1_cmd(char type, struct location location) {
    if (check_type1(type) == -1) {
        return -1;
    } 
    if (validate_location(location) == -1) {
        printf("Location out of bounds\n");
        return -1;
    }
    return 0;
}

static int validate_type2_cmd(char type, struct location startLocation, struct location endLocation) {
    if (check_type2(type) == -1) {
        return -1;
    } 
    if (validate_location(startLocation) == -1 && validate_location(endLocation) == -1) {
        printf("Location out of bounds\n");
        return -1;
    }
    if (int_compare(endLocation.row, startLocation.row) == -1) {
        //printf("DBG: endRow=%d<startRow=%d\n", endRow, startRow);
        return -1;
    }
    if (int_compare(endLocation.col, startLocation.col) == -1) {
        //printf("DBG: endCol=%d<startCol=%d\n", endCol, startCol);
        return -1;
    }
    if (startLocation.row != endLocation.row && startLocation.col != endLocation.col) {
        //printf("DBG: startRow=%d endRow=%d startCol=%d endCol=%d\n", startRow, endRow, startCol, endCol);
        return -1;
    }
    return 0;
}

static int parse_type1_cmd_and_update_board(char* cmd) {

    char type;
    int row, col;
    int res = sscanf(cmd, "%c %d %d", &type, &row, &col);

    if (res != 3) {
        //printf("DBG: Failure in parsing type1 cmd parsed var count=%d\n", res);
        return -1;
    }
    struct location location = {row, col};
    if (validate_type1_cmd(type, location) == -1) {
        //printf("DBG: Failure in parsing type1 cmd\n");
        return -1;
    }
    update_board(location, type);
    return 0;
}

static int parse_type2_cmd_and_update_board(char* cmd) {
    char type;
    int startRow, startCol, endRow, endCol;
    int res = sscanf(cmd, "%c %d %d %d %d", &type, &startRow, &startCol, &endRow, &endCol);

    if (res != 5) {
        //printf("DBG: Failure in parsing type2 cmd parsed var count=%d\n", res);
        return -1;
    }
    struct location startLocation = {startRow, startCol};
    struct location endLocation = {endRow, endCol};
    if (validate_type2_cmd(type, startLocation, endLocation) == -1) {
        //printf("DBG: Failure in parsing type2 cmd\n");
        return -1;
    }

    startLocation.row = max(startLocation.row, 0);
    startLocation.col = max(startLocation.col, 0);

    endLocation.row = min(endLocation.row, ROWS-1);
    endLocation.col = min(endLocation.col, COLS-1);

    struct location currLocation = startLocation;
    while (startLocation.row != endLocation.row &&
             currLocation.row <= endLocation.row) {
        update_board(currLocation, type);
        currLocation.row++;
    }
    while (startLocation.col != endLocation.col &&
            currLocation.col <= endLocation.col) {
        update_board(currLocation, type);
        currLocation.col++;
    }
    return 0;
}

static int parse_input_and_update_board(char* cmd) {
    int cmdType = find_cmd_type(cmd);
    if (cmdType == -1) {
        return -1;
    }
    if (cmdType == 1 && parse_type1_cmd_and_update_board(cmd) != -1) {
        return 0;
    }
    if (cmdType == 2 && parse_type2_cmd_and_update_board(cmd) != -1) {
        return 0;
    }
    return -1;
}

int level_builder() {
    init_board();
    printf("=== Level Setup ===\n");
    while(1) {
        char cmd[1024];
        if (get_line_input(cmd) == 0) {
            if (cmd[0] == 'q') {
                return 0;
            }
            parse_input_and_update_board(cmd);
            print_board();
        } else {
            return -1;
        }
    }
    return -1;
}