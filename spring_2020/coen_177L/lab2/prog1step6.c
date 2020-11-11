# Name: Keegan Papakipos
# Date: Turned in 4/20. This assignment was due 4/13. Labs on Tuesday.
# Title: Lab2 – Programming in C and use of Systems Calls
# Description: This program creates a thread and prints out the numbers 0-99, 
# like the program from step 2 did.

/*Sample C program for Lab assignment 1*/
#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */
#include <pthread.h>    /* pthread_create and pthread_t */
/* main function with command-line arguments to pass */

void *threadFunc(void *arg) {
    // Child process
    int i;
    for (i=0;i<100;i++) {
        printf("thread %d\n",i);
        usleep(*(int*)arg);
    }
}

int main(int argc, char *argv[]) {
    pthread_t  ptid;
    int i, n = atoi(argv[1]); // n microseconds to input from keyboard for delay
    printf("\n Before creating threads.\n");
    pthread_create(&ptid, NULL, threadFunc, &n);
    // Parent process
    for (i=0;i<100;i++) {
        printf("\t \t \t Parent Process %d \n",i);
        usleep(n);
    }    
    return 0;
}
