#ifndef BOX_H
#define BOX_H
#include <stdbool.h>
#include <stdlib.h>

typedef struct Box Box;

struct Box {
    bool up;
    bool down;
    bool right;
    bool left;
    char type;
    bool marked;
    char first;
};

Box* newBox(char type);
Box* newSharedBox(char type);

#endif



