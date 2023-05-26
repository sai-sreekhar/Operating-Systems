
#include <iostream>
#include <stdlib.h>
using namespace std;

class Process
{
    int id, burstTime, arrivalTime, completionTime, turnaroundTime, waitingTime;

public:
    void input(Process *, int);
    void calc(Process *, int);
    void display(Process *, int);
    void sort(Process *, int);
};

int main()
{
    int n;
    cout << "\nEnter the no of processes in your system:\n";
    cin >> n;
    Process *p = new Process[n];
    Process f;
    f.input(p, n);
    f.sort(p, n);
    f.calc(p, n);
    f.display(p, n);
    return 0;
}

void Process::input(Process *p, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter arriival time for process " << i + 1 << ":\n";
        cin >> p[i].arrivalTime;
        cout << "\nEnter burst time for process " << i + 1 << ":\n";
        cin >> p[i].burstTime;
        p[i].id = i + 1;
    }
}

void Process::calc(Process *p, int n)
{
    int sum = 0;
    sum = sum + p[0].arrivalTime;
    for (int i = 0; i < n; i++)
    {
        sum = sum + p[i].burstTime;
        p[i].completionTime = sum;
        p[i].turnaroundTime = p[i].completionTime - p[i].arrivalTime;
        p[i].waitingTime = p[i].turnaroundTime - p[i].burstTime;
        if (sum < p[i + 1].arrivalTime)
        {
            int t = p[i + 1].arrivalTime - sum;
            sum = sum + t;
        }
    }
}

void Process::sort(Process *p, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j].arrivalTime > p[j + 1].arrivalTime)
            {
                int temp;

                temp = p[j].burstTime;
                p[j].burstTime = p[j + 1].burstTime;
                p[j + 1].burstTime = temp;

                temp = p[j].arrivalTime;
                p[j].arrivalTime = p[j + 1].arrivalTime;
                p[j + 1].arrivalTime = temp;

                temp = p[j].id;
                p[j].id = p[j + 1].id;
                p[j + 1].id = temp;
            }
        }
    }
}

void Process::display(Process *p, int n)
{
    cout << "Process\tArrival\tBurst\tWaiting\tTurn Around\tCompletion\n";
    for (int i = 0; i < n; i++)
    {
        cout << " P[" << p[i].id << "]\t " << p[i].arrivalTime << "\t" << p[i].burstTime << "\t" << p[i].waitingTime << "\t " << p[i].turnaroundTime << "\t\t" << p[i].completionTime << "\n";
    }

    int totalWt = 0;
    int totalTat = 0;
    for (int i = 0; i < n; i++)
    {
        totalWt += p[i].waitingTime;
        totalTat += p[i].turnaroundTime;
    }
    cout << "\nAverage waiting time: " << (float)totalWt / (float)n;
    cout << "\nAverage turn around time: " << (float)totalTat / (float)n << "\n";
}
