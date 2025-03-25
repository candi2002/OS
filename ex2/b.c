#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Thread function: worker */
void *worker(void *arg) {
printf("Worker thread executing: PID: %d!\n", getpid());
return NULL;
}

int main() {
pthread_t thread1, thread2;
 
pthread_create(&thread1, NULL, worker, NULL);// Create thread1 thread
pthread_create(&thread2, NULL, worker, NULL);
pthread_join(thread1, NULL);// Wait for thread1 to complete
pthread_join(thread2, NULL);// Wait for thread2 to complete

printf("Main thread executing!\n");
return 0;
}
