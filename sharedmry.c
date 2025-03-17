#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
int main() {
    key_t key = ftok("shmfile", 65);
    int shmid;
    char *str;

    shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid > 0) { 
        str = (char*) shmat(shmid, (void*)0, 0);
        strcpy(str, "Hello from shared memory");
        printf("Parent wrote to shared memory: %s\n", str);
        sleep(2);
        shmdt(str);
        shmctl(shmid, IPC_RMID, NULL);
    } else { 
        sleep(1);
        str = (char*) shmat(shmid, (void*)0, 0);
        printf("Child read from shared memory: %s\n", str);
        shmdt(str);
    }
    return 0;
}
