#include <stdio.h>
#include <stdbool.h>
#include "sources/Box.c"
#include "sources/Path.c"
#include "sources/PathFinder.c"
#include "sources/Printer.c"
#include "sources/PrinterInfo.c"
#include "sources/MatrixInfo.c"
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>


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



void threadExecution(MatrixInfo* matrixInfo){

    int cols = matrixInfo->columns;
    int rows = matrixInfo->rows;

   //Thread execution
    printf("\n///////////////////////////////////////////////////////////////////////////\n");
    printf("Inicia Ejecucion Threads\n\n");
    sleep(2);

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
    Path* startPathThread = newPath();
    
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
}

void forkExecution(MatrixInfo* matrixInfo){

    int cols = matrixInfo->columns;
    int rows = matrixInfo->rows;

    //Fork Execution 
    printf("\n///////////////////////////////////////////////////////////////////////////\n");
    printf("Inicia Ejecucion Forks\n\n");
    sleep(2);

    // MUTEX
    pthread_mutex_t *mutexFork = mmap(NULL, sizeof mutexFork, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0); 
    pthread_mutexattr_t *att = mmap(NULL, sizeof att, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    pthread_mutexattr_init(att);
    pthread_mutexattr_setrobust(att,1);
    pthread_mutexattr_setpshared(att, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(mutexFork, att);

    //Get the Matrix
    Box** matrixForks = crateSharedMatrix(rows,cols,matrixInfo); 
    
    //Declare Printer Info
    bool *finishedForks = mmap(NULL, sizeof finishedForks, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0); 

    *finishedForks = false;
    PrinterInfo *printerInfoForks = newPrinterInfo(matrixForks,rows,cols,finishedForks);

   
    //SetVariables
    setVariables(matrixForks,rows,cols, mutexFork); 
    
    //Create first Path
    Path* startPathFork = newPath();
 


    //Create PrinterThread
    pthread_t printerForks;
    pthread_create(&printerForks, NULL, &printMatrix, printerInfoForks);

    pid_t pid = fork();
    
    int status;
    if (pid==0)  
    {
        executeFork(startPathFork);
        
    }
    else{
        waitpid(pid,&status,0);
        *finishedForks = true;
    }

    //Join Printer Thread
    pthread_join(printerForks,NULL);



}



int main(int argc, char *argv[]){
        
    char* path = "Tests/lab2.txt";
    MatrixInfo* matrixInfo = newMatrixInfo(path);
    matrixInfo->matrix[0][2] = '*';

    threadExecution(matrixInfo);
    forkExecution(matrixInfo);

    return 0;
}