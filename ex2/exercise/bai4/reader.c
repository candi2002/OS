#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

#define FILEPATH "shared_mem.dat"
#define FILESIZE 1024

int main() {
    int fd;
    char *map;

    // Mở file đã được writer tạo
    fd = open(FILEPATH, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // Map file vào vùng nhớ để đọc
    map = mmap(NULL, FILESIZE, PROT_READ, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
        perror("mmap");
        close(fd);
        exit(1);
    }

    // In nội dung
    printf("[Reader] Read message: %s\n", map);

    // Unmap và đóng file
    munmap(map, FILESIZE);
    close(fd);

    return 0;
}
