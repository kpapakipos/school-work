// Name: Keegan Papakipos 
// Date: Tuesday 4/27/20
// Title: Lab4- developing multi-thread applications
// Description: This program is the given example thread program for the lab.
// It spawns 20 threads that print a greeting, then return and print another message.
// Finally it prints Main thread done. 

/**************************************************************
*	threadHello.c - simple multi-threaded program.            *
*   compile with: >gcc -lp threadHello.c -o threadHello       *                                              *
**************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define NTHREADS 20

void *go(void *);
pthread_t threads[NTHREADS];

int main() {
    static int i;
    for (i = 0; i < NTHREADS; i++)  
        pthread_create(&threads[i], NULL, go, &i);
    for (i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i],NULL);
        printf("Thread %d returned \n", i);
    }
    printf("Main thread done.\n");
}
void *go(void *arg) {
    printf("Hello from thread %d with thread ID %d \n", *(int *)arg, (int)pthread_self());
    return (NULL);
}

