#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>

#define FILE1 "movie-100k_1.txt"
#define FILE2 "movie-100k_2.txt"

void calculate_average(const char* filename, char* shared_data){
    FILE* file = fopen(filename, "r");
    if(file == NULL){
        perror("ERROR");
        exit(EXIT_FAILURE);
    }

    int movie_id, use_id, rating, timeStamp;
    int total_rating = 0, count = 0;

    while (fscanf(file, ""%d\t%d\t%d\t%d", &user_id, &movie_id, &rating, &timestamp) != EOF"){
        count++;
        total_rating += rating;
    }
    fclose(file);

    double average = (double)total_rating/count;
    sprintf(shared_data, "File: %s, Average Rating: %.2f", filename, average);
}
int main() {
    key_t key = ftok("share_memory", 15);
    int shmid = shmget(key, 1024, 0666|IPC_CREATE);
    char *share_data = (char*) shmat(shmid, (void*)0,0);
    
}
