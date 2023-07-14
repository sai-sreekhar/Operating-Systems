#include <iostream>
#include <vector>
using namespace std;

int find(int key, vector<int> frameVec, int frameOccupied)
{
    for (int i = 0; i < frameOccupied; i++)
    {
        if (frameVec[i] == key)
        {
            return 1;
        }
    }
    return 0;
}

void displayOuterFrames(int noOfFrames)
{
    printf("Stream ");

    for (int i = 0; i < noOfFrames; i++)
    {
        printf("Frame%d ", i + 1);
    }
}

void printCurrFrames(int item, vector<int> frameVec, int frameOccupied, int noOfFrames)
{

    printf("\n%d \t\t", item);

    for (int i = 0; i < noOfFrames; i++)
    {
        if (i < frameOccupied)
        {
            printf("%d \t\t", frameVec[i]);
        }
        else
        {
            printf("- \t\t");
        }
    }
}

int predict(vector<int> incomingStreamVec, vector<int> frameVec, int noOfPages, int idx, int frameOccupied)
{

    int result = -1, farthestFrame = idx;
    for (int i = 0; i < frameOccupied; i++)
    {
        int j;
        for (j = idx; j < noOfPages; j++)
        {
            if (frameVec[i] == incomingStreamVec[j])
            {
                if (j > farthestFrame)
                {
                    farthestFrame = j;
                    result = i;
                }
                break;
            }
        }

        if (j == noOfPages)
        {
            return i;
        }
    }

    if (result == -1)
    {
        return 0;
    }
    return result;
}

void optimalPage(vector<int> incomingStreamVec, int noOfPages, vector<int> frameVec, int noOfFrames)
{

    int frameOccupied = 0;
    displayOuterFrames(noOfFrames);

    int hits = 0;
    for (int i = 0; i < noOfPages; i++)
    {

        if (find(incomingStreamVec[i], frameVec, frameOccupied))
        {
            hits++;
            printCurrFrames(incomingStreamVec[i], frameVec, frameOccupied, noOfFrames);
            continue;
        }

        if (frameOccupied < noOfFrames)
        {
            frameVec[frameOccupied] = incomingStreamVec[i];
            frameOccupied++;
            printCurrFrames(incomingStreamVec[i], frameVec, frameOccupied, noOfFrames);
        }
        else
        {
            int pos = predict(incomingStreamVec, frameVec, noOfPages, i + 1, frameOccupied);
            frameVec[pos] = incomingStreamVec[i];
            printCurrFrames(incomingStreamVec[i], frameVec, frameOccupied, noOfFrames);
        }
    }

    printf("\nTotal Page Faults:\t%d\n", noOfPages - hits);
    printf("Total Page Hits:\t%d\n", hits);
    printf("Page Fault Rate:\t%f\n", (float)(noOfPages - hits) / (float)noOfPages);
    printf("Page Hit Rate:\t\t%f\n", (float)(hits) / (float)noOfPages);
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

    vector<int> frameVec(noOfFrames);
    optimalPage(incomingStreamVec, noOfPages, frameVec, noOfFrames);
    return 0;
}