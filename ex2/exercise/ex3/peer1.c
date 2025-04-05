#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MSG_KEY_SEND 0x123 // A → B
#define MSG_KEY_RECV 0x456 // B → A
#define PERMS 0644

struct my_msgbuf {
    long mtype;
    char mtext[200];
};

void* sender_thread(void* arg) {
    int msqid = msgget(MSG_KEY_SEND, PERMS | IPC_CREAT);
    struct my_msgbuf buf;
    buf.mtype = 1;

    printf("[A] Gửi tin nhắn (nhập và Enter):\n");
    while (fgets(buf.mtext, sizeof buf.mtext, stdin)) {
        size_t len = strlen(buf.mtext);
        if (buf.mtext[len - 1] == '\n') buf.mtext[len - 1] = '\0';
        msgsnd(msqid, &buf, strlen(buf.mtext) + 1, 0);
        if (strcmp(buf.mtext, "end") == 0) break;
    }
    return NULL;
}

void* receiver_thread(void* arg) {
    int msqid = msgget(MSG_KEY_RECV, PERMS | IPC_CREAT);
    struct my_msgbuf buf;

    while (1) {
        if (msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }
        if (strcmp(buf.mtext, "end") == 0) break;
        printf("[A] Nhận từ B: %s\n", buf.mtext);
    }
    return NULL;
}

int main() {
    pthread_t sender, receiver;
    pthread_create(&sender, NULL, sender_thread, NULL);
    pthread_create(&receiver, NULL, receiver_thread, NULL);

    pthread_join(sender, NULL);
    pthread_join(receiver, NULL);

    msgctl(msgget(MSG_KEY_SEND, 0), IPC_RMID, NULL);
    msgctl(msgget(MSG_KEY_RECV, 0), IPC_RMID, NULL);

    printf("[A] Kết thúc giao tiếp.\n");
    return 0;
}
