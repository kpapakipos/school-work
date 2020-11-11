// Name: Keegan Papakipos 
// Date: Tuesday (the day you have lab) 
// Title: Lab3 – Pthreads and IPC- Pipes
// Description: This program fixes the bug in step 6. Threads now do not
// repeat values of i between different threads.

/**************************
*       COEN177: Threads  *
**************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *go(void *);
#define NTHREADS 10
pthread_t threads[NTHREADS];
int i_arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int main() {
    int i;
    for (i = 0; i < NTHREADS; i++)  
        pthread_create(&threads[i], NULL, go, &i_arr[i]);
    for (i = 0; i < NTHREADS; i++) {
	printf("Thread %d returned\n", i);
        pthread_join(threads[i],NULL);
    }
    printf("Main thread done.\n");
    return 0;
}
void *go(void *arg) {
 printf("Hello from thread %d with iteration %d\n",  (int)pthread_self(), *(int *)arg);
 return 0;
}


