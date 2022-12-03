#include <iostream>
#include <algorithm>
using namespace std;

class element
{
public:
    int data;
    char dir;
};

void print_LCS_matrix(string s, string t, element **dp)
{
    for (int i = 1; i < t.size() + 1; i++)
    {
        for (int j = 1; j < s.size() + 1; j++)
        {
            if (s[j - 1] == t[i - 1]) // same character
            {
                dp[i][j].data = dp[i - 1][j - 1].data + 1;
                dp[i][j].dir = 'd';
            }
            else // different character
            {
                if (dp[i][j - 1].data > dp[i - 1][j].data) // left greater than top
                {
                    dp[i][j].data = dp[i][j - 1].data;
                    dp[i][j].dir = 'l';
                }
                else if (dp[i][j - 1].data < dp[i - 1][j].data) // top greater than left
                {
                    dp[i][j].data = dp[i - 1][j].data;
                    dp[i][j].dir = 'u';
                }
                else // top and left equal
                {
                    dp[i][j].data = dp[i - 1][j].data;
                    dp[i][j].dir = 'u';
                }
            }
        }
    }

    for (int i = 0; i < t.size() + 1; i++)
    {
        for (int j = 0; j < s.size() + 1; j++)
        {
            if (i == 0 || j == 0)
            {
                cout << dp[i][j].data << dp[i][j].dir << "  ";
                continue;
            }
            cout << dp[i][j].data << dp[i][j].dir << " ";
        }

        cout << endl;
    }
}

void printLCS(string s, string t, element **dp)
{
    string ans = "";
    int i = t.size();
    int j = s.size();
    while (i > 0 && j > 0)
    {
        if (dp[i][j].dir == 'u')
        {
            i--;
        }
        if (dp[i][j].dir == 'l')
        {
            j--;
        }
        if (dp[i][j].dir == 'd')
        {
            ans += s[j - 1];
            i--;
            j--;
        }
    }

    reverse(ans.begin(), ans.end());
    cout << "LCS: " << ans << endl;
}

int main()
{
    // string s = "bcfgh"; //LCS = bcfg
    // string t = "abcdefg";
    cout << "Enter first string: ";
    string s;
    cin >> s;
    cout << "Enter second string: ";
    string t;
    cin >> t;
    element **dp = new element *[t.size() + 1];
    for (int i = 0; i < t.size() + 1; i++)
    {
        dp[i] = new element[s.size() + 1];
    }

    for (int i = 0; i < s.size() + 1; i++)
    {
        dp[0][i].data = 0;
    }

    for (int i = 0; i < t.size() + 1; i++)
    {
        dp[i][0].data = 0;
    }

    print_LCS_matrix(s, t, dp);
    printLCS(s, t, dp);

    for (int i = 0; i < t.size() + 1; i++)
    {
        delete[] dp[i];
    }

    delete[] dp;

    return 0;
}