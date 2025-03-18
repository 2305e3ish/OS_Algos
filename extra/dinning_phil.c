#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 5  

enum { THINKING, HUNGRY, EATING };
int state[N];

void test(int i) {
    int left = (i + N - 1) % N;
    int right = (i + 1) % N;
    if (state[i] == HUNGRY && state[left] != EATING && state[right] != EATING) {
        state[i] = EATING;
        printf("Philosopher %d is eating.\n", i);
    }
}

void pickup(int i) {
    state[i] = HUNGRY;
    printf("Philosopher %d is hungry.\n", i);
    test(i);
}

void putdown(int i) {
    state[i] = THINKING;
    printf("Philosopher %d is thinking.\n", i);
    test((i + N - 1) % N);
    test((i + 1) % N);
}

int main() {
    int i;
    
    for (i = 0; i < N; i++) {
        state[i] = THINKING;
    }
    
    for (i = 0; i < N; i++) {
        printf("Philosopher %d is thinking.\n", i);
        sleep(1);
        
        pickup(i);
        
        if (state[i] == EATING) {
            sleep(1);
            putdown(i);
            printf("Philosopher %d finished eating.\n", i);
        } else {
            printf("Philosopher %d could not eat (neighbors were eating).\n", i);
        }
    }
    
    printf("Simulation complete: All philosophers have attempted to eat.\n");
    return 0;
}
