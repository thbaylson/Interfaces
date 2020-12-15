/**
 * Implementation of Malloc.h
 */

#include <stdio.h>
#include <stdlib.h>
#include "Malloc.h"

void* Malloc(size_t size){
    void *ptr = malloc(size);
    
    /*Check for errors in allocating memory*/
    if(!ptr){
        perror("Error allocating memory");
        exit(1);
    }

    return ptr;
}

void* Realloc(void* ptr, size_t size){
    ptr = realloc(ptr, size);

    /*Check for errors in reallocating memory*/
    if(!ptr){
        perror("Error REallocating memory");
        exit(1);
    }

    return ptr;
}
