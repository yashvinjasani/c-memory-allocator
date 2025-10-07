#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mymalloc.h"

int main(){

    char *a1 = malloc(1000);
    char *a2 = malloc(1000);
    char *a3 = malloc(1000);
    char *a4 = malloc(1000);
    // not heap is about full

    free(a1);
    free(a2);
    // now if both chunks were coalesced we can put another chunk which is big enough 

    char *a5 = malloc(2000);
    free(a5);
    free(a3);
    free(a4);

    return 0;
}