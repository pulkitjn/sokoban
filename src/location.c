#include "constants.h"
#include "location.h"

#include <stdio.h>

int validate_bound(int index, int maxBound) {
    if (index < 0 || index > maxBound-1) {
        //printf("DBG: index=%d is out of bounds=%d\n", index, maxBound);
        return -1;
    }
    return 0;
}

int validate_location(struct location location) {
    if (validate_bound(location.row, ROWS) == -1) {
        return -1;
    }
    if (validate_bound(location.col, COLS) == -1) {
        return -1;
    }
    return 0;
}

void print_location(struct location location) {
    printf("%d %d\n", location.row, location.col);
}