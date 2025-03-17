#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main() {
    int fd[2];
    pid_t pid;
    char write_msg[] = "Hello from pipe";
    char read_msg[100];

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) { 
        close(fd[0]);
        write(fd[1], write_msg, strlen(write_msg) + 1);
        close(fd[1]);
    } else { 
        close(fd[1]);
        read(fd[0], read_msg, sizeof(read_msg));
        printf("Child read from pipe: %s\n", read_msg);
        close(fd[0]);
    }
    return 0;
}
