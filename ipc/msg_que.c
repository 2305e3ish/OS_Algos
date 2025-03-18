#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>

#define BUFFER_SIZE 100

struct msg_buffer {
    long msg_type;
    char msg_text[BUFFER_SIZE];
};

int main() {
    pid_t pid;
    int msgid;
    key_t key;
    struct msg_buffer message;

    key = ftok("progfile", 65);
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child Process
        msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0);
        printf("Child process received: %s\n", message.msg_text);
        msgctl(msgid, IPC_RMID, NULL); // Remove the message queue
    } else { // Parent Process
        message.msg_type = 1;
        printf("Enter a message: ");
        fgets(message.msg_text, BUFFER_SIZE, stdin);
        msgsnd(msgid, &message, sizeof(message.msg_text), 0);
        wait(NULL); // Wait for the child process to finish
    }

    return 0;
}