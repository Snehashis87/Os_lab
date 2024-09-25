#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    int value;  // Semaphore value
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} CountingSemaphore;

void initSemaphore(CountingSemaphore *sem, int initial) {
    sem->value = initial;  // Initialize with a given value
    pthread_mutex_init(&sem->mutex, NULL);
    pthread_cond_init(&sem->cond, NULL);
}

void waitSemaphore(CountingSemaphore *sem) {
    pthread_mutex_lock(&sem->mutex);
    while (sem->value <= 0) {
        pthread_cond_wait(&sem->cond, &sem->mutex);
    }
    sem->value--;  // Decrement the semaphore value
    pthread_mutex_unlock(&sem->mutex);
}

void signalSemaphore(CountingSemaphore *sem) {
    pthread_mutex_lock(&sem->mutex);
    sem->value++;  // Increment the semaphore value
    pthread_cond_signal(&sem->cond);  // Notify a waiting thread
    pthread_mutex_unlock(&sem->mutex);
}

void* threadFunction(void* arg) {
    CountingSemaphore *sem = (CountingSemaphore *)arg;

    printf("Thread %ld trying to acquire the semaphore.\n", pthread_self());
    waitSemaphore(sem);
    printf("Thread %ld acquired the semaphore. Remaining: %d\n", pthread_self(), sem->value);

    // Simulate some work
    sleep(1);

    printf("Thread %ld releasing the semaphore.\n", pthread_self());
    signalSemaphore(sem);

    return NULL;
}

int main() {
    pthread_t threads[5];
    CountingSemaphore sem;

    // Initialize the semaphore with a value of 2 (2 resources available)
    initSemaphore(&sem, 2);

    // Create multiple threads
    for (int i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, threadFunction, (void*)&sem);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    // Cleanup
    pthread_mutex_destroy(&sem.mutex);
    pthread_cond_destroy(&sem.cond);

    return 0;
}

