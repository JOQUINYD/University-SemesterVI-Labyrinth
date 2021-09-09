
#include "../headers/Path.h"


Path* newPath(int i, int j, char direction, int amount){
    //new
    Path* self = (Path*)malloc(sizeof(Path));
    
    //atributes
    self->i = i;
    self->j = j;
    self->direction = direction;
    self->amount = amount;
    self->done = false;
    
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
    self->done = false;
    
    return self;
}


