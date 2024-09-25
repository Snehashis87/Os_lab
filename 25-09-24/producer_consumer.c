#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct Node {
    int item;
    struct Node* next;
} Node;

typedef struct Buffer {
    Node* front;
    Node* rear;
    int size;
    int maxSize;
} Buffer;

Buffer* buffer;
pthread_mutex_t mutex;
pthread_cond_t not_empty;
pthread_cond_t not_full;

// Global counters for produced and consumed items
int total_produced = 0;
int total_consumed = 0;

Buffer* createBuffer(int maxSize) {
    Buffer* b = (Buffer*)malloc(sizeof(Buffer));
    b->front = NULL;
    b->rear = NULL;
    b->size = 0;
    b->maxSize = maxSize;
    return b;
}

void produce(int item) {
    pthread_mutex_lock(&mutex);
    
    while (buffer->size == buffer->maxSize) {
        printf("Buffer is full, producer is waiting...\n");
        pthread_cond_wait(&not_full, &mutex);
    }
    
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->item = item;
    newNode->next = NULL;

    if (buffer->rear == NULL) { // Buffer is empty
        buffer->front = newNode;
        buffer->rear = newNode;
    } else {
        buffer->rear->next = newNode;
        buffer->rear = newNode;
    }
    
    buffer->size++;
    total_produced++;
    printf("Produced: %d, Buffer size: %d\n", item, buffer->size);
    
    pthread_cond_signal(&not_empty);
    pthread_mutex_unlock(&mutex);
}

int consume() {
    pthread_mutex_lock(&mutex);
    
    while (buffer->size == 0) {
        printf("Buffer is empty, consumer is waiting...\n");
        pthread_cond_wait(&not_empty, &mutex);
    }
    
    Node* temp = buffer->front;
    int item = temp->item;
    buffer->front = buffer->front->next;

    if (buffer->front == NULL) { // Buffer is empty after consuming
        buffer->rear = NULL;
    }

    buffer->size--;
    total_consumed++;
    printf("Consumed: %d, Buffer size: %d\n", item, buffer->size);
    
    free(temp);
    pthread_cond_signal(&not_full);
    pthread_mutex_unlock(&mutex);
    
    return item;
}

void* producer(void* arg) {
    int item;
    for (item = 1; item <= 10; item++) {
        produce(item);
        sleep(rand() % 2); // Random delay
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 0; i < 10; i++) {
        consume();
        sleep(rand() % 2); // Random delay
    }
    return NULL;
}

int main() {
    int bufferSize;
    
    printf("Enter the buffer size: ");
    scanf("%d", &bufferSize);

    // Ensure the buffer size is positive
    if (bufferSize <= 0) {
        fprintf(stderr, "Buffer size must be a positive integer.\n");
        return 1;
    }

    pthread_t prod_thread, cons_thread;

    buffer = createBuffer(bufferSize);
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&not_empty, NULL);
    pthread_cond_init(&not_full, NULL);

    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Clean up remaining items in the buffer
    while (buffer->front != NULL) {
        consume(); // Consume any remaining items
    }

    printf("Total produced items: %d\n", total_produced);
    printf("Total consumed items: %d\n", total_consumed);

    // Clean up
    free(buffer);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&not_empty);
    pthread_cond_destroy(&not_full);

    return 0;
}

