#include <stdio.h>
#include <stdbool.h>
#include "sources/Box.c"
#include "sources/MatrixInfo.c"

int main(int argc, char *argv[]){

    char* path = "/home/mela227/Downloads/lab1.txt";
    MatrixInfo* matrixInfo = newMatrixInfo(path);
    //matrixInfo->getMatrixSize(matrixInfo);
    printf("%d", matrixInfo->rows);
    printf("%d", matrixInfo->columns);
    
    printf("\n");
    return 0;
}