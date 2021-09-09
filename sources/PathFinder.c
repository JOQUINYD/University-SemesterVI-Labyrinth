#include "../headers/Path.h"
#include <pthread.h>


Box** matrix;
int rows;
int cols;


void setVariables(Box** matrix_i, int rows_i, int cols_i){
    matrix = matrix_i;
    rows = rows_i;
    cols = cols_i;
}


//mutex
bool canMoveTo(Path* path, char direction){

    switch (direction)
    {
        case 'u':
            if((path->i-1)>=0){
                Box* box = &(matrix[path->i-1][path->j]);

                if (box->type==' ' && !(box->up))
                {
                    return true;
                }
            }
            break;
        
        case 'd':
            if((path->i+1)<rows){
                Box* box = &(matrix[path->i+1][path->j]);

                if (box->type==' ' && !(box->down))
                {
                    return true;
                }
            }
            break;
        
        case 'l':
            if((path->j-1)>=0){
                Box* box = &(matrix[path->i][path->j-1]);

                if (box->type==' ' && !(box->left))
                {
                    return true;
                }
            }
            break;
        
        case 'r':
            if((path->j+1)<cols){
                Box* box = &(matrix[path->i][path->j+1]);

                if (box->type==' ' && !(box->right))
                {
                    return true;
                }
            }
            break;

        default:
            return false; 
            break;
    }
    return false;


}

//mutex
void move(Path* path, char direction){
    switch (direction)
    {
        case 'u':
            path->direction = 'u';
            path->amount++;
            path->i--;

            matrix[path->i][path->j].marked = true;
            matrix[path->i][path->j].up = true;

            break;
        case 'd':
            path->direction = 'd';
            path->amount++;
            path->i++;

            matrix[path->i][path->j].marked = true;
            matrix[path->i][path->j].down = true;

            break;
        case 'l':
            path->direction = 'l';
            path->amount++;
            path->j--;

            matrix[path->i][path->j].marked = true;
            matrix[path->i][path->j].left= true;

            break;
        case 'r':
            path->direction = 'r';
            path->amount++;
            path->j++;

            matrix[path->i][path->j].marked = true;
            matrix[path->i][path->j].right = true;

            break;
    }

}

void *printMatrix(){

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix[i][j].marked)
            {
                printf("x");
            }
            else{
                printf("o");
            }
            
        }
            printf("\n");

    }
    printf("------------------------------------\n");

}

void printM(){
    pthread_t t1;
    pthread_create(&t1, NULL, &printMatrix, NULL);
    pthread_join(t1, NULL);
}

void *executeThread(Path* path){


    if (path->direction!='u' && canMoveTo(path,'u'))
    {
        pthread_t t1;
        Path* newPath = clonePath(path);
        move(newPath,'u');
        pthread_create(&t1, NULL, &executeThread, newPath);
        pthread_join(t1, NULL);

    }
    if (path->direction!='d' && canMoveTo(path,'d'))
    {
        pthread_t t1;
        Path* newPath = clonePath(path);
        move(newPath,'d');
        pthread_create(&t1, NULL, &executeThread, newPath);
        pthread_join(t1, NULL);

    }
    if (path->direction!='r' && canMoveTo(path,'r'))
    {
        pthread_t t1;
        Path* newPath = clonePath(path);
        move(newPath,'r');
        pthread_create(&t1, NULL, &executeThread, newPath);
        pthread_join(t1, NULL);

    }
    if (path->direction!='l' && canMoveTo(path,'l'))
    {
        pthread_t t1;
        Path* newPath = clonePath(path);
        move(newPath,'l');
        pthread_create(&t1, NULL, &executeThread, newPath);
        pthread_join(t1, NULL);

    }

    
    if(canMoveTo(path,path->direction)){
        move(path,path->direction);
        executeThread(path);
    }

}

void executeFork(Path* path){


    if (path->direction!='u' && canMoveTo(path,'u'))
    {
        if(fork()==0){
            path->direction = 'u';
        }
    }
    if (path->direction!='d' && canMoveTo(path,'d'))
    {
        if(fork()==0){
            path->direction = 'd';
        }
    }
    if (path->direction!='r' && canMoveTo(path,'r'))
    {
        if(fork()==0){
            path->direction = 'r';
        }
    }
    if (path->direction!='l' && canMoveTo(path,'l'))
    {
        if(fork()==0){
            path->direction = 'l';
        }
    }

    printf("La direccion actual es %c\n",path->direction);

    // puedo ir hacia las otras direcciones?
        //  hacer un fork por cada direccion y poner la nueva direccion 
    
    //puedo moverme ahcia mi direccion?
        //me muevo y llamo execute Fork
    //else
        //termino 

}




