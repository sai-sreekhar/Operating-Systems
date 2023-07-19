#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int checkHit(int incomingPage, vector<int> queueVec, int occupied)
{
    for (int i = 0; i < occupied; i++)
    {
        if (incomingPage == queueVec[i])
        {
            return 1;
        }
    }

    return 0;
}

void printFrame(vector<int> queueVec, int occupied)
{
    for (int i = 0; i < occupied; i++)
    {
        printf("%d\t\t\t", queueVec[i]);
    }
}

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

    vector<int> queueVec(noOfFrames);
    vector<int> distanceVec(noOfFrames);
    int occupied = 0;
    int pageFaultCount = 0;

    printf("Page\t Frame1 \t Frame2 \t Frame3\n");

    for (int i = 0; i < noOfPages; i++)
    {
        printf("%d:  \t\t", incomingStreamVec[i]);
        if (checkHit(incomingStreamVec[i], queueVec, occupied))
        {
            printFrame(queueVec, occupied);
        }
        else if (occupied < noOfFrames)
        {
            queueVec[occupied] = incomingStreamVec[i];
            pageFaultCount++;
            occupied++;

            printFrame(queueVec, occupied);
        }
        else
        {
            int max = INT_MIN;
            int index;
            for (int j = 0; j < noOfFrames; j++)
            {
                distanceVec[j] = 0;
                for (int k = i + 1; k < noOfPages; k++)
                {
                    ++distanceVec[j];
                    if (queueVec[j] == incomingStreamVec[k])
                    {
                        break;
                    }
                }
                if (distanceVec[j] > max)
                {
                    max = distanceVec[j];
                    index = j;
                }
            }

            queueVec[index] = incomingStreamVec[i];
            printFrame(queueVec, occupied);
            pageFaultCount++;
        }

        printf("\n");
    }

    printf("\nTotal Page Faults:\t%d\n", pageFaultCount);
    printf("Total Page Hits:\t%d\n", noOfPages - pageFaultCount);
    printf("Page Fault Rate:\t%f\n", (float)pageFaultCount / (float)noOfPages);
    printf("Page Hit Rate:\t\t%f\n", (float)(noOfPages - pageFaultCount) / (float)noOfPages);

    return 0;
}