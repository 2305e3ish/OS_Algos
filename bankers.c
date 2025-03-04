#include <stdio.h>
int main() {
    int n, m, i, j, k;
   
    // Input number of processes and resources
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    // Initialize matrices and available resources array and total instances of resources
    int alloc[n][m], max[n][m], avail[m], total[m];

    // Input Allocation Matrix
    printf("Enter the allocation matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Input Maximum Matrix
    printf("Enter the maximum matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input Total Instances of Resources
    printf("Enter the total instances of resources:\n");
    for (i = 0; i < m; i++){
        scanf("%d", &total[i]);
    }

    // Calculate Available Resources
    for (i = 0; i < m; i++){
        avail[i] = total[i];
        for (int j = 0; j < n; j++){
            avail[i] -= alloc[j][i];
        }
        
    }

    // Initialize necessary arrays
    int f[n], ans[n], ind = 0;
    for (k = 0; k < n; k++) {
        f[k] = 0;
    }

    int need[n][m];
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Banker's Algorithm to find safe sequence
    
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            if (f[i] == 0) {
                int flag = 0;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    ans[ind++] = i;
                    for (int y = 0; y < m; y++) {
                        avail[y] += alloc[i][y];
                    }
                    f[i] = 1;
                }
            }
        }
    }

    // Check if system is in a safe state
    int flag = 1;
    for (i = 0; i < n; i++) {
        if (f[i] == 0) {
            flag = 0;
            printf("The following system is not safe\n");
            break;
        }
    }

    // Print Safe Sequence if the system is in a safe state
    if (flag == 1) {
        printf("Following is the SAFE Sequence\n");
        for (i = 0; i < n - 1; i++) {
            printf(" P%d ->", ans[i]);
        }
        printf(" P%d\n", ans[n - 1]);
    }

    return 0;
}