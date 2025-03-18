#include <stdio.h>

struct Process {
    int id, bt, priority, wt, tat;
};

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
    p[0].wt = 0;
    for (int i = 1; i < n; i++) {
        p[i].wt = p[i - 1].wt + p[i - 1].bt;
    }
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].wt + p[i].bt;
    }
}

void display(struct Process p[], int n) {
    int total_wt = 0, total_tat = 0;
    printf("Process ID\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].id, p[i].bt, p[i].priority, p[i].wt, p[i].tat);
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }
    printf("\nAverage Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
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
