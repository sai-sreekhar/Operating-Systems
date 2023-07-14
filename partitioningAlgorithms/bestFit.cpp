#include <iostream>
#include <vector>

void bestFit(std::vector<int> blockSizeVec, int noOfBlocks, std::vector<int> processSizeVec, int noOfProcess)
{
    std::vector<int> allocationVec(noOfProcess, -1);
    for (int i = 0; i < noOfProcess; i++)
    {
        int indexPos = -1;
        for (int j = 0; j < noOfBlocks; j++)
        {
            if (blockSizeVec[j] >= processSizeVec[i])
            {
                if (indexPos == -1)
                {
                    indexPos = j;
                }
                else if (blockSizeVec[j] < blockSizeVec[indexPos])
                {
                    indexPos = j;
                }
            }
        }

        if (indexPos != -1)
        {
            allocationVec[i] = indexPos;
            blockSizeVec[indexPos] -= processSizeVec[i];
        }
    }

    printf("\nProcess No.\tProcess Size\t\t\tBlock no.\n");
    for (int i = 0; i < noOfProcess; i++)
    {
        printf("%d \t\t\t %d \t\t\t", i + 1, processSizeVec[i]);
        if (allocationVec[i] != -1)
        {
            printf("%d\n", allocationVec[i] + 1);
        }
        else
        {
            printf("Not Allocated\n");
        }
    }
}

int main()
{
    int noOfBlocks, noOfProcesses;

    std::cout << "Enter the number of noOfBlocks: ";
    std::cin >> noOfBlocks;

    std::vector<int> blockSizeVec(noOfBlocks);
    std::cout << "Enter the block sizes: ";
    for (int i = 0; i < noOfBlocks; i++)
    {
        std::cin >> blockSizeVec[i];
    }

    std::cout << "Enter the number of noOfProcess: ";
    std::cin >> noOfProcesses;

    std::vector<int> processSizeVec(noOfProcesses);
    std::cout << "Enter the process sizes: ";
    for (int i = 0; i < noOfProcesses; i++)
    {
        std::cin >> processSizeVec[i];
    }

    bestFit(blockSizeVec, noOfBlocks, processSizeVec, noOfProcesses);
    return 0;
}