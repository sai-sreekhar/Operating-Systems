#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int noOfPages;
    cout << "Enter the number of incoming streams: ";
    cin >> noOfPages;
    vector<int> incomingStreamVec(noOfPages);
    cout << "Enter the incoming streams: ";
    for (int i = 0; i < noOfPages; i++)
    {
        cin >> incomingStreamVec[i];
    }
    int noOfFrames;
    cout << "Enter the number of frames: ";
    cin >> noOfFrames;

    int pageFaultsCount = 0;
    int tempVar;

    printf("Incoming \t Frame 1 \t Frame 2 \t Frame 3");
    vector<int> tempVec(noOfFrames, -1);
    for (int i = 0; i < noOfPages; i++)
    {
        tempVar = 0;

        for (int j = 0; j < noOfFrames; j++)
        {
            if (incomingStreamVec[i] == tempVec[j])
            {
                tempVar++;
                pageFaultsCount--;
            }
        }
        pageFaultsCount++;

        if ((pageFaultsCount <= noOfFrames) && (tempVar == 0))
        {
            tempVec[i] = incomingStreamVec[i];
        }
        else if (tempVar == 0)
        {
            tempVec[(pageFaultsCount - 1) % noOfFrames] = incomingStreamVec[i];
        }

        printf("\n");
        printf("%d\t\t\t", incomingStreamVec[i]);
        for (int k = 0; k < noOfFrames; k++)
        {
            if (tempVec[k] != -1)
            {
                printf(" %d\t\t\t", tempVec[k]);
            }
            else
            {
                printf(" - \t\t\t");
            }
        }
    }

    printf("\nTotal Page Faults:\t%d\n", pageFaultsCount);
    printf("Total Page Hits:\t%d\n", noOfPages - pageFaultsCount);
    printf("Page Fault Rate:\t%f\n", (float)pageFaultsCount / (float)noOfPages);
    printf("Page Hit Rate:\t\t%f\n", (float)(noOfPages - pageFaultsCount) / (float)noOfPages);
    
    return 0;
}