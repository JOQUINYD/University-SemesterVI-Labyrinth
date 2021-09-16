
#include "../headers/Path.h"



void printFinish(Path* self){
    if (self->win)
    {
        printf("Finalizó exitosamente con %d especios recorridos.\n\n",self->amount);
    }
    else{
        printf("Finalizó sin éxito con %d especios recorridos.\n\n",self->amount);
    }
}



Path* newPath(){
    //new
    Path* self = (Path*)malloc(sizeof(Path));
    
    //atributes
    self->i = 0;
    self->j = 0;
    self->direction = 'd';
    self->amount = 1;
    self->win = false;

    self->printFinish = printFinish;
    
    return self;
}


Path* clonePath(Path* old){
    //new
    Path* self = (Path*)malloc(sizeof(Path));
    
    //atributes
    self->i = old->i;
    self->j = old->j;
    self->direction = old->direction;
    self->amount = old->amount;
    self->win = false;
    
    self->printFinish = printFinish;

    return self;
}


