#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mymalloc.h"

int main(){

    char *a = malloc(1000);
    int x;
    free(&x);
/*
output: 
free: Inappropriate pointer (Test4_1.c:11)
mymalloc: 1000 bytes leaked in 1 objects
*/

    return 0;
}
