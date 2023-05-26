

#include <bits/stdc++.h>
using namespace std;

struct Process
{
    int processId;
    int burstTime;
    int arrivalTime;
};

void findWaitingTime(Process processArr[], int n, int waitingTime[])
{
    int rt[n];
    for (int i = 0; i < n; i++)
    {
        rt[i] = processArr[i].burstTime;
    }

    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    bool check = false;

    while (complete != n)
    {
        for (int j = 0; j < n; j++)
        {
            if ((processArr[j].arrivalTime <= t) &&
                (rt[j] < minm) && rt[j] > 0)
            {
                minm = rt[j];
                shortest = j;
                check = true;
            }
        }

        if (check == false)
        {
            t++;
            continue;
        }

        rt[shortest]--;

        minm = rt[shortest];
        if (minm == 0)
            minm = INT_MAX;

        if (rt[shortest] == 0)
        {

            complete++;
            check = false;
            finish_time = t + 1;
            waitingTime[shortest] = finish_time - processArr[shortest].burstTime - processArr[shortest].arrivalTime;

            if (waitingTime[shortest] < 0)
            {
                waitingTime[shortest] = 0;
            }
        }

        t++;
    }
}

void findTurnAroundTime(Process processArr[], int n, int waitingTime[], int turnAroundTime[])
{
    for (int i = 0; i < n; i++)
        turnAroundTime[i] = processArr[i].burstTime + waitingTime[i];
}

void findavgTime(Process processArr[], int n)
{
    int waitingTime[n], turnAroundTime[n], total_wt = 0, total_tat = 0;
    findWaitingTime(processArr, n, waitingTime);
    findTurnAroundTime(processArr, n, waitingTime, turnAroundTime);

    cout << "Processes "
         << " Burst time "
         << " Waiting time "
         << " Turn around time\n";

    for (int i = 0; i < n; i++)
    {
        total_wt = total_wt + waitingTime[i];
        total_tat = total_tat + turnAroundTime[i];
        cout << " " << processArr[i].processId << "\t\t"
             << processArr[i].burstTime << "\t\t " << waitingTime[i]
             << "\t\t " << turnAroundTime[i] << endl;
    }

    cout << "\nAverage waiting time = "
         << (float)total_wt / (float)n;
    cout << "\nAverage turn around time = "
         << (float)total_tat / (float)n << "\n";
}

int main()
{
    int n;
    cout << "Enter the number of processes:\n";
    cin >> n;
    Process processArr[n];
    for (int i = 0; i < n; i++)
    {
        processArr[i].processId = i + 1;
        cout << "Enter the burst time of process " << i + 1 << ":\n";
        cin >> processArr[i].burstTime;
        cout << "Enter the arrival time of process " << i + 1 << ":\n";
        cin >> processArr[i].arrivalTime;
    }

    findavgTime(processArr, n);
    return 0;
}
