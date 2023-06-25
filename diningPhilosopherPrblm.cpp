#include <iostream>
#include <fstream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

#define NUM_PHILOSOPHERS 5
#define IS_THINKING 2
#define IS_HUNGRY 1
#define IS_EATING 0
#define LEFT_FORK (philosopher_id + 4) % NUM_PHILOSOPHERS
#define RIGHT_FORK (philosopher_id + 1) % NUM_PHILOSOPHERS

int state[NUM_PHILOSOPHERS];
int philosopherIdsArr[NUM_PHILOSOPHERS] = {0, 1, 2, 3, 4};

sem_t mutex;
sem_t S[NUM_PHILOSOPHERS];

void test(int philosopher_id)
{
    if (state[philosopher_id] == IS_HUNGRY && state[LEFT_FORK] != IS_EATING && state[RIGHT_FORK] != IS_EATING)
    {
        state[philosopher_id] = IS_EATING;

        sleep(2);

        ofstream outputFile("diningPhilosopherPrblmOutput.txt", ofstream::out | ofstream::app);
        outputFile << "Philosopher " << philosopher_id + 1 << " takes fork " << LEFT_FORK + 1 << " and " << philosopher_id + 1 << endl;
        outputFile << "Philosopher " << philosopher_id + 1 << " is Eating" << endl;
        outputFile.close();

        sem_post(&S[philosopher_id]);
    }
}

void take_fork(int philosopher_id)
{
    sem_wait(&mutex);

    state[philosopher_id] = IS_HUNGRY;

    ofstream outputFile("diningPhilosopherPrblmOutput.txt", ofstream::out | ofstream::app);
    outputFile << "Philosopher " << philosopher_id + 1 << " is Hungry" << endl;
    outputFile.close();

    test(philosopher_id);

    sem_post(&mutex);

    sem_wait(&S[philosopher_id]);

    sleep(1);
}

void put_fork(int philosopher_id)
{
    sem_wait(&mutex);

    state[philosopher_id] = IS_THINKING;

    ofstream outputFile("diningPhilosopherPrblmOutput.txt", ofstream::out | ofstream::app);
    outputFile << "Philosopher " << philosopher_id + 1 << " putting fork " << LEFT_FORK + 1 << " and " << philosopher_id + 1 << " down" << endl;
    outputFile << "Philosopher " << philosopher_id + 1 << " is thinking" << endl;
    outputFile.close();

    test(LEFT_FORK);
    test(RIGHT_FORK);

    sem_post(&mutex);
}

void *philosopher(void *param)
{
    while (1)
    {
        int *philosopher_id = (int *)param;

        sleep(1);

        take_fork(*philosopher_id);

        sleep(0);

        put_fork(*philosopher_id);
    }
    return NULL;
}

int main()
{
    int i;
    pthread_t thread_id[NUM_PHILOSOPHERS];

    sem_init(&mutex, 0, 1);

    for (i = 0; i < NUM_PHILOSOPHERS; i++)
        sem_init(&S[i], 0, 0);

    for (i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_create(&thread_id[i], NULL, philosopher, &philosopherIdsArr[i]);

        ofstream outputFile("diningPhilosopherPrblmOutput.txt", ofstream::out | ofstream::app);
        outputFile << "Philosopher " << i + 1 << " is thinking" << endl;
        outputFile.close();
    }

    for (i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_join(thread_id[i], NULL);
    }
    return 0;
}
