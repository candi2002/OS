#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int start;
    int end;
    long long partial_sum;
} ThreadData;

void* calculate_partial_sum(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    data->partial_sum = 0;
    for (int i = data->start; i <= data->end; i++) {
        data->partial_sum += i;
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <numThreads> <n>\n", argv[0]);
        return 1;
    }

    int numThreads = atoi(argv[1]);
    int n = atoi(argv[2]);

    if (numThreads <= 0 || n <= 0) {
        printf("Number of threads and n must be positive integers.\n");
        return 1;
    }

    pthread_t threads[numThreads];
    ThreadData threadData[numThreads];

    int range = n / numThreads;
    long long total_sum = 0;

    for (int i = 0; i < numThreads; i++) {
        threadData[i].start = i * range + 1;
        threadData[i].end = (i == numThreads - 1) ? n : (i + 1) * range;
        pthread_create(&threads[i], NULL, calculate_partial_sum, &threadData[i]);
    }

    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
        total_sum += threadData[i].partial_sum;
    }

    printf("Multi-threaded Sum of 1 to %d = %lld\n", n, total_sum);
    return 0;
}
