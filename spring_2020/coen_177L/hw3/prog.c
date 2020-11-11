#include <stdio.h>
#include <unistd.h>

int main (int argc, char ** argv) {
    int child = fork();
    int x = 5;
    printf("x created\n");

    if (child == 0) {
        x += 5;
        printf("x added 5\n");
    } else {
        child = fork();
        x += 10;
        printf("x added 10\n");
        if (child) {
            x += 5;
            printf("x added 5\n");
        }
    }
}