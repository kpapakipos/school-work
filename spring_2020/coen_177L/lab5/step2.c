// Name: Keegan Papakipos
// Date: 5/4/20
// Title: Lab5 – Synchronization using semaphores, lock, and condition variables
// Description: This program has the same functionality as threadSync.c, but uses mutex locks.

// Thread Sychronization

#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <fcntl.h>

#define NTHREADS 10
pthread_t threads[NTHREADS];
pthread_mutex_t lock;

void* go(void* arg) { 
  pthread_mutex_lock(&lock); //entry section
  printf("Thread %d Entered Critical Section..\n", (int)arg); //critical section 
   sleep(1);
  pthread_mutex_unlock(&lock); //exit section 
  return (NULL);
}

int main() { 
pthread_mutex_init(&lock, NULL);
static int i;
for (i = 0; i < NTHREADS; i++)
   pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
for (i = 0; i < NTHREADS; i++) {
   pthread_join(threads[i],NULL);
   printf("\t\t\tThread %d returned \n", i);
   }
printf("Main thread done.\n");
pthread_mutex_destroy(&lock); // delete lock
return 0;
} 
