#include <bits/stdc++.h>
using namespace std;

struct process
{
    int id;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
    int completionTime;
};

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the arrival time and burst time of each process:\n";
    process processArr[n];
    for (int i = 0; i < n; i++)
    {
        cin >> processArr[i].arrivalTime >> processArr[i].burstTime;
        processArr[i].id = i + 1;
    }

    int timeQuantum;
    cout << "Enter the time quantum: ";
    cin >> timeQuantum;

    queue<pair<int, int>> readyQueue;
    vector<bool> isCompleted(n, false);
    // queue<pair<int, int>> runningQueue;
    int currTime = 0;
    int minArrivalTimeIdx = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        if (processArr[i].arrivalTime < minArrivalTimeIdx)
        {
            minArrivalTimeIdx = i;
        }
    }
    currTime = processArr[minArrivalTimeIdx].arrivalTime;
    readyQueue.push({processArr[minArrivalTimeIdx].burstTime, minArrivalTimeIdx});
    isCompleted[minArrivalTimeIdx] = true;

    while (readyQueue.size() != 0)
    {
        pair<int, int> curr = readyQueue.front();
        readyQueue.pop();
        if (curr.first > timeQuantum)
        {
            curr.first -= timeQuantum;
            currTime += timeQuantum;

            for (int i = 0; i < n; i++)
            {
                if (processArr[i].arrivalTime <= currTime && !isCompleted[i])
                {
                    cout << "Pushing process " << i << " to ready queue\n";
                    readyQueue.push({processArr[i].burstTime, i});
                    isCompleted[i] = true;
                }
            }
            cout << "Pushing process " << curr.second << " back to ready queue\n";
            readyQueue.push(curr);
        }
        else
        {
            currTime += curr.first;
            curr.first = 0;
            for (int i = 0; i < n; i++)
            {
                if (processArr[i].arrivalTime <= currTime && !isCompleted[i])
                {
                    readyQueue.push({processArr[i].burstTime, i});
                    isCompleted[i] = true;
                }
            }
            processArr[curr.second].completionTime = currTime;
            processArr[curr.second].turnaroundTime = processArr[curr.second].completionTime - processArr[curr.second].arrivalTime;
            processArr[curr.second].waitingTime = processArr[curr.second].turnaroundTime - processArr[curr.second].burstTime;
        }
    }

    for (int i = 0; i < n; i++)
    {
        cout << "Process " << processArr[i].id << ":\n";
        cout << "Arrival time = " << processArr[i].arrivalTime << "\n";
        cout << "Burst time = " << processArr[i].burstTime << "\n";
        cout << "Completion time = " << processArr[i].completionTime << "\n";
        cout << "Turnaround time = " << processArr[i].turnaroundTime << "\n";
        cout << "Waiting time = " << processArr[i].waitingTime << "\n";
        cout << "\n";
    }
}