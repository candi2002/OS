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

    // Tạo file (nếu chưa tồn tại) và thiết lập kích thước
    fd = open(FILEPATH, O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // Tăng kích thước file lên FILESIZE byte
    if (ftruncate(fd, FILESIZE) == -1) {
        perror("ftruncate");
        close(fd);
        exit(1);
    }

    // Map file vào bộ nhớ
    map = mmap(NULL, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
        perror("mmap");
        close(fd);
        exit(1);
    }

    // Ghi dữ liệu vào vùng nhớ
    const char *message = "Hello from writer via mmap!";
    memcpy(map, message, strlen(message));

    printf("[Writer] Wrote message: %s\n", message);

    // Duy trì để reader có thể đọc
    sleep(10);

    // Unmap và đóng file
    munmap(map, FILESIZE);
    close(fd);

    return 0;
}
