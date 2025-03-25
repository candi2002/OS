#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MSGKEY 0x1234 // Unique key for message queue
#define PERMS 0644    // Permissions

struct msgbuf {
    long mtype;        // Message type
    char mtext[200];   // Message content
};

void* send_messages(void* arg) {
    int msqid = *(int*)arg;
    struct msgbuf buf;
    buf.mtype = 1; // Type 1 for sending
    for (int i = 0; i < 5; i++) {
        sprintf(buf.mtext, "Message %d from sender", i + 1);
        if (msgsnd(msqid, &buf, strlen(buf.mtext) + 1, 0) == -1) {
            perror("msgsnd");
            exit(1);
        }
        printf("Sent: %s\n", buf.mtext);
        sleep(1); // Simulate delay
    }
    return NULL;
}

void* receive_messages(void* arg) {
    int msqid = *(int*)arg;
    struct msgbuf buf;
    while (1) {
        if (msgrcv(msqid, &buf, sizeof(buf.mtext), 1, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }
        printf("Received: %s\n", buf.mtext);
        if (strcmp(buf.mtext, "exit") == 0) break;
    }
    return NULL;
}

int main() {
    int msqid;
    pthread_t sender, receiver;

    // Create message queue
    if ((msqid = msgget(MSGKEY, PERMS | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
    }

    // Create threads for sending and receiving
    pthread_create(&sender, NULL, send_messages, &msqid);
    pthread_create(&receiver, NULL, receive_messages, &msqid);

    // Wait for threads to finish
    pthread_join(sender, NULL);
    pthread_join(receiver, NULL);

    // Destroy message queue
    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }

    return 0;
}
