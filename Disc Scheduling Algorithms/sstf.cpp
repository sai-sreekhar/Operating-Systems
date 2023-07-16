#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;

void calculateDifference(vector<int> &req, int h, vector<vector<int>> &diff, int n)
{
    for (int i = 0; i < n; i++)
    {
        diff[i][0] = abs(h - req[i]);
    }
}

int findMinIndex(vector<vector<int>> &diff, int n)
{
    int idx = -1;
    int minVal = 1e9;

    for (int i = 0; i < n; i++)
    {
        if (!diff[i][1] && minVal > diff[i][0])
        {
            minVal = diff[i][0];
            idx = i;
        }
    }
    return idx;
}

void shortestSeekTimeFirst(vector<int> &req, int initialHead, int n)
{
    if (n == 0)
    {
        return;
    }

    vector<vector<int>> diff(n, vector<int>(2, 0));
    int seekCnt = 0;
    vector<int> seekSeq(n + 1, 0);

    for (int i = 0; i < n; i++)
    {
        seekSeq[i] = initialHead;
        calculateDifference(req, initialHead, diff, n);
        int index = findMinIndex(diff, n);
        diff[index][1] = 1;
        seekCnt += diff[index][0];
        initialHead = req[index];
    }
    seekSeq[n] = initialHead;

    cout << "Total number of seek operations = " << seekCnt << endl;
    cout << "Seek sequence is : " << endl;

    for (int i = 0; i <= n; i++)
    {
        cout << seekSeq[i] << endl;
    }
}

int main()
{
    int n;
    cout << "Enter the number of process requests: ";
    cin >> n;

    vector<int> procReqs(n);
    cout << "Enter the process requests: ";
    for (int i = 0; i < n; i++)
    {
        cin >> procReqs[i];
    }

    int initialHead;
    cout << "Enter the initial head position: ";
    cin >> initialHead;

    shortestSeekTimeFirst(procReqs, initialHead, n);

    return 0;
}
