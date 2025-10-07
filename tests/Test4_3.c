#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mymalloc.h"

int main(){

    char *a2 = malloc(1000);
    char *q = a2;
    free(a2);
    free(q);
/*
output 
free: Inappropriate pointer (Test4_3.c:12)
*/
    return 0;
}
