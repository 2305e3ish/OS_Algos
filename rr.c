#include <stdio.h>

typedef struct {
    int arrival_time;
    int burst_time;
    int remaining_time;
    int wait_time;
    int turnaround_time;
    int completion_time;
} Process;

void round_robin(Process processes[], int n, int tq) {
    int timer = 0;
    int remaining_processes = n;

    // Track the processes that are ready to execute
    int front = 0;
    int rear = 0;
    int ready_queue[n];
    
    // Initialize ready queue to -1 (indicating no process is in the queue)
    for (int i = 0; i < n; i++) {
        ready_queue[i] = -1;
    }

    // Begin Round Robin Scheduling
    while (remaining_processes > 0) {
        // Add any processes that have arrived at the current time
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= timer && processes[i].remaining_time > 0) {
                int is_already_in_queue = 0;
                for (int j = 0; j < rear; j++) {
                    if (ready_queue[j] == i) {
                        is_already_in_queue = 1;
                        break;
                    }
                }
                if (!is_already_in_queue) {
                    ready_queue[rear++] = i;
                }
            }
        }

        // If the ready queue is empty, just increment the time and continue
        if (front == rear) {
            timer++;
            continue;
        }

        // Pick the next process to execute
        int process_index = ready_queue[front++];
        
        // Process execution for at most 'tq' time
        int time_to_run = tq;
        if (processes[process_index].remaining_time < tq) {
            time_to_run = processes[process_index].remaining_time;
        }

        processes[process_index].remaining_time -= time_to_run;
        timer += time_to_run;

        // If the process has finished
        if (processes[process_index].remaining_time == 0) {
            processes[process_index].completion_time = timer;
            remaining_processes--;
        }

        // If the process is not finished, add it back to the queue
        if (processes[process_index].remaining_time > 0) {
            ready_queue[rear++] = process_index;
        }

        // Reset the front index if it exceeds rear
        if (front == rear) {
            front = 0;
        }
    }
}

int main() {
    int n, tq;

    // Input number of processes and time quantum
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the time quantum: ");
    scanf("%d", &tq);

    Process processes[n];

    // Input arrival times and burst times
    printf("Enter the arrival and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d arrival time: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("P%d burst time: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].wait_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].completion_time = 0;
    }

    // Execute round robin scheduling
    round_robin(processes, n, tq);

    // Calculate waiting time and turnaround time
    float total_wait_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].wait_time = processes[i].turnaround_time - processes[i].burst_time;
        total_wait_time += processes[i].wait_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    // Output the results
    printf("\nProcess No.\tArrival Time\tBurst Time\tWait Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, processes[i].arrival_time, processes[i].burst_time,
                processes[i].wait_time, processes[i].turnaround_time);
    }

    // Print the averages
    printf("\nAverage wait time: %.2f\n", total_wait_time / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);

    return 0;
}
