#include "../headers/Path.h"
#include <pthread.h>
#include <sys/wait.h>

Box** matrix;
int rows;
int cols;
pthread_mutex_t *mutex; 

void setVariables(Box** matrix_i, int rows_i, int cols_i, pthread_mutex_t *_mutex){
    matrix = matrix_i;
    rows = rows_i;
    cols = cols_i;
    mutex = _mutex;
}


//mutex
bool canMoveTo(Path* path, char direction){

    switch (direction)
    {
        case 'u':
            if((path->i-1)>=0){
                Box* box = &(matrix[path->i-1][path->j]);

                if (box->type!='*' && !(box->up))
                {
                    return true;
                }
            }
            break;
        
        case 'd':
            if((path->i+1)<rows){
                Box* box = &(matrix[path->i+1][path->j]);

                if (box->type!='*' && !(box->down))
                {
                    return true;
                }
            }
            break;
        
        case 'l':
            if((path->j-1)>=0){
                Box* box = &(matrix[path->i][path->j-1]);

                if (box->type!='*' && !(box->left))
                {
                    return true;
                }
            }
            break;
        
        case 'r':
            if((path->j+1)<cols){
                Box* box = &(matrix[path->i][path->j+1]);

                if (box->type!='*' && !(box->right))
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

bool win(Path* path){
    return matrix[path->i][path->j].type == '/';
}

void *executeThread(void* path_i){
    
    Path* path = (Path*)path_i;
    
    bool won = win(path);

    if (won)
    {
        path->win = true;
        path->printFinish(path);
        return;
    }
    
    usleep(300000);


    pthread_t threads[4] = {0,0,0,0};


    if (!won && path->direction!='u' && path->direction!='d')
    {
        pthread_mutex_lock(mutex);
        if (canMoveTo(path,'u'))
        {
            pthread_t t1;
            Path* newPath = clonePath(path);
            move(newPath,'u');
            pthread_mutex_unlock(mutex);
            pthread_create(&t1, NULL, &executeThread, newPath);
            threads[0]=t1;
        }
        else
        {
            pthread_mutex_unlock(mutex);
        }
        
    }
    if (!won && path->direction!='d' && path->direction!='u')
    {
        pthread_mutex_lock(mutex);
        if (canMoveTo(path,'d'))
        {
            pthread_t t2;
            Path* newPath = clonePath(path);
            move(newPath,'d');
            pthread_mutex_unlock(mutex);
            pthread_create(&t2, NULL, &executeThread, newPath);           
            threads[1]=t2;
        }
        else
        {
            pthread_mutex_unlock(mutex);
        }
        
    }
    if (!won && path->direction!='r' && path->direction!='l')
    {
        pthread_mutex_lock(mutex);
        if (canMoveTo(path,'r'))
        {
            pthread_t t3;
            Path* newPath = clonePath(path);
            move(newPath,'r');
            pthread_mutex_unlock(mutex);
            pthread_create(&t3, NULL, &executeThread, newPath);
            threads[2]=t3;
        }
        else
        {
            pthread_mutex_unlock(mutex);
        }
    }
    if (!won && path->direction!='l' && path->direction!='r')
    {
        pthread_mutex_lock(mutex);
        if (canMoveTo(path,'l'))
        {
            pthread_t t4;   
            Path* newPath = clonePath(path);
            move(newPath,'l');
            pthread_mutex_unlock(mutex);
            pthread_create(&t4, NULL, &executeThread, newPath);
            threads[3]=t4; 
        }
        else
        {
            pthread_mutex_unlock(mutex);
        }
    }


    pthread_mutex_lock(mutex);
    if(!won && canMoveTo(path,path->direction)){
        move(path,path->direction);
        pthread_mutex_unlock(mutex);
        executeThread(path);
    }
    else
    {
        path->printFinish(path);
        pthread_mutex_unlock(mutex);
    }
    
    for (int i = 0; i <4; i++)
    {
        if (threads[i] != 0)
        {
            pthread_join(threads[i],NULL);
        }
        
    }



}

void *executeFork(void* path_i){
    

    Path* path = (Path*)path_i;

    int forks[] = {0,0,0,0};
    
    bool won = win(path);

    if (won)
    {
        path->win = true;
        path->printFinish(path);
        return;
    }
    
    usleep(300000);



    if (path->direction!='u' && path->direction!='d' && canMoveTo(path,'u'))
    {
        
        int forkId = fork();
        if (forkId==0)
        {
            move(path,'u');
            executeFork(path);
            return;
        }
        else{
            forks [0]=forkId;
        }
        
    }

    if (path->direction!='u' && path->direction!='d' && canMoveTo(path,'d'))
    {
        int forkId = fork();
        if (forkId==0)
        {
            move(path,'d');
            executeFork(path);
            return;
        }
        else{
            forks [1]=forkId;
        }
        
    }


    if (path->direction!='r' && path->direction!='l' && canMoveTo(path,'l'))
    {
        int forkId = fork();
        if (forkId==0)
        {
            move(path,'l');
            executeFork(path);
            return;
        }
        else{
            forks [2]=forkId;
        }
                
    }


    if (path->direction!='r' && path->direction!='l' && canMoveTo(path,'r'))
    {
        int forkId = fork();
        if (forkId==0)
        {
            move(path,'r');
            executeFork(path);
            return;
        }
        else{
            forks [3]=forkId;
        }      
    }
    

    if(canMoveTo(path,path->direction)){
        move(path,path->direction);
        executeFork(path);
    }
    else{
        path->printFinish(path);
    }

    for (int i = 0; i < 4; i++)
    {   int status = 0;
        if (forks[i]!=0)
        {
            waitpid(forks[i],&status,0);

        }
        
    }


}

