#include <bits/stdc++.h>
using namespace std;

int main()
{
    int noOfProcesses;
    // cout << "Enter the number of processes: ";
    cin >> noOfProcesses;

    int noOfResources;
    // cout << "Enter the number of resources: ";
    cin >> noOfResources;

    vector<int> totalAvailable(noOfResources);
    vector<vector<int>> maxNeed(noOfProcesses, vector<int>(noOfResources));
    vector<vector<int>> allocated(noOfProcesses, vector<int>(noOfResources));
    vector<vector<int>> remainingNeed(noOfProcesses, vector<int>(noOfResources));

    for (int i = 0; i < noOfResources; i++)
    {
        // cout << "Enter the total available resources of resource " << i << ": ";
        cin >> totalAvailable[i];
    }

    for (int i = 0; i < noOfProcesses; i++)
    {
        // cout << "Enter the allocated resources of process " << i << ": ";
        for (int j = 0; j < noOfResources; j++)
        {
            cin >> allocated[i][j];
        }
        // cout << "Enter the maximum need of process " << i << ": ";
        for (int j = 0; j < noOfResources; j++)
        {
            cin >> maxNeed[i][j];
        }
    }

    for (int i = 0; i < noOfProcesses; i++)
    {
        for (int j = 0; j < noOfResources; j++)
        {
            remainingNeed[i][j] = maxNeed[i][j] - allocated[i][j];
        }
    }

    vector<int> available(noOfResources);
    for (int i = 0; i < noOfResources; i++)
    {
        int temp = 0;
        for (int j = 0; j < noOfProcesses; j++)
        {
            temp += allocated[j][i];
        }
        available[i] = totalAvailable[i] - temp;
    }

    vector<int> sizeVec(noOfProcesses, -1);

    queue<int> readyQueue;
    for (int i = 0; i < noOfProcesses; i++)
    {
        readyQueue.push(i);
    }

    while (!readyQueue.empty())
    {
        int idx = readyQueue.front();
        readyQueue.pop();
        bool isPossible = true;
        for (int i = 0; i < noOfResources; i++)
        {
            if (remainingNeed[idx][i] > available[i])
            {
                isPossible = false;
                break;
            }
        }
        if (isPossible)
        {
            cout << "Process " << idx << " is possible\n";
            for (int i = 0; i < noOfResources; i++)
            {
                available[i] += allocated[idx][i];
            }
        }
        else
        {
            // cout << "Process " << idx << " is not possible\n";
            readyQueue.push(idx);
            if (sizeVec[idx] != -1 && sizeVec[idx] == readyQueue.size())
            {
                cout << "Deadlock detected\n";
                break;
            }

            sizeVec[idx] = readyQueue.size();
        }
    }
}

/*
5
3
10 5 7
0 1 0 7 5 3
2 0 0 3 2 2
3 0 2 9 0 2
2 1 1 4 2 2
0 0 2 5 3 3
*/