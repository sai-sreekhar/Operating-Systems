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

    int currTime = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    int minArrivalTimeIdx = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        if (processArr[i].arrivalTime < minArrivalTimeIdx)
        {
            minArrivalTimeIdx = i;
        }
    }
    currTime = processArr[minArrivalTimeIdx].arrivalTime;
    pq.push({processArr[minArrivalTimeIdx].burstTime, minArrivalTimeIdx});

    while (!pq.empty())
    {
        for (int i = 0; i < n; i++)
        {
            if (processArr[i].arrivalTime == currTime && i != minArrivalTimeIdx)
            {
                pq.push({processArr[i].burstTime, i});
            }
        }
        pair<int, int> curr = pq.top();
        pq.pop();
        curr.first -= 1;
        if (curr.first != 0)
        {
            pq.push(curr);
        }
        else
        {
            processArr[curr.second].completionTime = currTime + 1;
            processArr[curr.second].turnaroundTime = processArr[curr.second].completionTime - processArr[curr.second].arrivalTime;
            processArr[curr.second].waitingTime = processArr[curr.second].turnaroundTime - processArr[curr.second].burstTime;
        }
        currTime++;
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