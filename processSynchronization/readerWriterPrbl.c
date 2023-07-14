#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t readMutex, writeMutex;
int sharedData = 0, readerCount = 0;

void *reader(void *arg)
{
  int readerID;
  readerID = ((int)arg);
  sem_wait(&readMutex);
  readerCount = readerCount + 1;
  if (readerCount == 1)
  {
    sem_wait(&writeMutex);
  }
  sem_post(&readMutex);

  printf("Data read by reader %d is %d\n", readerID, sharedData);
  sleep(1);

  sem_wait(&readMutex);
  readerCount = readerCount - 1;
  if (readerCount == 0)
  {
    sem_post(&writeMutex);
  }
  sem_post(&readMutex);
}

void *writer(void *arg)
{
  int writerID;
  writerID = ((int)arg);
  sem_wait(&writeMutex);
  sharedData++;
  printf("Data written by writer %d is %d\n", writerID, sharedData);
  sleep(1);
  sem_post(&writeMutex);
}

int main()
{
  int i, threadID;
  pthread_t readerThreads[5], writerThreads[5];

  sem_init(&readMutex, 0, 1);
  sem_init(&writeMutex, 0, 1);

  for (i = 0; i <= 3; i++)
  {
    threadID = i;
    pthread_create(&writerThreads[i], NULL, writer, (void *)threadID);
    pthread_create(&readerThreads[i], NULL, reader, (void *)threadID);
  }

  for (i = 0; i <= 3; i++)
  {
    pthread_join(writerThreads[i], NULL);
    pthread_join(readerThreads[i], NULL);
  }

  return 0;
}
