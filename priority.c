#include <stdio.h>

// Structure to represent each process
struct Process {
    int id, bt, priority, wt, tat;
};

// Function to sort processes by priority (ascending)
void sortProcesses(struct Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].priority > p[j + 1].priority) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void calculateTimes(struct Process p[], int n) {
    p[0].wt = 0; // First process has no waiting time
    for (int i = 1; i < n; i++) {
        p[i].wt = p[i - 1].wt + p[i - 1].bt; // Waiting time is sum of burst times of previous processes
    }
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].wt + p[i].bt; // Turnaround time = Waiting time + Burst time
    }
}

void display(struct Process p[], int n) {
    printf("Process ID\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].id, p[i].bt, p[i].priority, p[i].wt, p[i].tat);
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter burst time and priority for process %d: ", i + 1);
        scanf("%d %d", &p[i].bt, &p[i].priority);
    }

    // Sort processes by priority (lower priority number means higher priority)
    sortProcesses(p, n);

    // Calculate waiting time and turnaround time
    calculateTimes(p, n);

    // Display the results
    display(p, n);

    return 0;
}
