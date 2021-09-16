#ifndef PATH_H
#define PATH_H
#include <stdbool.h>
#include "Box.h"
#include <pthread.h>
#include <stdlib.h>

typedef struct Path Path;

struct Path {
    int i;
    int j;
    char direction;
    int amount;
    bool win;

    void (*printFinish)(Path* self);

};

Path* newPath();

#endif