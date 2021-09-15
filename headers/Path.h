#ifndef PATH_H
#define PATH_H
#include <stdbool.h>
#include "Box.h"

typedef struct Path Path;

struct Path {
    int i;
    int j;
    char direction;
    int amount;
    bool done;
};

Path* newPath(int i, int j, char direction, int amount);

#endif