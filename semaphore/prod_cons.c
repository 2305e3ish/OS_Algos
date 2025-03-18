#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5 // Fixed buffer size

int buffer[BUFFER_SIZE]; 
int count = 0, in = 0, out = 0; // Buffer variables

pthread_mutex_t mutex; // Mutex for synchronization
pthread_cond_t full, empty; // Condition variables

void *producer(void *arg) {
    while (1) {
        sleep(1); // Simulate production time
        int item = rand() % 100;

        pthread_mutex_lock(&mutex);
        while (count == BUFFER_SIZE) 
            pthread_cond_wait(&empty, &mutex); // Wait if buffer is full
        
        buffer[in] = item;
        printf("Producer produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;
        count++;

        pthread_cond_signal(&full); // Signal consumer
        pthread_mutex_unlock(&mutex);
    }
}

void *consumer(void *arg) {
    while (1) {
        sleep(2); // Simulate consumption time

        pthread_mutex_lock(&mutex);
        while (count == 0) 
            pthread_cond_wait(&full, &mutex); // Wait if buffer is empty
        
        int item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;
        count--;

        pthread_cond_signal(&empty); // Signal producer
        pthread_mutex_unlock(&mutex);
    }
}

int main() {
    pthread_t prod, cons;
    srand(time(NULL));

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    return 0;
}
