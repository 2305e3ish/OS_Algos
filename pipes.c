#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 100

int main() {
    int fd[2];
    pid_t pid;
    char write_msg[BUFFER_SIZE];
    char read_msg[BUFFER_SIZE];

    if (pipe(fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) { // Child Process
        close(fd[1]); // Close write end
        read(fd[0], read_msg, BUFFER_SIZE);
        printf("Child process received: %s\n", read_msg);
        close(fd[0]); // Close read end
    } else { // Parent Process
        close(fd[0]); // Close read end
        printf("Enter a message: ");
        fgets(write_msg, BUFFER_SIZE, stdin);
        write(fd[1], write_msg, strlen(write_msg) + 1);
        close(fd[1]); // Close write end
        wait(NULL); // Wait for child process
    }
    return 0;
}