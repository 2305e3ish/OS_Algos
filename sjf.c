#include <stdio.h>

typedef struct {
    int pid;  // Process ID
    int at;   // Arrival Time
    int bt;   // Burst Time
    int ct;   // Completion Time
    int tat;  // Turnaround Time
    int wt;   // Waiting Time
} Process;

// Function to sort the processes based on arrival time
void sortByArrivalTime(Process proc[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (proc[i].at > proc[j].at) {
                Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

// Function to calculate the average waiting time and turnaround time
void calculateAvgTimes(Process proc[], int n) {
    int totalTAT = 0, totalWT = 0;
    
    for (int i = 0; i < n; i++) {
        totalTAT += proc[i].tat;
        totalWT += proc[i].wt;
    }
    
    printf("Average Turnaround Time: %.2f\n", (float)totalTAT / n);
    printf("Average Waiting Time: %.2f\n", (float)totalWT / n);
}

// Shortest Job First scheduling
void sjf(Process proc[], int n) {
    int currentTime = 0; // Start with time 0
    int completed = 0;   // Process completion counter
    
    while (completed < n) {
        int minBT = 1000, index = -1;
        
        // Find the process with the shortest burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (proc[i].at <= currentTime && proc[i].ct == 0 && proc[i].bt < minBT) {
                minBT = proc[i].bt;
                index = i;
            }
        }

        if (index != -1) {
            proc[index].ct = currentTime + proc[index].bt; // Set completion time
            proc[index].tat = proc[index].ct - proc[index].at; // Turnaround Time = CT - AT
            proc[index].wt = proc[index].tat - proc[index].bt; // Waiting Time = TAT - BT
            
            currentTime = proc[index].ct; // Update current time
            completed++; // Increase completed process counter
        } else {
            currentTime++; // If no process is available, increment time
        }
    }
    
    // Print results
    printf("PID  Arrival Time  Burst Time  Completion Time  Turnaround Time  Waiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].at, proc[i].bt, proc[i].ct, proc[i].tat, proc[i].wt);
    }

    calculateAvgTimes(proc, n);
}

int main() {
    int n;
    
    // Taking the number of processes as input
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process proc[n];
    
    // Taking input for process details
    for (int i = 0; i < n; i++) {
        printf("\nEnter for Process %d:\n", i + 1);
        proc[i].pid = i + 1;  // Assigning process id
        printf("Enter Arrival Time: ");
        scanf("%d", &proc[i].at);
        printf("Enter Burst Time: ");
        scanf("%d", &proc[i].bt);
        proc[i].ct = 0;  // Initializing Completion Time to 0
    }
    
    // Sort processes by arrival time
    sortByArrivalTime(proc, n);
    
    // Execute SJF scheduling
    sjf(proc, n);
    
    return 0;
}
