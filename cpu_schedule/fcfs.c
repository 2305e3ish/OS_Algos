#include <stdio.h>

void sort(int pro[], int ari[], int bru[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (ari[i] > ari[j]) {
                // Swap arrival times
                temp = ari[i];
                ari[i] = ari[j];
                ari[j] = temp;

                // Swap burst times
                temp = bru[i];
                bru[i] = bru[j];
                bru[j] = temp;

                // Swap process IDs
                temp = pro[i];
                pro[i] = pro[j];
                pro[j] = temp;
            }
        }
    }
}

void avg(int pro[], int ari[], int bru[], int n) {
    int i, completion[n], turnaround[n], waiting[n];
    float avg_turnaround = 0, avg_waiting = 0;
    int time = 0;

    printf("Process\tArrival\tBurst\tWaiting\tTurn Around\n");

    for (i = 0; i < n; i++) {
        if (time < ari[i]) {
            time = ari[i];
        }
        completion[i] = time + bru[i];
        time = completion[i];
        
        turnaround[i] = completion[i] - ari[i];
        waiting[i] = turnaround[i] - bru[i];
        
        avg_turnaround += turnaround[i];
        avg_waiting += waiting[i];

        printf("%d\t%d\t%d\t%d\t%d\n", pro[i], ari[i], bru[i], waiting[i], turnaround[i]);
    }

    avg_turnaround /= n;
    avg_waiting /= n;

    printf("\nAverage Turn Around Time: %.2f\n", avg_turnaround);
    printf("Average Waiting Time: %.2f\n", avg_waiting);
}

int main() {
    int n, i;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int pro[n], ari[n], bru[n];

    printf("Enter the process IDs:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &pro[i]);
    }

    printf("Enter the arrival times:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &ari[i]);
    }

    printf("Enter the burst times:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &bru[i]);
    }

    // Sorting based on arrival times
    sort(pro, ari, bru, n);

    // Calculate and print the average turnaround and waiting times
    avg(pro, ari, bru, n);

    return 0;
}

