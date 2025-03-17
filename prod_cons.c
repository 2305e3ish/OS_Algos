#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Define a simple semaphore structure
typedef struct {
    int value;
    pthread_mutex_t lock;
    pthread_cond_t cond;
} semaphore;

// Initialize the semaphore
void sem_init(semaphore *s, int value) {
    s->value = value;
    pthread_mutex_init(&s->lock, NULL);
    pthread_cond_init(&s->cond, NULL);
}

// wait() operation
void wait_sem(semaphore *s) {
    pthread_mutex_lock(&s->lock);
    s->value--;
    if (s->value < 0) {
        pthread_cond_wait(&s->cond, &s->lock);
    }
    pthread_mutex_unlock(&s->lock);
}

// signal() operation
void signal_sem(semaphore *s) {
    pthread_mutex_lock(&s->lock);
    s->value++;
    if (s->value <= 0) {
        pthread_cond_signal(&s->cond);
    }
    pthread_mutex_unlock(&s->lock);
}

// Thread function
void *thread_func(void *arg) {
    semaphore *s = (semaphore *)arg;
    printf("Thread: Waiting on semaphore...\n");
    wait_sem(s);
    printf("Thread: Woken up! Proceeding...\n");
    return NULL;
}

int main() {
    semaphore sem;
    pthread_t tid;
    
    // Initialize semaphore with 0
    sem_init(&sem, 0);
    
    // Create a thread that will block on the semaphore
    if (pthread_create(&tid, NULL, thread_func, (void *)&sem) != 0) {
        perror("Error creating thread");
        exit(EXIT_FAILURE);
    }
    
    // Sleep for 2 seconds
    sleep(2);
    printf("Main: Signaling semaphore to wake the waiting thread.\n");
    signal_sem(&sem);
    
    // Wait for thread to finish
    pthread_join(tid, NULL);
    
    // Clean up resources
    pthread_mutex_destroy(&sem.lock);
    pthread_cond_destroy(&sem.cond);
    
    return 0;
}
