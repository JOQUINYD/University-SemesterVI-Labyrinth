#include <stdio.h>
#include <stdbool.h>
#include "sources/Box.c"
#include "sources/Path.c"
#include "sources/PathFinder.c"
#include "sources/Printer.c"
#include "sources/PrinterInfo.c"
#include <sys/mman.h>


Box** crateMatrix(int rows, int cols){
    Box** matrix = malloc(rows * sizeof *matrix);
    for (int i=0; i<rows; i++)
    {
        matrix[i] = malloc(cols * sizeof *matrix[i]);
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] = *newBox('*');

        }
        
    }
    matrix[0][0].marked = true;
    matrix[0][0].down = true;

    matrix[0][0].type = ' ';
    matrix[1][0].type = ' ';
    matrix[1][1].type = ' ';
    matrix[2][1].type = ' ';
    matrix[3][1].type = ' ';
    matrix[3][2].type = ' ';
    matrix[4][2].type = ' ';   
    return matrix;
}



int main(int argc, char *argv[]){

  
    int cols = 5;
    int rows = 5;

    //Get the Matrix
    Box** matrixThreads = crateMatrix(rows,cols); 
    
    //SetVariables
    setVariables(matrixThreads,rows,cols); 
    
    //Create first Path
    Path* startPathThread = newPath(0,0,'d',0);
    
    //Create first thread
    pthread_t t1;
    pthread_create(&t1, NULL, &executeThread, startPathThread);

    //Declare Printer Info
    bool *finished = malloc(sizeof finished);
    *finished = false;
    PrinterInfo *printerInfo = newPrinterInfo(matrixThreads,rows,cols,finished);

    //Create PrinterThread
    pthread_t printerThread;
    pthread_create(&printerThread, NULL, &printMatrix, printerInfo);

    //Join the PathFinderExecute Thread
    pthread_join(t1, NULL);
    
    //Finish Printer Thread
    *finished = true;
    
    //Join Printer Thread
    pthread_join(printerThread, NULL);
    
    





    
    printf("Terminé crack\n");

    return 0;
}