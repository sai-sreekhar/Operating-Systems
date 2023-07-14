#include <iostream>
#include <vector>

using namespace std;

bool isSafe(vector<vector<int>> &maxDemand, vector<vector<int>> &allocation, vector<int> &available, vector<bool> &finish)
{
    int numProcesses = maxDemand.size();
    int numResources = available.size();

    vector<vector<int>> need(numProcesses, vector<int>(numResources));

    for (int i = 0; i < numProcesses; ++i)
    {
        for (int j = 0; j < numResources; ++j)
        {
            need[i][j] = maxDemand[i][j] - allocation[i][j];
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
        cout << "\n";

        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    int numProcesses, numResources;
    cout << "--------------------Banker's Algorithm--------------------\n";
    cout << "--------------------Sai Sreekar 21BDS0387--------------------\n";

    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    cout << "Enter the number of resources: ";
    cin >> numResources;

    vector<vector<int>> maxDemand(numProcesses, vector<int>(numResources));
    vector<vector<int>> allocation(numProcesses, vector<int>(numResources));
    vector<int> available(numResources);
    vector<bool> finish(numProcesses, false);

    cout << "Enter the maximum demand matrix:\n";
    for (int i = 0; i < numProcesses; ++i)
    {
        cout << "For process " << i << ":\n";
        for (int j = 0; j < numResources; ++j)
        {
            cin >> maxDemand[i][j];
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

    if (isSafe(maxDemand, allocation, available, finish))
    {
        cout << "The system is in a safe state.\n";
    }
    else
    {
        cout << "The system is in an unsafe state.\n";
    }

    return 0;
}
