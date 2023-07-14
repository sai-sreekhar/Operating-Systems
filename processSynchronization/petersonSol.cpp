#include <iostream>
#include <fstream>
#include <unistd.h>
#include <ctime>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstdlib>
#include <iomanip>
#include <sys/wait.h>

using namespace std;

#define buffer_size 8

int shmid1, shmid2;
int shmid3, shmid4;
bool *flag_memory;
int *turn_memory;
int *buffer_memory;

int getrandom(int n)
{
    srand(time(NULL));
    return (rand() % n + 1);
}

time_t gettime()
{
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return ts.tv_sec;
}

int main()
{
    shmid1 = shmget(5354, sizeof(bool) * 2, IPC_CREAT | 0660);
    shmid2 = shmget(1232, sizeof(int) * 1, IPC_CREAT | 0660);
    shmid3 = shmget(4232, sizeof(int) * buffer_size, IPC_CREAT | 0660);
    shmid4 = shmget(5633, sizeof(int) * 1, IPC_CREAT | 0660);

    if (shmid1 < 0 || shmid2 < 0 || shmid3 < 0 || shmid4 < 0)
    {
        perror("Shared memory creation failed");
        exit(1);
    }

    time_t t1, t2;
    t1 = gettime();

    buffer_memory = (int *)shmat(shmid3, NULL, 0);
    int num = 0;
    while (num < buffer_size)
        buffer_memory[num++] = 0;

    int *current_state = (int *)shmat(shmid4, NULL, 0);
    *current_state = 1;
    int wait_time;
    int i = 0;
    int j = 1;

    pid_t a = fork();
    if (a < 0)
    {
        perror("Creating producer and consumer failed");
        exit(1);
    }
    if (a > 0)
    {
        flag_memory = (bool *)shmat(shmid1, NULL, 0);
        turn_memory = (int *)shmat(shmid2, NULL, 0);
        buffer_memory = (int *)shmat(shmid3, NULL, 0);
        if (flag_memory == (bool *)-1 || turn_memory == (int *)-1 || buffer_memory == (int *)-1)
        {
            perror("Producer shared memory error");
            exit(1);
        }

        bool *flag = flag_memory;
        int *turn = turn_memory;
        int *buf = buffer_memory;
        int index = 0;

        ofstream outputFile("petersonSolOutput.txt", ofstream::out | ofstream::app);
        while (*current_state == 1)
        {
            flag[j] = true;
            outputFile << "Producer is ready now." << endl << endl;
            *turn = i;
            while (flag[i] == true && *turn == i)
                ;

            index = 0;
            while (index < buffer_size)
            {
                if (buf[index] == 0)
                {
                    int temp = getrandom(buffer_size * 3);
                    outputFile << "The product " << temp << " has been produced and is ready to be consumed" << endl;
                    buf[index] = temp;
                    break;
                }
                index++;
            }

            if (index == buffer_size)
                outputFile << "The producer has produced the products to maximum capacity" << endl;
            outputFile << "Products: ";
            index = 0;
            while (index < buffer_size)
            {
                outputFile << buf[index] << " ";
                index++;
            }
            outputFile << endl;

            flag[j] = false;
            if (*current_state == 0)
                break;
            wait_time = getrandom(2);
            outputFile << "Producer will wait for " << wait_time << " seconds" << endl << endl;
            sleep(wait_time);
        }
        outputFile.close();
        exit(0);
    }
    else
    {
        flag_memory = (bool *)shmat(shmid1, NULL, 0);
        turn_memory = (int *)shmat(shmid2, NULL, 0);
        buffer_memory = (int *)shmat(shmid3, NULL, 0);
        if (flag_memory == (bool *)-1 || turn_memory == (int *)-1 || buffer_memory == (int *)-1)
        {
            perror("Consumer shared memory error");
            exit(1);
        }

        bool *flag = flag_memory;
        int *turn = turn_memory;
        int *buf = buffer_memory;
        int index = 0;
        flag[i] = false;
        sleep(5);

        ofstream outputFile("petersonSolOutput.txt", ofstream::out | ofstream::app);
        while (*current_state == 1)
        {
            flag[i] = true;
            outputFile << "Consumer can consume products." << endl << endl;
            *turn = j;
            while (flag[j] == true && *turn == j)
                ;

            if (buf[0] != 0)
            {
                outputFile << "Job " << buf[0] << " has been consumed" << endl;
                buf[0] = 0;
                index = 1;
                while (index < buffer_size)
                {
                    buf[index - 1] = buf[index];
                    index++;
                }
                buf[index - 1] = 0;
            }
            else
                outputFile << "No products available for the consumer to be consumed" << endl;
            outputFile << "Buffer: ";
            index = 0;
            while (index < buffer_size)
            {
                outputFile << buf[index] << " ";
                index++;
            }
            outputFile << endl;

            flag[i] = false;
            if (*current_state == 0)
                break;
            wait_time = getrandom(15);

            outputFile << "Consumer will need to wait for " << wait_time << " seconds to get products to be consumed." << endl << endl;
            sleep(wait_time);
        }
        outputFile.close();
        exit(0);
    }

    while (1)
    {
        t2 = gettime();

        if (t2 - t1 > 10)
        {
            *current_state = 0;
            break;
        }
    }

    wait(NULL);
    wait(NULL);
    ofstream outputFile("petersonSolOutput.txt", ofstream::out | ofstream::app);
    outputFile << "Too much time has passed." << endl;
    outputFile.close();

    return 0;
}
