#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

int main() {
    // Open a file for writing
    int file = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file == -1) {
        perror("Open failed");
        return 1;
    }

    // Write to the file
    const char *text = "Hello, this is a test file. The size is not known by me so let's see if garbage values come.\n";
    ssize_t bytesWritten = write(file, text, strlen(text));
    if (bytesWritten == -1) {
        perror("Write failed");
        close(file);
        return 1;
    }

    // Close the file
    close(file);

    // Open the file for reading
    file = open("example.txt", O_RDONLY);
    if (file == -1) {
        perror("Open failed");
        return 1;
    }

    // Read from the file
    char buffer[strlen(text)];
    ssize_t bytesRead = read(file, buffer, strlen(text));
    if (bytesRead == -1) {
        perror("Read failed");
        close(file);
        return 1;
    }
    buffer[bytesRead] = '\0'; // Null-terminate the string
    printf("Content of example.txt: %s\n", buffer);

    // Use lseek to move the file pointer to the beginning
    if (lseek(file, 0, SEEK_SET) == -1) {
        perror("Lseek failed");
        close(file);
        return 1;
    }

    // Read again from the file
    bytesRead = read(file, buffer, strlen(text));
    if (bytesRead == -1) {
        perror("Read failed");
        close(file);
        return 1;
    }
    buffer[bytesRead] = '\0'; // Null-terminate the string
    printf("Content of example.txt after lseek: %s\n", buffer);

    // Close the file
    close(file);

    // Get file information
    struct stat fileStat;
    if (stat("example.txt", &fileStat) == -1) {
        perror("Stat failed");
        return 1;
    }
    printf("File size: %ld bytes\n", fileStat.st_size);

    // List the contents of the current directory
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("Opendir failed");
        return 1;
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);

    return 0;
}