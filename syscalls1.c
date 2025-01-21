#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2, wpid;
    int status;

    pid1 = fork();
    if (pid1 < 0) {
        perror("Fork failed for child 1");
        exit(1);
    }

    if (pid1 == 0) {
        // Child 1 (fcfs process)
        printf("Child 1: Executing fcfs.c (PID = %d)\n", getpid());
        char *args1[] = {"./fcfs", NULL};  // Execute fcfs program
        execvp(args1[0], args1);
        perror("Exec failed for fcfs");
        exit(1);
    }

    // Parent process waits for child 1 to finish first
    wpid = waitpid(pid1, &status, 0);
    if (wpid == -1) {
        perror("Waitpid failed for child 1");
        exit(1);
    }

    if (WIFEXITED(status)) {
        printf("Child 1 (fcfs) exited with status %d\n", WEXITSTATUS(status));
    }

    pid2 = fork();
    if (pid2 < 0) {
        perror("Fork failed for child 2");
        exit(1);
    }

    if (pid2 == 0) {
        // Child 2 (sjf process)
        printf("Child 2: Executing sjf.c (PID = %d)\n", getpid());
        char *args2[] = {"./sjf", NULL};  // Execute sjf program
        execvp(args2[0], args2);
        perror("Exec failed for sjf");
        exit(1);
    }

    // Parent process waits for child 2 to finish
    wpid = waitpid(pid2, &status, 0);
    if (wpid == -1) {
        perror("Waitpid failed for child 2");
        exit(1);
    }

    if (WIFEXITED(status)) {
        printf("Child 2 (sjf) exited with status %d\n", WEXITSTATUS(status));
    }

    printf("Both fcfs and sjf executed successfully!\n");

    return 0;
}
