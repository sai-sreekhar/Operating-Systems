#include <iostream>
#include <fstream>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

using namespace std;

#define NUMBER_OF_THREADS 2
#define BUFFER_SIZE 10

typedef struct {
    int buffer[BUFFER_SIZE];
    int writeIndex;
    int readIndex;
    int filledSlots;
} CircularBuffer;

CircularBuffer cirBuffer = {0};

pthread_mutex_t syncMutex;
sem_t semEmptySlots;
sem_t semFilledSlots;

void *consumer(void *arg) {
    ofstream outputFile("producerConsumerPrblmOutput.txt", ofstream::out | ofstream::app);
    while (true) {
        sem_wait(&semFilledSlots);
        pthread_mutex_lock(&syncMutex);

        int consumedValue = cirBuffer.buffer[cirBuffer.readIndex];
        outputFile << "Consumed: " << consumedValue << endl;

        cirBuffer.readIndex = (cirBuffer.readIndex + 1) % BUFFER_SIZE;
        cirBuffer.filledSlots--;

        pthread_mutex_unlock(&syncMutex);
        sem_post(&semEmptySlots);
    }
    outputFile.close();
    return NULL;
}

void *producer(void *arg) {
    int value = 0;
    ofstream outputFile("producerConsumerPrblmOutput.txt", ofstream::out | ofstream::app);
    while (true) {
        sem_wait(&semEmptySlots);
        pthread_mutex_lock(&syncMutex);

        cirBuffer.buffer[cirBuffer.writeIndex] = value;
        outputFile << "Produced: " << value << endl;

        cirBuffer.writeIndex = (cirBuffer.writeIndex + 1) % BUFFER_SIZE;
        cirBuffer.filledSlots++;

        pthread_mutex_unlock(&syncMutex);
        sem_post(&semFilledSlots);

        value++;
    }
    outputFile.close();
    return NULL;
}

int main() {
    pthread_t threadId[NUMBER_OF_THREADS];

    if (pthread_mutex_init(&syncMutex, NULL)) {
        cout << "Mutex initialization failed" << endl;
        return 1;
    }

    if (sem_init(&semEmptySlots, 0, BUFFER_SIZE)) {
        cout << "Semaphore initialization for empty slots failed" << endl;
        return 1;
    }

    if (sem_init(&semFilledSlots, 0, 0)) {
        cout << "Semaphore initialization for filled slots failed" << endl;
        return 1;
    }

    pthread_create(&threadId[0], NULL, producer, NULL);
    pthread_create(&threadId[1], NULL, consumer, NULL);

    pthread_join(threadId[0], NULL);
    pthread_join(threadId[1], NULL);

    pthread_mutex_destroy(&syncMutex);
    sem_destroy(&semEmptySlots);
    sem_destroy(&semFilledSlots);

    return 0;
}
