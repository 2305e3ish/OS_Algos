#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define FIFO_NAME "myfifo"
#define BUFFER_SIZE 100

int main() {
    pid_t pid;
    char write_msg[BUFFER_SIZE], read_msg[BUFFER_SIZE];

    if (mkfifo(FIFO_NAME, 0666) == -1) {
        perror("mkfifo");
        exit(1);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) { // Child Process
        int fd = open(FIFO_NAME, O_RDONLY);
        read(fd, read_msg, BUFFER_SIZE);
        printf("Child process received: %s\n", read_msg);
        close(fd);
    } else { // Parent Process
        int fd = open(FIFO_NAME, O_WRONLY);
        printf("Enter a message: ");
        fgets(write_msg, BUFFER_SIZE, stdin);
        write(fd, write_msg, strlen(write_msg) + 1);
        close(fd);
        wait(NULL);
        unlink(FIFO_NAME);
    }
    return 0;
}