#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mymalloc.h"

int main(){

    char *a = malloc(500);
    memset(a, 'A', 500);

    char *b = malloc(500);
    memset(b, 'B', 500);

    char *c = malloc(500);
    memset(c, 'C', 500);

    int overlap = 0; // 0 = overlap no found
    for(int i = 0; i < 500; i++){
        if(a[i] != 'A' || b[i] != 'B' || c[i] != 'C'){
            overlap = 1;
            break;
        }

    }
 
    if(overlap == 1){
        printf("Overlap Detected\n");
    }else {
        printf("No Overlap Detected\n");

    }

    free(a);
    free(b);
    free(c);
    
    return 0;
}
