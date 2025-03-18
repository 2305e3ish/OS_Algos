#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_NAME "myfifo"
#define BUFFER_SIZE 100

int main() {
    char read_msg[BUFFER_SIZE];

    // Create the FIFO if it doesn't exist
    if (mkfifo(FIFO_NAME, 0666) == -1) {
        perror("mkfifo");
        exit(1);
    }

    printf("Reader: Waiting for writer...\n");
    int fd = open(FIFO_NAME, O_RDONLY); // Open FIFO for reading
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    printf("Reader: Ready to receive messages. Type 'exit' to quit.\n");
    while (1) {
        // Read the message from the FIFO
        if (read(fd, read_msg, BUFFER_SIZE) == -1) {
            perror("read");
            break;
        }

        printf("Writer: %s\n", read_msg);

        // Exit if the writer sends "exit"
        if (strcmp(read_msg, "exit") == 0) {
            break;
        }
    }

    close(fd); // Close the FIFO
    printf("Reader: Conversation ended.\n");
    return 0;
}