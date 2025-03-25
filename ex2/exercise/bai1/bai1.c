#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <string.h>

#define FILE1 "movie-100k_1.txt"
#define FILE2 "movie-100k_2.txt"

void calculate_average(const char* filename, char* shared_data, int* result){
    FILE* file = fopen(filename, "r");
    if(file == NULL){
        perror("ERROR");
        exit(EXIT_FAILURE);
    }

    int movie_id, user_id, rating, timeStamp;
    int total_rating = 0, count = 0;

    while (fscanf(file, "%d\t%d\t%d\t%d", &user_id, &movie_id, &rating, &timeStamp) != EOF) {
        count++;
        total_rating += rating;
    }
    fclose(file);

    double average = (double)total_rating/count;
    sprintf(shared_data, "File: %s, Average Rating: %.2f", filename, average);
    result[0] = count;
    result[1] = total_rating;
}

int main() {
    key_t key = ftok("share_memory", 65);
    int shmid = shmget(key, 2048, 0666|IPC_CREAT);
    char *shared_data = (char*) shmat(shmid, (void*)0,0);
    int *result = (int*)(shared_data + 1024);
    
    if(fork()==0){
        //Child 1
        calculate_average(FILE1, shared_data,result);
    }
    else if(fork() == 0){
        //Child 2
        char* child_data = shared_data + 512;
        int* child2_result = result + 2;
        calculate_average(FILE2, child_data,child2_result);
    }
    else{
        //Parent
        wait(NULL);
        wait(NULL);
        printf("Parent reading shared memory:\n");
        printf("%s\n", shared_data);
        printf("Count: %d, Total Rating: %d\n", int_data[0], int_data[1]);
        printf("%s\n", shared_data + 512);
        printf("Count: %d, Total Rating: %d\n", int_data[2], int_data[3]);
        printf("Both files, Average Rating:  %d + %d \: %d + %d = %.2f\n", 
        int_data[0], int_data[1], FILE2, int_data[2], int_data[3], 
        ((double)(int_data[1] + int_data[3])) / (int_data[0] + int_data[2]));

    }

    // Detach and destroy shared memory
    shmdt(shared_data);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
