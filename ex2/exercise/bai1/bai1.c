#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>

int main() {
    key_t key = ftok("shared_memory", 65);
    int shmid = shmget(key, 1024, 0666|IPC_CREAT);
    char *shared_data = (char*) shmat(shmid, (void*)0, 0);

    if (fork() == 0) {
        // Child Process 1: Read and process the first file
        printf("Child 1 is processing...\n");
        // Read File 1, compute average, write to shared_data
        strcpy(shared_data, "Child 1 Average");
    } else if (fork() == 0) {
        // Child Process 2: Read and process the second file
        printf("Child 2 is processing...\n");
        // Read File 2, compute average, write to shared_data
        strcat(shared_data, " | Child 2 Average");
    } else {
        // Parent Process: Wait for children, access shared memory
        wait(NULL);
        printf("Parent reading shared memory: %s\n", shared_data);
    }

    // Detach and destroy shared memory
    shmdt(shared_data);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
