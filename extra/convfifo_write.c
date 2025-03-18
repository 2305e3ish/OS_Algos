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
    int fd;
    char write_msg[BUFFER_SIZE];
    char read_msg[BUFFER_SIZE];

    // Create the FIFO if it doesn't exist
    if (mkfifo(FIFO_NAME, 0666) == -1) {
        perror("mkfifo");
    }

    printf("Writer: Ready for chat. Type 'exit' to quit.\n");
    while (1) {
        // Open FIFO for writing
        fd = open(FIFO_NAME, O_WRONLY);
        if (fd == -1) {
            perror("open for writing");
            exit(1);
        }

        // Write a message to the FIFO
        printf("You: ");
        fgets(write_msg, BUFFER_SIZE, stdin);
        write_msg[strcspn(write_msg, "\n")] = '\0'; // Remove newline character
        write(fd, write_msg, strlen(write_msg) + 1);
        close(fd);

        // Exit if the user types "exit"
        if (strcmp(write_msg, "exit") == 0) {
            break;
        }

        // Open FIFO for reading
        fd = open(FIFO_NAME, O_RDONLY);
        if (fd == -1) {
            perror("open for reading");
            exit(1);
        }

        // Read the response from the FIFO
        read(fd, read_msg, BUFFER_SIZE);
        printf("Reader: %s\n", read_msg);
        close(fd);

        // Exit if the reader sends "exit"
        if (strcmp(read_msg, "exit") == 0) {
            break;
        }
    }

    printf("Writer: Chat ended.\n");
    return 0;
}