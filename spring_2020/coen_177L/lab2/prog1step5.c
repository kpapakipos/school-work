# Name: Keegan Papakipos
# Date: Turned in 4/20. This assignment was due 4/13. Labs on Tuesday.
# Title: Lab2 – Programming in C and use of Systems Calls
# Description: This program creates 7 processes with 0 or 2 children, and prints
# out a line for each process.

/*Sample C program for Lab assignment 1*/
#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */
/* main function with command-line arguments to pass */
int main(int argc, char *argv[]) {
    pid_t  pid1, pid2, pid3, pid4, pid5, pid6;
    int i;
    printf("Before forking.\n");
    pid1 = fork();
    if (pid1 == -1) {
        fprintf(stderr, "can't fork, error %d\n", errno);
    }
    if (pid1){
        // Original process
        printf("Original process\n");
	pid2 = fork();
	if (pid2 == -1) {
            fprintf(stderr, "can't fork, error %d\n", errno);
        }
        if (pid2){
	    // Original process
        }  
        else{
	    // Child 2 of original
            printf("Child 2\n");
	    pid5 = fork();
            if (pid5 == -1) {
                fprintf(stderr, "can't fork, error %d\n", errno);
            }
	    if (pid5){
                // Child 2 of original
                pid6 = fork();
                if (pid6 == -1) {
                    fprintf(stderr, "can't fork, error %d\n", errno);
                }
                if (pid6){
                    // Child 2 of original
                }
                else{
                    // Child 2 of child 2
                    printf("Grandchild 4\n");
                }
	    }
	    else{
                // Child 1 of child 2
                printf("Grandchild 3\n");
            }
        }
    }    
    else{          
	// Child 1 of original
        pid3 = fork();
   	if (pid3 == -1) {
            fprintf(stderr, "can't fork, error %d\n", errno);
        }
    	if (pid3){
	    // Child 1 of original
            printf("Child 1\n");
            pid4 = fork();
	    if (pid4 == -1) {
                fprintf(stderr, "can't fork, error %d\n", errno);
            }
	    if (pid4){
                // Child 1 of original
            }
	    else{
                // Child 2 of child 1
                printf("Grandchild 2\n");
            }
    	}  
    	else{
	    // Child 1 of child 1
            printf("Grandchild 1\n");
            
        }    
    }    
    return 0;
}
