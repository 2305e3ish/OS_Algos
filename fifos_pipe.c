#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_NAME "myfifo"
#define MSG_SIZE 100

int main() {
    int fd;
    char msg[MSG_SIZE];

    if (mkfifo(FIFO_NAME, 0666) == -1) {
        perror("mkfifo");
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) { 
        fd = open(FIFO_NAME, O_WRONLY);
        char *write_msg = "Hello from FIFO";
        write(fd, write_msg, strlen(write_msg) + 1);
        close(fd);
    } else { 
        fd = open(FIFO_NAME, O_RDONLY);
        read(fd, msg, MSG_SIZE);
        printf("Child read from FIFO: %s\n", msg);
        close(fd);
    }

    unlink(FIFO_NAME);
    return 0;
}
