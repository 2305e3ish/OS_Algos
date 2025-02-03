#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>

int main() {
    // Open a file for writing
    int file = open("example.txt", O_WRONLY | O_CREAT, 0644);
    if (file == -1) {
        perror("Open failed");
        return 1;
    }

    // Write to the file
    const char *text = "Hello, this is a test file.\n";
    write(file, text, 26);

    // Close the file
    close(file);

    // Open the file for reading
    file = open("example.txt", O_RDONLY);
    if (file == -1) {
        perror("Open failed");
        return 1;
    }

    // Read from the file
    char buffer[27];
    read(file, buffer, 26);
    buffer[26] = '\0'; // Null-terminate the string
    printf("Content of example.txt: %s\n", buffer);

    // Use lseek to move the file pointer to the beginning
    lseek(file, 0, SEEK_SET);

    // Read again from the file
    read(file, buffer, 26);
    buffer[26] = '\0'; // Null-terminate the string
    printf("Content of example.txt after lseek: %s\n", buffer);

    // Close the file
    close(file);

    // Get file information
    struct stat fileStat;
    stat("example.txt", &fileStat);
    printf("File size: %ld bytes\n", fileStat.st_size);

    // List the contents of the current directory
    DIR *dir = opendir(".");
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);

    return 0;
}
