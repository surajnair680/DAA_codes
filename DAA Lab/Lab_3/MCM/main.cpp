#include <iostream>
#include <climits>
using namespace std;

int solveMem(int *input, int i, int j, int **dp)
{
    if (i >= j)
        return 0;

    if (dp[i][j] != -1)
        return dp[i][j];

    int min = INT_MAX;
    for (int k = i; k <= j - 1; k++)
    {
        int tempAns = solveMem(input, i, k, dp) + solveMem(input, k + 1, j, dp) + input[i - 1] * input[k] * input[j];
        if (tempAns < min)
            min = tempAns;
    }

    dp[i][j] = min;
    return dp[i][j];
}

int solve(int *input, int i, int j)
{
    if (i >= j)
        return 0;

    int min = INT_MAX;
    for (int k = i; k <= j - 1; k++)
    {
        int tempAns = solve(input, i, k) + solve(input, k + 1, j) + input[i - 1] * input[k] * input[j];
        if (tempAns < min)
            min = tempAns;
    }

    return min;
}

int main()
{
    int input[6] = {4, 10, 3, 12, 20, 7};

    int **dp = new int *[6];
    for (int i = 0; i < 6; i++)
    {
        dp[i] = new int[6];
        for (int j = 0; j < 6; j++)
            dp[i][j] = -1;
    }

    cout << solve(input, 1, 5) << endl;
    cout << solveMem(input, 1, 5, dp) << endl;

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            cout << dp[i][j] << " ";
        }

        cout << endl;
    }

    return 0;
}