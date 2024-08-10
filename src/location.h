#ifndef LOCATION_H
#define LOCATION_H

struct location {
    int row;
    int col;
};

int validate_bound(int index, int maxBound);

int validate_location(struct location location);

void print_location(struct location location);

#endif /* LOCATION_H */