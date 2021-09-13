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


void *executeThread(void* path_i){
    //lo llamo con path* en lugar de coid* en los subthreads

    Path* path = (Path*)path_i;
    usleep(500000);

    pthread_t threads[4] = {0,0,0,0};



    if (path->direction!='u' && path->direction!='d'&& canMoveTo(path,'u'))
    {
        pthread_t t1;
        Path* newPath = clonePath(path);
        move(newPath,'u');
        pthread_create(&t1, NULL, &executeThread, newPath);
        threads[0]=t1;
    }
    if (path->direction!='d' && path->direction!='u'&& canMoveTo(path,'d'))
    {
        pthread_t t2;
        Path* newPath = clonePath(path);
        move(newPath,'d');
        pthread_create(&t2, NULL, &executeThread, newPath);           
        threads[1]=t2;
    }
    if (path->direction!='r' && path->direction!='l' && canMoveTo(path,'r'))
    {
        pthread_t t3;
        
        Path* newPath = clonePath(path);
        move(newPath,'r');
        pthread_create(&t3, NULL, &executeThread, newPath);
        threads[2]=t3;
    }
    if (path->direction!='l' && path->direction!='r' && canMoveTo(path,'l'))
    {
        pthread_t t4;   

        Path* newPath = clonePath(path);
        move(newPath,'l');
        pthread_create(&t4, NULL, &executeThread, newPath);
        threads[3]=t4; 
    }



    if(canMoveTo(path,path->direction)){
        move(path,path->direction);
        executeThread(path);
    }


    for (int i = 0; i <4; i++)
    {
        if (threads[i] != 0)
        {
            pthread_join(threads[i],NULL);
        }
        
    }

}

void executeFork(void* path_i){

    Path* path = (Path*)path_i;
    usleep(500000);

    int father = 1;
    int childIds[4] = {0,0,0,0};

    if (father!=0 && path->direction!='u' && path->direction!='d'&& canMoveTo(path,'u'))
    {
        father = fork();
        if (father==0)
        {
            path->direction = 'u';
        }
        else{
            childIds[0] = father;
        }
        
    }
    if (father!=0 && path->direction!='d' && path->direction!='u'&& canMoveTo(path,'d'))
    {
        father = fork();
        if (father==0)
        {
            path->direction = 'd';
        }
        else{
            childIds[1] = father;
        }
    }
    if (father!=0 && path->direction!='r' && path->direction!='l' && canMoveTo(path,'r'))
    {
        father = fork();
        if (father==0)
        {
            path->direction = 'r';
        }
        else{
            childIds[2] = father;
        }
       
    }
    if (father!=0 && path->direction!='l' && path->direction!='r' && canMoveTo(path,'l'))
    {
        father = fork();
        if (father==0)
        {
            path->direction = 'l';
        }   
        else{
            childIds[3] = father;
        }
    }

    if(canMoveTo(path,path->direction)){
        move(path,path->direction);
        executeFork(path);
    }

    for (int i = 0; i < 4; i++)
    {
        if (childIds[i]!=0)
        {
            waitpid(childIds[i]);
        }
        
    }
    
}




