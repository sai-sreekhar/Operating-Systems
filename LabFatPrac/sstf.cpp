#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <queue>
using namespace std;
int currHeadPos = 0;

struct compare
{
    bool operator()(int p1, int p2)
    {
        return abs(currHeadPos - p1) > abs(currHeadPos - p2);
    }
};

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

    currHeadPos = initialHead;

    priority_queue<int, vector<int>, compare> pq;
    for (int i = 0; i < n; i++)
    {
        pq.push(procReqs[i]);
    }

    int res = 0;
    while (!pq.empty())
    {
        int curr = pq.top();
        cout << curr << "\n";
        res += abs(currHeadPos - curr);
        currHeadPos = curr;
        pq.pop();
    }

    cout << "Total number of seek operations = " << res << endl;
    return 0;
}
