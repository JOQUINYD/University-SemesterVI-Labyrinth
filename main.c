#include <stdio.h>
#include <stdbool.h>
#include "sources/Box.c"
#include "sources/Path.c"
#include "sources/PathFinder.c"
#include "sources/Printer.c"
#include "sources/PrinterInfo.c"
#include <sys/mman.h>
#include <sys/wait.h>


int cols = 5;
int rows = 5;

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
    matrix[1][2].type = ' ';
    matrix[2][3].type = ' ';
    matrix[1][3].type = ' ';
    matrix[3][1].type = ' ';
    matrix[3][2].type = '/';
    matrix[4][2].type = ' ';   
    matrix[3][3].type = ' '; 
    return matrix;
}

Box** crateSharedMatrix(int rows, int cols){
    Box** matrix = mmap(NULL, rows * sizeof *matrix, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0); 


    for (int i=0; i<rows; i++)
    {
        matrix[i] = mmap(NULL, cols * sizeof *matrix[i], PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0); 
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] = *newSharedBox('*');

        }
        
    }
    matrix[0][0].marked = true;
    matrix[0][0].down = true;

    matrix[0][0].type = ' ';
    matrix[1][0].type = ' ';
    matrix[1][1].type = ' ';
    matrix[2][1].type = ' ';
    matrix[1][2].type = ' ';
    matrix[2][3].type = ' ';
    matrix[1][3].type = ' ';
    matrix[3][1].type = ' ';
    matrix[3][2].type = '/';
    matrix[4][2].type = ' ';   
    matrix[3][3].type = ' ';
    return matrix;
}


void threadExecution(){
   //Thread execution
    printf("///////////////////////////////////////////////////////////////////////////\n");
    printf("Inicia Ejecucion Threads\n");
    sleep(1);

    // MUTEX
    pthread_mutex_t mutexThread;
    pthread_mutex_init(&mutexThread, NULL);

    //Get the Matrix
    Box** matrixThreads = crateMatrix(rows,cols); 

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
}

void forkExecution(){
    //Fork Execution 
    printf("///////////////////////////////////////////////////////////////////////////\n");
    printf("Inicia Ejecucion Forks\n");
    sleep(1);

    // MUTEX
    pthread_mutex_t *mutexFork = mmap(NULL, sizeof mutexFork, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0); 
    pthread_mutex_init(mutexFork, NULL);

    //Get the Matrix
    Box** matrixForks = crateSharedMatrix(rows,cols); 
    
    //Declare Printer Info
    bool *finishedForks = mmap(NULL, sizeof finishedForks, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0); 

    *finishedForks = false;
    PrinterInfo *printerInfoForks = newPrinterInfo(matrixForks,rows,cols,finishedForks);

   
    //SetVariables
    setVariables(matrixForks,rows,cols, mutexFork); 
    
    //Create first Path
    Path* startPathFork = newPath(0,0,'d',0);
 


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
  
    //threadExecution();
    forkExecution();

    return 0;
}