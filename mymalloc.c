#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

#define MEMLENGTH 4096

static union {
    char bytes[MEMLENGTH];
    double not_used; 
} heap;

typedef struct header {
        int size; // size of the chunk 
        int is_allocated; // if 0 empty if 1 full
} header; 

static int initialized = 0;
static header *head = NULL;
void leak_report();

void allocation(){
    if(!initialized){
        head = (header*) heap.bytes; // the first header 
        head -> size = MEMLENGTH - sizeof(header);  
        head -> is_allocated = 0;  
        initialized = 1;   
        atexit(leak_report);

    }
}

void * mymalloc(size_t size, char *file, int line){

    allocation();
    header *current = head;

   // making size multiple of 8
    if((size % 8) != 0){
        size = size + (8 - (size % 8));
    }

    while ((char*)current < heap.bytes + MEMLENGTH) {
        if((current -> is_allocated) == 0 && current -> size >= size){ // if the current chunk is empty and enough
            int old_size = current->size; // the size of free space
            current -> size = size;
            current -> is_allocated = 1; // allocate the heap
            header *temp = current; 
                // making the size left free if it is enough 
            if((old_size) > (size + sizeof(header))){
                header *next = (header *) ((char *)current + sizeof(header) + size); // from first bytes of the heap to next header by skipping header and allocated chunk
                next -> size = old_size - size - sizeof(header); // setting the rest of chunk free the size of previous free chunk - size of allocated - header
                next -> is_allocated = 0;
            }
            return (void*) ((char*)temp + sizeof(header));
        }
        current = (header *)((char *)current + (sizeof(header)) + current -> size);
    }

    fprintf(stderr, "malloc: Unable to allocate %zu bytes (%s:%d)\n", size, file, line);
    return NULL;
}

void myfree(void *ptr, char *file, int line){

    allocation();

    if(!ptr){
        return;
    }

    // if the pointer is outside the heap
    if ((char*)ptr < (heap.bytes + sizeof(header)) || (char*)ptr >= (heap.bytes + MEMLENGTH)) {

        fprintf(stderr, "free: Inappropriate pointer (%s:%d)\n", file, line);
        exit(2);
    }

    // if the pointer is not pointing to start of the chunk
    header *r = head;
    int is_in = 0;
    while((char*)r < heap.bytes + MEMLENGTH){
        if ((char*)r + sizeof(header) == (char*)ptr){
                is_in = 1;
                break;
        }
    r = (header *)((char*)r + sizeof(header) + r -> size);

    }
    if(!is_in){
        fprintf(stderr, "free: Inappropriate pointer (%s:%d)\n", file, line);
        exit(2);

    }

    // if the chunk is already free
    header *chunk = (header *)((char *) ptr - sizeof(header)); // getting the header of the given chunk

    if (chunk -> is_allocated == 0) {
        fprintf(stderr, "free: Inappropriate pointer (%s:%d)\n", file, line);
        exit(2);
    }

    chunk -> is_allocated = 0;

    // finding the previous header
    header *c = (header*) heap.bytes; 
    header *p = NULL;

    while((char*)c < (char*)chunk){
        p = c;
        c = (header *)((char *)p + sizeof(header) + p -> size );
    }

    if(p != NULL && p->is_allocated == 0){            
        p ->size += chunk -> size + sizeof(header);      
        chunk = p;        
    }
    header *next = (header *) ((char *)(chunk) + sizeof(header) + chunk -> size); // !!!!check if you are inside heap !!!!

    //
    while ((char*)next < heap.bytes + MEMLENGTH - sizeof(header) && next->is_allocated == 0) {

        if (((char *)next >= heap.bytes + MEMLENGTH)){
            break;
        }
        //int tempsize = next -> size;
        chunk -> size += sizeof(header) + next -> size;
        next = (header *) ((char *)(chunk) + sizeof(header) + chunk -> size);
            
    }

}


void leak_report(){

    header *h = head;

    int memory = 0;
    int chunks = 0;

    while((char*)h < heap.bytes + MEMLENGTH){

        if(h -> is_allocated == 1){
            memory += h -> size;
            chunks += 1;
        }
        h = (header *)((char *)h + sizeof(header) + h -> size );

    }
    if(chunks > 0){
        fprintf(stderr, "mymalloc: %d bytes leaked in %d objects\n", memory, chunks);
    }
   

}

