#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;

void firstComeFirstServe(vector<int>& requests, int initialHead)
{
    int seekCount = 0;
    int distance, currentTrack;

    for (int i = 0; i < requests.size(); i++)
    {
        currentTrack = requests[i];

        distance = abs(currentTrack - initialHead);

        seekCount += distance;

        initialHead = currentTrack;
    }

    cout << "Total number of seek operations = " << seekCount << endl;

    cout << "Seek Sequence is" << endl;

    for (int i = 0; i < requests.size(); i++)
    {
        cout << requests[i] << endl;
    }
}

int main()
{
    int n;
    cout << "Enter the number of process requests: ";
    cin >> n;

    vector<int> procRequests(n);
    cout << "Enter the process requests: ";
    for (int i = 0; i < n; i++)
    {
        cin >> procRequests[i];
    }

    int initialHead;
    cout << "Enter the initial head position: ";
    cin >> initialHead;

    firstComeFirstServe(procRequests, initialHead);

    return 0;
}
