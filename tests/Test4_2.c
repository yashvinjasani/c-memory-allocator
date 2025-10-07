#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mymalloc.h"

int main(){

    int *a1 = malloc(sizeof(int) * 2);
    free(a1 + 1);
/*
output 
free: Inappropriate pointer (Test4_2.c:10)
mymalloc: 8 bytes leaked in 1 objects
*/

    return 0;
}
