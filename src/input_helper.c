#include <stdio.h>
#include <string.h>
#include "input_helper.h"

int get_line_input(char* res) {
    char input[1024];
    if (fgets(input, 1024, stdin) != NULL) {
        strcpy(res, input);
        return 0;
    } else {
        return -1;
    }
    return 0;
}