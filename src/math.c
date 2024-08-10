#include "math.h"

int int_compare(int a, int b) {
    int res = a-b;
    if (res < 0) {
        return -1;
    }
    return 0;
}

int min(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}