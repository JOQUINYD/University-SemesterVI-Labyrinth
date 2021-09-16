#ifndef PRINTER_INFO_H
#define PRINTER_INFO_H
#include <stdbool.h>
#include "Box.h"
#include <stdlib.h>

typedef struct PrinterInfo PrinterInfo;

struct PrinterInfo {
    Box** matrix;
    int numOfRows;
    int numOfCols;
    bool* done;
};

PrinterInfo* newPrinterInfo(Box** matrix, int numOfRows, int numOfCols, bool* done);

#endif