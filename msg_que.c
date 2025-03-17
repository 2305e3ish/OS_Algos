#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key;
    int msgid;
    key = ftok("progfile", 65);

    msgid = msgget(key, 0666 | IPC_CREAT);
    if(msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    
    if (pid > 0) { 
        struct msg_buffer message;
        message.msg_type = 1;
        strcpy(message.msg_text, "Hello from message queue");
        msgsnd(msgid, &message, sizeof(message.msg_text), 0);
        printf("Parent: Message sent\n");
    } else { 
        struct msg_buffer message;
        msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0);
        printf("Child received: %s\n", message.msg_text);
    }
    
    if (pid > 0) {
        sleep(1);
        msgctl(msgid, IPC_RMID, NULL);
    }
    return 0;
}
