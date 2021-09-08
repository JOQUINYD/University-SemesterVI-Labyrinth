#ifndef BOX_H
#define BOX_H
#include <stdbool.h>

typedef struct Box Box;

struct Box {
    bool up;
    bool down;
    bool right;
    bool left;
    char type;
    bool marked;
};

Box* newBox(char type);

#endif



