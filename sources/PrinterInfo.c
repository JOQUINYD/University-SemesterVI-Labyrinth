#include "../headers/PrinterInfo.h"
#include <sys/mman.h>



PrinterInfo* newPrinterInfo(Box** matrix, int numOfRows, int numOfCols, bool* done){
    //new
    PrinterInfo* self = (PrinterInfo*)malloc(sizeof(PrinterInfo));
    
    //atributes
    self->matrix = matrix;
    self->numOfRows = numOfRows;
    self->numOfCols = numOfCols;
    self->done = done;
    
    return self;
}