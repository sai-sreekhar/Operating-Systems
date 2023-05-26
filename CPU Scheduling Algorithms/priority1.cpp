#include <bits/stdc++.h>
using namespace std;

struct process
{
    int arrivalTime, burstTime, priority, processNum;
};

process processArr[50];

bool comp(process a, process b)
{
    if (a.arrivalTime == b.arrivalTime)
    {
        return a.priority < b.priority;
    }
    else
    {
        return a.arrivalTime < b.arrivalTime;
    }
}

void getWaitingTime(int wt[], int totalProcess)
{
    int service[50];
    service[0] = processArr[0].arrivalTime;
    wt[0] = 0;

    for (int i = 1; i < totalProcess; i++)
    {
        service[i] = processArr[i - 1].burstTime + service[i - 1];
        wt[i] = service[i] - processArr[i].arrivalTime;
        if (wt[i] < 0)
        {
            wt[i] = 0;
        }
    }
}

void getTurnaroundTime(int tat[], int wt[], int totalProcess)
{

    for (int i = 0; i < totalProcess; i++)
    {
        tat[i] = processArr[i].burstTime + wt[i];
    }
}

void findgc(int totalProcess)
{
    int wt[50], tat[50];
    double wavg = 0, tavg = 0;
    getWaitingTime(wt, totalProcess);
    getTurnaroundTime(tat, wt, totalProcess);

    int stime[50], ctime[50];
    stime[0] = processArr[0].arrivalTime;
    ctime[0] = stime[0] + tat[0];

    for (int i = 1; i < totalProcess; i++)
    {
        stime[i] = ctime[i - 1];
        ctime[i] = stime[i] + tat[i] - wt[i];
    }

    cout << "Process_no\tStart_time\tComplete_time\tTurn_Around_Time\tWaiting_Time" << endl;

    for (int i = 0; i < totalProcess; i++)
    {
        wavg += wt[i];
        tavg += tat[i];

        cout << processArr[i].processNum << "\t\t" << stime[i] << "\t\t" << ctime[i] << "\t\t" << tat[i] << "\t\t\t" << wt[i] << endl;
    }

    cout << "Average waiting time is : ";
    cout << wavg / (float)totalProcess << endl;
    cout << "average turnaround time : ";
    cout << tavg / (float)totalProcess << endl;
}

int main()
{
    int totalProcess;
    cout << "Enter the number of processes:\n";
    cin >> totalProcess;
    int arrivalTime[totalProcess], burstTime[totalProcess], priority[totalProcess];
    cout << "Enter the arrival time, burst time and priority of each process:\n";
    for (int i = 0; i < totalProcess; i++)
    {
        cin >> arrivalTime[i] >> burstTime[i] >> priority[i];
    }

    for (int i = 0; i < totalProcess; i++)
    {
        processArr[i].arrivalTime = arrivalTime[i];
        processArr[i].burstTime = burstTime[i];
        processArr[i].priority = priority[i];
        processArr[i].processNum = i + 1;
    }

    sort(processArr, processArr + totalProcess, comp);

    findgc(totalProcess);

    return 0;
}
