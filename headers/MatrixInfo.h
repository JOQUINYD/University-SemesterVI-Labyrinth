#ifndef MATRIXINFO_H
#define MATRIXINFO_H
#include <stdbool.h>
#include "Box.h"

typedef struct MatrixInfo MatrixInfo;

struct MatrixInfo {
    int rows;
    int columns;
    Box** matrix;
    char* path;
    void (*getMatrixSize)(MatrixInfo* self);
    char** (*generateMatrixChars)(MatrixInfo* self);
};

MatrixInfo* newMatrixInfo(char* path);

#endif

