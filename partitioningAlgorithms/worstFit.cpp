#include <iostream>
#include <vector>

void worstFit(std::vector<int> blockSize, int noOfBlocks, std::vector<int> processSize, int noOfProcess)
{
    std::vector<int> allocationVec(noOfProcess, -1);
    for (int i = 0; i < noOfProcess; i++)
    {

        int indexPlaced = -1;
        for (int j = 0; j < noOfBlocks; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (indexPlaced == -1)
                {
                    indexPlaced = j;
                }
                else if (blockSize[indexPlaced] < blockSize[j])
                {
                    indexPlaced = j;
                }
            }
        }

        if (indexPlaced != -1)
        {
            allocationVec[i] = indexPlaced;
            blockSize[indexPlaced] -= processSize[i];
        }
    }

    printf("\nProcess No.\tProcess Size\t\t\tBlock no.\n");
    for (int i = 0; i < noOfProcess; i++)
    {
        printf("%d \t\t\t %d \t\t\t", i + 1, processSize[i]);
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

    std::vector<int> blockSize(noOfBlocks);
    std::cout << "Enter the block sizes: ";
    for (int i = 0; i < noOfBlocks; i++)
    {
        std::cin >> blockSize[i];
    }

    std::cout << "Enter the number of noOfProcess: ";
    std::cin >> noOfProcesses;

    std::vector<int> processSize(noOfProcesses);
    std::cout << "Enter the process sizes: ";
    for (int i = 0; i < noOfProcesses; i++)
    {
        std::cin >> processSize[i];
    }

    worstFit(blockSize, noOfBlocks, processSize, noOfProcesses);
    return 0;
}