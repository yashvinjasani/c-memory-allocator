#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mymalloc.h"

int main(){

    
 
    char *a1 = malloc(500);
    char *a2 = malloc(1500); // we are not going to free this chunk

    free(a1);



/*  output:
    mymalloc: 1504 bytes leaked in 1 objects
    (because it is multiple of 8)
*/

    return 0;
}
