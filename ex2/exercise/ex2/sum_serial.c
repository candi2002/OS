#include <stdio.h>
#include <stdlib.h>

long long sum_serial(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    return sum;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]); // Convert input to integer
    long long result = sum_serial(n);
    printf("Serial Sum of 1 to %d = %lld\n", n, result);
    return 0;
}
