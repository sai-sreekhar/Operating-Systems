#include <iostream>
#include <vector>

using namespace std;

bool isSafe(vector<vector<int>> &max, vector<vector<int>> &allocation, vector<int> &available, vector<bool> &finish)
{
    int numProcesses = max.size();
    int numResources = available.size();

    vector<vector<int>> need(numProcesses, vector<int>(numResources));

    for (int i = 0; i < numProcesses; ++i)
    {
        for (int j = 0; j < numResources; ++j)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    vector<int> work = available;
    vector<int> safeSequence;

    while (safeSequence.size() < numProcesses)
    {
        bool found = false;
        for (int i = 0; i < numProcesses; ++i)
        {
            if (!finish[i])
            {
                bool canAllocate = true;
                for (int j = 0; j < numResources; ++j)
                {
                    if (need[i][j] > work[j])
                    {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate)
                {
                    for (int j = 0; j < numResources; ++j)
                    {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    safeSequence.push_back(i);
                    found = true;
                }
            }
        }

        if (!found)
        {
            break;
        }
    }

    if (safeSequence.size() == numProcesses)
    {
        cout << "Safe sequence: ";
        for (int i = 0; i < numProcesses; ++i)
        {
            cout << safeSequence[i];
            if (i != numProcesses - 1)
            {
                cout << " -> ";
            }
        }
        cout << endl;

        return true;
    }
    else
    {
        return false;
    }
}

bool isRequestSafe(vector<vector<int>> &max, vector<vector<int>> &allocation, vector<int> &available, vector<bool> &finish, int processId, vector<int> &request)
{
    int numProcesses = max.size();
    int numResources = available.size();

    vector<vector<int>> need(numProcesses, vector<int>(numResources));

    for (int i = 0; i < numProcesses; ++i)
    {
        for (int j = 0; j < numResources; ++j)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    for (int j = 0; j < numResources; ++j)
    {
        if (request[j] > need[processId][j] || request[j] > available[j])
        {
            return false;
        }
    }

    for (int j = 0; j < numResources; ++j)
    {
        available[j] -= request[j];
        allocation[processId][j] += request[j];
        need[processId][j] -= request[j];
    }

    vector<bool> tempFinish = finish;
    tempFinish[processId] = true;
    bool isSafeState = isSafe(max, allocation, available, tempFinish);

    for (int j = 0; j < numResources; ++j)
    {
        available[j] += request[j];
        allocation[processId][j] -= request[j];
        need[processId][j] += request[j];
    }

    return isSafeState;
}

int main()
{
    cout << "--------------------Banker's Algorithm--------------------\n";
    cout << "--------------------Sai Sreekar 21BDS0387--------------------\n";

    int numProcesses, numResources;
    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    cout << "Enter the number of resources: ";
    cin >> numResources;

    vector<vector<int>> max(numProcesses, vector<int>(numResources));
    vector<vector<int>> allocation(numProcesses, vector<int>(numResources));
    vector<int> available(numResources);
    vector<bool> finish(numProcesses, false);

    cout << "Enter the maximum demand matrix:\n";
    for (int i = 0; i < numProcesses; ++i)
    {
        cout << "For process " << i << ":\n";
        for (int j = 0; j < numResources; ++j)
        {
            cin >> max[i][j];
        }
    }

    cout << "Enter the allocation matrix:\n";
    for (int i = 0; i < numProcesses; ++i)
    {
        cout << "For process " << i << ":\n";
        for (int j = 0; j < numResources; ++j)
        {
            cin >> allocation[i][j];
        }
    }

    cout << "Enter the available resources:\n";
    for (int i = 0; i < numResources; ++i)
    {
        cin >> available[i];
    }

    if (isSafe(max, allocation, available, finish))
    {
        cout << "The system is in a safe state.\n";
    }
    else
    {
        cout << "The system is in an unsafe state.\n";
    }

    int processId;
    vector<int> request(numResources);

    cout << "Enter the process ID for the additional request: ";
    cin >> processId;

    cout << "Enter the additional request vector:\n";
    for (int i = 0; i < numResources; ++i)
    {
        cin >> request[i];
    }

    if (isRequestSafe(max, allocation, available, finish, processId, request))
    {
        cout << "The additional request can be granted while maintaining a safe state.\n";
    }
    else
    {
        cout << "The additional request cannot be granted while maintaining a safe state.\n";
    }

    return 0;
}
