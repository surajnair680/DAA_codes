#include <iostream>
using namespace std;

int solveDP(int *arr, int **dp, int n, int **paranthesizationMatrix)
{
    int temp;
    int minans;
    for (int i = n - 1; i >= 1; i--)
    {
        for (int j = i + 1; j < n; j++)
        {
            int minval = INT_MAX;
            int paranthesization;
            minval = INT_MAX;
            for (int k = i; k < j; k++)
            {
                temp = dp[i][k] + dp[k + 1][j] + arr[i - 1] * arr[k] * arr[j];
                if (temp < minval)
                {
                    minval = temp;
                    paranthesization = k;
                }
            }
            dp[i][j] = minval;
            paranthesizationMatrix[i][j] = paranthesization;
        }
    }
    return dp[1][n - 1];
}

void printMatrix(int **dp, int n)
{
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < n; j++)
        {
            cout << dp[i][j] << " ";
        }

        cout << endl;
    }
}

void printParanthesizationMatrix(int **paranthesizationMatrix, int n)
{
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < n; j++)
        {
            cout << paranthesizationMatrix[i][j] << " ";
        }

        cout << endl;
    }
}

int main()
{
    cout << "Enter the number of matrices: ";
    int N;
    cin >> N;
    cout << "Enter the dimension array" << endl;
    int arr[N + 1];
    for (int i = 0; i < N + 1; i++)
    {
        cin >> arr[i];
    }

    int n = N + 1;

    // int arr[6] = {4, 10, 3, 12, 20, 7};

    int **dp = new int *[n];
    for (int i = 0; i < n; i++)
    {
        dp[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            dp[i][j] = 0;
        }
    }

    int **paranthesizationMatrix = new int *[n];
    for (int i = 0; i < n; i++)
    {
        paranthesizationMatrix[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            paranthesizationMatrix[i][j] = 0;
        }
    }

    cout << "MINIMUM COST: " << solveDP(arr, dp, n, paranthesizationMatrix) << endl << endl;

    printMatrix(dp, n);
    cout << endl;
    printParanthesizationMatrix(paranthesizationMatrix, n);

    return 0;
}