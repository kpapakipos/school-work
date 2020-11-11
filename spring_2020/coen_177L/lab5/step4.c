// Name: Keegan Papakipos
// Date: 5/4/20
// Title: Lab5 – Synchronization using semaphores, lock, and condition variables
// Description: This program solves the producer-consumer problem using condition variables.

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>

#define n 4

pthread_t threads[2];
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int buffer[n];
int emptySlots;

void *prod(void *arg) {
    //Producer thread
    int item;
    int i = 0;
    printf("Producing items\n");
    do {
        item = rand() % 10;
    	pthread_mutex_lock(&mutex);
    	while (emptySlots == 0)
        	pthread_cond_wait(&empty, &mutex); 
		printf("produced item %d\n", item);
    	buffer[i % n] = item;
		emptySlots--;
    	pthread_cond_signal(&full);
	    pthread_mutex_unlock(&mutex);
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
		pthread_mutex_lock(&mutex);
    	while (emptySlots == n)
    		pthread_cond_wait(&full, &mutex);
    	item = buffer[i % n];
    	buffer[i % n] = -1;
		emptySlots++;
    	pthread_cond_signal(&empty);
    	pthread_mutex_unlock(&mutex);
	    printf("consumed item %d\n", item);
        i++;
    } while (1);
}

int main() {
    int i;
	emptySlots = n;
    pthread_create(&threads[0], NULL, prod, NULL);
    pthread_create(&threads[1], NULL, cons, NULL);
    sleep(30);
    printf("main done\n");
}

/*//Producer thread
do { 
    produce next item
    lock(mutex);
    while (buffer is full)
		condV.wait(empty, mutex);
    add the item to buffer
    condV.signal(full);
    unlock(mutex);
} while (1);

//Consumer thread
do { 
    lock(mutex)
    while (buffer is empty)
		condV.wait(full, mutex)
    remove next item from buffer
    condV.signal(empty);
    unlock(mutex);
    consume the item
} while (1);
*/
