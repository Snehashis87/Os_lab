#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    int value; 
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} BinarySemaphore;

void initSemaphore(BinarySemaphore *sem) {
    sem->value = 1; 
    pthread_mutex_init(&sem->mutex, NULL);
    pthread_cond_init(&sem->cond, NULL);
}

void waitSemaphore(BinarySemaphore *sem) {
    pthread_mutex_lock(&sem->mutex);
    while (sem->value == 0) {
        pthread_cond_wait(&sem->cond, &sem->mutex);
    }
    sem->value = 0; 
    pthread_mutex_unlock(&sem->mutex);
}

void signalSemaphore(BinarySemaphore *sem) {
    pthread_mutex_lock(&sem->mutex);
    sem->value = 1;  
    pthread_cond_signal(&sem->cond);  
    pthread_mutex_unlock(&sem->mutex);
}

void* threadFunction(void* arg) {
    BinarySemaphore *sem = (BinarySemaphore *)arg;

    printf("Thread %ld trying to acquire the semaphore.\n", pthread_self());
    waitSemaphore(sem);
    printf("Thread %ld acquired the semaphore.\n", pthread_self());
    sleep(1);

    printf("Thread %ld releasing the semaphore.\n", pthread_self());
    signalSemaphore(sem);

    return NULL;
}

int main() {
    pthread_t threads[5]; 
    BinarySemaphore sem;

    initSemaphore(&sem);

    for (int i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, threadFunction, (void*)&sem);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&sem.mutex);
    pthread_cond_destroy(&sem.cond);

    return 0;
}

