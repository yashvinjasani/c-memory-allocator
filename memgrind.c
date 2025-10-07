#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "mymalloc.h"

// for linkedlist
typedef struct Node {
    int value;
    struct Node *next;
}Node;

// for binary tree
typedef struct Tree {
    int value;
    struct Tree *right;
    struct Tree *left;
}Tree;

void freeTree(Tree *root){
    if(!root){
        return;
    }
    freeTree(root -> left);
    freeTree(root -> right);
    free(root);
}

int main(){

    // The first test
    // 1. malloc() and immediately free() a 1-byte object, 120 times.

    struct timeval start, end;
    long seconds, useconds;

    gettimeofday(&start, NULL);


    for(int t = 0; t < 50; t++){
        for(int i = 0; i < 120; i++){
            char *a = malloc(1);
            if(a == NULL){
                fprintf(stderr, "Memory allocation failed");
                continue;

            }
            free(a);
        }
    }


    // second test
    // Use malloc() to get 120 1-byte objects, storing the pointers in an array, then use free() to
    // deallocate the chunks.

    gettimeofday(&end, NULL);
    seconds = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;
    double time = (seconds * 1000000.0 + useconds) / 1000000.0;

    double avg_time = time/50;

    printf("The average time for first workload is %1.8f seconds.\n", avg_time);

    gettimeofday(&start, NULL);
    for(int t = 0; t < 50; t++){

        char *p[120];
        for(int i = 0; i < 120; i++){

            p[i] = malloc(1);
            if(p[i] == NULL){
                fprintf(stderr, "Memory allocation failed");
                continue;

            }            

        }
        for(int i = 0; i < 120; i++){
                free(p[i]);
        }
    }

    // Third test
    /*
    Create an array of 120 pointers. Repeatedly make a random choice between (a) allocating a
    1-byte object and adding the pointer to the array and (b) deallocating a random previously
    allocated object (if any). Once 120 allocations have been performed, deallocate all remaining
    objects.
    */

    gettimeofday(&end, NULL);
    seconds = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;
    double time2 = (seconds * 1000000.0 + useconds) / 1000000.0;

    double avg_time2 = time2 / 50;

    printf("The average time for second workload is %1.8f seconds.\n", avg_time2);



    gettimeofday(&start, NULL);

    for(int t = 0; t < 50; t++){

        char *q[120];
        int alreay_free[120] = {0};

        int up = 3;
        int low = 0;

        for(int i = 0; i < 120; i++){

            q[i] = malloc(1);

            if(i == up){ 
                
                for(int j = low; j < i; j++){
                    int min = 0;
                    int max = up;
                    int random = (rand() % (max - min + 1)) + min;

                    if(alreay_free[random] == 0){// check if the current chunk is already free
                        free(q[random]);
                        alreay_free[random] = 1; // mark the index which is free
                    }
                }

                // pick any number between 1 and 4 and after that number of iteration, we will free the random chunks
                int min = 1;
                int max = 4;
                int random2 = (rand() % (max - min + 1)) + min;

                low = up; 
                up += random2;
                
            }

        }


        // freeing rest pointers 
        for(int i = 0; i < 120; i++){

            if(alreay_free[i] == 0){
                free(q[i]);
            }
        }
    }
    gettimeofday(&end, NULL);
    seconds = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;
    double time3 = (seconds * 1000000.0 + useconds) / 1000000.0;

    double avg_time3 = time3 / 50;

    printf("The average time for second workload is %1.8f seconds.\n", avg_time3);


    // Fourth test
    // make a linked list of 100 nodes and allocate 16 bytes to every node, and free them.


    gettimeofday(&start, NULL);

    for(int j = 0; j < 50; j++){

        Node *head = NULL;
       
        //making linked list 100 times size = 16 bytes every node contains value 10
        for (int i = 0; i < 100; i++) {
            Node* node = (Node*)malloc(sizeof(Node));
            node -> value = 10;
            node -> next = head;
            head = node;

        }

        while(head != NULL){
            Node *next = head -> next;
            free(head);
            head = next;
        }

    }
    gettimeofday(&end, NULL);
    seconds = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;
    double time4 = (seconds * 1000000.0 + useconds) / 1000000.0;

    double avg_time4 = time4/50;

    printf("The average time for fourth workload is %1.8f seconds.\n", avg_time4);


    // Fifth test
    // Making a binary tree with 100 nodes total, including left and right child for every node and free all 
    // nodes 

    gettimeofday(&start, NULL);

    for(int j = 0; j < 50; j++){
        Tree* nodes[100];

        for(int i = 0; i < 100; i++){
            nodes[i] = malloc(sizeof(Tree));
            nodes[i]  -> value = i;
            nodes[i] -> left = NULL;
            nodes[i] -> right = NULL;
        }
        for(int i = 0; i < 100; i++){

            int left = (i * 2) + 1; // right child 
            int right = (i * 2) + 2; // left child

            if(left < 100){
                nodes[i]  -> left = nodes[left];
            }
            if(right < 100){
                nodes[i]  -> right = nodes[right];
            }

        }
        freeTree(nodes[0]);
    }
    gettimeofday(&end, NULL);
    seconds = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;
    double time5 = (seconds * 1000000.0 + useconds) / 1000000.0;

    double avg_time5 = time5/50;

    printf("The average time for fifth workload is %1.8f seconds.\n", avg_time5);

    return 0;

}



/*
gcc -o memgrind memgrind.c mymalloc.c
./memgrind


gcc -o Test1 Test1.c mymalloc.c

*/
