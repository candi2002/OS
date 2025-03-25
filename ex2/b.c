#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
void* worker(void *param){
printf("Thread function is called! \n");
return 0;
}
int main() {
pthread_t tid1, tid2;
fork(); fork();
pthread_create(&tid1, NULL, worker, NULL);
pthread_create(&tid2, NULL, worker, NULL);
pthread_join(tid1, NULL);
pthread_join(tid2, NULL);
 
return 0;
}
