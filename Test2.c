#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mymalloc.h"

int main(){

    char *p = malloc(4000);
    free(p);

    char *p2 = malloc(2000); // if free deallocated memory this would run, if not our heap won't be able to 
                             // provide another chunk of 2000 bytes because limit is 4098.
    free(p2);
    return 0;
}