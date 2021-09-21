#include "../headers/Box.h"
#include <sys/mman.h>



Box* newBox(char type){
    //new
    Box* self = (Box*)malloc(sizeof(Box));
    
    //atributes
    self->up = false;
    self->down = false;
    self->right = false;
    self->down = false; 
    self->first = ' ';
    self->type = type;
    self->marked = false;
    
    return self;
}


Box* newSharedBox(char type){
    //new
    Box* self = (Box*)(mmap(NULL, sizeof(Box), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0)); 
    
    //atributes
    self->up = false;
    self->down = false;
    self->right = false;
    self->down = false; 
    self->first = ' ';
    self->type = type;
    self->marked = false;
    
    return self;
}





