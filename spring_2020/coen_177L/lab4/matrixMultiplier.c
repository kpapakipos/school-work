// Name: Keegan Papakipos 
// Date: 4/27/20 
// Title: Lab4 – developing multi-threaded applications
// Description: This program uses multithreading to multiply two randomly-generated
// matrices together. It is for step 3 of the lab.

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define N 1024
#define M 1024
#define L 1024

void *go(void *);
pthread_t tid[N];
double matrixA[N][M];
double matrixB[M][L];
double matrixC[N][L];
int iVals[N];

int main(void) {
    int i;
    for(i = 0; i < N; i++)
        iVals[i] = i;

    srand(time(NULL));
    int j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
	    int x = rand() % 10;
//	    printf("%.2f %d %d\n", x, i, j);
            matrixA[i][j] = x;
	}
    }
    for (i = 0; i < M; i++)
        for (j = 0; j < L; j++)
            matrixB[i][j] = rand() % 10;
/*    for (i=0;i<N;i++) {
        for (j=0;j<M;j++) {
            printf("%.2f ", matrixA[i][j]);
        }
	printf("\n");
    }
    printf("\n");
    for (i=0;i<M;i++) {
        for (j=0;j<L;j++) {
            printf("%.2f ", matrixB[i][j]);
        }
	printf("\n");
    }*/
    for (i = 0; i < N; i++)
        pthread_create(&tid[i], NULL, go, &iVals[i]);
    for (i = 0; i < N; i++) {
        pthread_join(tid[i],NULL);
    }
    printf("\n");
    for (i=0;i<N;i++) {
	for (j=0;j<L;j++) {
	    printf("%.2f ", matrixC[i][j]);
	}
        printf("\n");
    }
}

void *go(void *i) {
    int j;
    int k;
//    printf("L: %d\n", L);
    for (j = 0; j < L; j++) {
        double temp = 0;
        for (k = 0; k < M; k++) {
//	    printf("%d,%d,%d,%.2f,%.2f\n", *(int*)i, j, k, matrixA[*(int*)i][k], matrixB[k][j]);
            temp += matrixA[*(int*)i][k] * matrixB[k][j];
        }
	matrixC[*(int*)i][j] = temp;
    }
}
