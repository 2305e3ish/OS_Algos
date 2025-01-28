#include <stdio.h>

void calculateWaitingTime(int n, int bt[], int wt[], int at[], int tq) {
    int rem_bt[n];
    for (int i = 0; i < n; i++) {
        rem_bt[i] = bt[i]; 
    }

    int t = 0; 

    while (1) {
        int done = 1; 

        for (int i = 0; i < n; i++) {
            if (rem_bt[i] > 0) {
                done = 0; 

                if (rem_bt[i] > tq) {
                    t += tq; 
                    rem_bt[i] -= tq; 
                } else {
                    t += rem_bt[i]; 
                    wt[i] = t - bt[i] - at[i]; 
                    rem_bt[i] = 0; 
                }
            }
        }

        if (done == 1) {
            break;
        }
    }
}

void calculateTurnAroundTime(int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i]; 
    }
}

int main() {
    int n, tq;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int bt[n], at[n], wt[n], tat[n];

    printf("Enter the time quantum: ");
    scanf("%d", &tq);

    for (int i = 0; i < n; i++) {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &bt[i]);
        at[i] = 0; 
    }

   
    calculateWaitingTime(n, bt, wt, at, tq);
    calculateTurnAroundTime(n, bt, wt, tat);


    printf("\nProcesses\tBurst Time\tWaiting Time\tTurn-Around Time\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }

    float avg_wt = 0, avg_tat = 0;
    for (int i = 0; i < n; i++) {
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    avg_wt /= n;
    avg_tat /= n;

    printf("\nAverage Waiting Time: %.2f\n", avg_wt);
    printf("Average Turn-Around Time: %.2f\n", avg_tat);

    return 0;
}