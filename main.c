#include <stdio.h>
#include <stdbool.h>
#include "sources/Box.c"
#include "sources/Path.c"
#include "sources/PathFinder.c"
#include "sources/Printer.c"
#include "sources/PrinterInfo.c"
#include "sources/MatrixInfo.c"
#include <sys/mman.h>


Box** crateMatrix(int rows, int cols, MatrixInfo* matrixInfo){
    Box** matrix = malloc(rows * sizeof *matrix);
    for (int i=0; i<rows; i++)
    {
        matrix[i] = malloc(cols * sizeof *matrix[i]);
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] = *newBox(matrixInfo->matrix[i][j]);

        }
        
    }
    matrix[0][0].marked = true;
    matrix[0][0].down = true;

    return matrix;
}

Box** crateSharedMatrix(int rows, int cols, MatrixInfo* matrixInfo){
    Box** matrix = mmap(NULL, rows * sizeof *matrix, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0); 


    for (int i=0; i<rows; i++)
    {
        matrix[i] = mmap(NULL, cols * sizeof *matrix[i], PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0); 
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] = *newSharedBox(matrixInfo->matrix[i][j]);

        }
        
    }
    matrix[0][0].marked = true;
    matrix[0][0].down = true;
 
    return matrix;
}

int main(int argc, char *argv[]){

    char* path = "/home/mela227/Downloads/lab1.txt";
    MatrixInfo* matrixInfo = newMatrixInfo(path);
    
  
    int cols = matrixInfo->columns;
    int rows = matrixInfo->rows;


    ///////////////////////////////////////////////////////////////////////////

    //Thread execution
    printf("///////////////////////////////////////////////////////////////////////////\n");
    printf("Inicia Ejecucion Threads\n");
    sleep(1);

    // MUTEX
    pthread_mutex_t mutexThread;
    pthread_mutex_init(&mutexThread, NULL);

    //Get the Matrix
    Box** matrixThreads = crateMatrix(rows,cols,matrixInfo); 

    //Declare Printer Info
    bool *finishedThreads = malloc(sizeof finishedThreads);
    *finishedThreads = false;
    PrinterInfo *printerInfoThreads = newPrinterInfo(matrixThreads,rows,cols,finishedThreads);

    //Create PrinterThread
    pthread_t printerThreads;
    pthread_create(&printerThreads, NULL, &printMatrix, printerInfoThreads);
    
    //SetVariables
    setVariables(matrixThreads,rows,cols, &mutexThread); 
    
    //Create first Path
    Path* startPathThread = newPath(0,0,'d',0);
    
    //Create first thread
    pthread_t t1;
    pthread_create(&t1, NULL, &executeThread, startPathThread);

    //Join the PathFinderExecute Thread
    pthread_join(t1, NULL);
    
    //Finish Printer Thread
    *finishedThreads = true;
    
    //Join Printer Thread
    pthread_join(printerThreads, NULL);
    
    printf("TERMINA THREAD\n");

    pthread_mutex_destroy(&mutexThread);    

    ///////////////////////////////////////////////////////////////////////////

    //Fork Execution 
    printf("///////////////////////////////////////////////////////////////////////////\n");
    printf("Inicia Ejecucion Forks\n");
    sleep(1);

    // MUTEX
    pthread_mutex_t *mutexFork = mmap(NULL, sizeof mutexFork, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0); 
    pthread_mutex_init(mutexFork, NULL);

    //Get the Matrix
    Box** matrixForks = crateSharedMatrix(rows,cols,matrixInfo); 
    
    //Declare Printer Info
    bool *finishedForks = mmap(NULL, sizeof finishedForks, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0); 

    *finishedForks = false;
    PrinterInfo *printerInfoForks = newPrinterInfo(matrixForks,rows,cols,finishedForks);

   
    //SetVariables
    setVariables(matrixForks,rows,cols, mutexFork); 
    
    //Create first Path
    Path* startPathFork = newPath(0,0,'d',0);

    //Fork the execution and Printer
    if (fork()==0)
    {
        executeFork(startPathFork);
        wait();
        *finishedForks = true;

    }
    else{
        printMatrix(printerInfoForks);
    }



    return 0;
}