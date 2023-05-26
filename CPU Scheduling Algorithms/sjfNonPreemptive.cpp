#include <bits/stdc++.h>
using namespace std;
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sortArrivalTimes(int num, vector<vector<int>> &matrix)
{
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num - i - 1; j++)
        {
            if (matrix[1][j] > matrix[1][j + 1])
            {
                for (int k = 0; k < 5; k++)
                {
                    swap(matrix[k][j], matrix[k][j + 1]);
                }
            }
        }
    }
}
void completionTime(int num, vector<vector<int>> &matrix)
{
    int temp, val;
    matrix[3][0] = matrix[1][0] + matrix[2][0];
    matrix[5][0] = matrix[3][0] - matrix[1][0];
    matrix[4][0] = matrix[5][0] - matrix[2][0];
    for (int i = 1; i < num; i++)
    {
        temp = matrix[3][i - 1];
        int low = matrix[2][i];
        for (int j = i; j < num; j++)
        {
            if (temp >= matrix[1][j] && low >= matrix[2][j])
            {
                low = matrix[2][j];
                val = j;
            }
        }
        matrix[3][val] = temp + matrix[2][val];
        matrix[5][val] = matrix[3][val] - matrix[1][val];
        matrix[4][val] = matrix[5][val] - matrix[2][val];
        for (int k = 0; k < 6; k++)
        {
            swap(matrix[k][val], matrix[k][i]);
        }
    }
}
int main()
{
    int num, temp;
    cout << "Enter the number of processes:\n";
    cin >> num;
    vector<vector<int>> matrix(6, vector<int>(num));
    for (int i = 0; i < num; i++)
    {
        matrix[0][i] = i + 1;
        cout << "Enter the arrival time of process " << i + 1 << ":\n";
        cin >> matrix[1][i];
        cout << "Enter the burst time of process " << i + 1 << ":\n";
        cin >> matrix[2][i];
    }

    sortArrivalTimes(num, matrix);
    completionTime(num, matrix);
    cout << "Final Result...\n";
    cout << "Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
    int totalWt = 0;
    int totalTat = 0;
    for (int i = 0; i < num; i++)
    {
        cout << matrix[0][i] << "\t\t" << matrix[1][i] << "\t\t" << matrix[2][i] << "\t\t" << matrix[4][i] << "\t\t" << matrix[5][i] << "\n";
        totalWt += matrix[4][i];
        totalTat += matrix[5][i];
    }

    cout << "Average waiting time: " << (float)totalWt / (float)num << "\n";
    cout << "Average turnaround time: " << (float)totalTat / (float)num << "\n";
}