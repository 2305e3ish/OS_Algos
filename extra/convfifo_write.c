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
    char write_msg[BUFFER_SIZE];

    // Create the FIFO if it doesn't exist
    if (mkfifo(FIFO_NAME, 0666) == -1) {
        perror("mkfifo");
        exit(1);
    }

    printf("Writer: Waiting for reader...\n");
    int fd = open(FIFO_NAME, O_WRONLY); // Open FIFO for writing
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    printf("Writer: Ready to send messages. Type 'exit' to quit.\n");
    while (1) {
        printf("You: ");
        fgets(write_msg, BUFFER_SIZE, stdin);
        write_msg[strcspn(write_msg, "\n")] = '\0'; // Remove newline character

        // Write the message to the FIFO
        if (write(fd, write_msg, strlen(write_msg) + 1) == -1) {
            perror("write");
            break;
        }

        // Exit if the user types "exit"
        if (strcmp(write_msg, "exit") == 0) {
            break;
        }
    }

    close(fd); // Close the FIFO
    printf("Writer: Conversation ended.\n");
    return 0;
}