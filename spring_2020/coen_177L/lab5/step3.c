// Name: Keegan Papakipos
// Date: 5/4/20
// Title: Lab5 – Synchronization using semaphores, lock, and condition variables
// Description: This program solves the producer-consumer problem using semaphores.

//Shared data: semaphore full, empty, mutex;
//pool of n buffers, each can hold one item
//mutex provides mutual exclusion to the buffer pool
//empty and full count the number of empty and full buffers
//Initially: full = 0, empty = n, mutex = 1

#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <fcntl.h>

#define n 4

pthread_t threads[2];
sem_t *full;
sem_t *empty;
sem_t *mutex;
int buffer[n];

void *prod(void *arg) {
    //Producer thread
	int item;
	int i = 0;
	printf("Producing items\n");
	do {
		item = rand() % 10;
		sem_wait(empty);
		sem_wait(mutex);
		printf("produced item %d\n", item);
		buffer[i % n] = item;
		sem_post(mutex);
		sem_post(full);
		i++;
		sleep(1);
	} while (1);
}

void *cons(void *arg) {
	//Consumer thread
	int item;
	int i = 0;
	printf("Consuming items\n");
	do { 
		sem_wait(full);
		sem_wait(mutex);
		item = buffer[i % n];
		buffer[i % n] = -1;
		sem_post(mutex);
		sem_post(empty);
		printf("consumed item %d\n", item);
		i++;
	} while (1);
}

int main() {
	int i;
	full = sem_open("full", O_CREAT, 0644, 0);
	empty = sem_open("empty", O_CREAT, 0644, n);
	mutex = sem_open("mutex", O_CREAT, 0644, 1);
	pthread_create(&threads[0], NULL, prod, NULL);
	pthread_create(&threads[1], NULL, cons, NULL);
	sleep(30);
	sem_unlink("full");
	sem_unlink("empty");
	sem_unlink("mutex");
	printf("main done\n");
}
