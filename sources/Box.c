#include "../headers/Box.h"


Box* newBox(char type){
    //new
    Box* self = (Box*)malloc(sizeof(Box));
    
    //atributes
    self->up = false;
    self->down = false;
    self->right = false;
    self->down = false; 

    self->type = type;
    self->marked = false;
    
    return self;
}





