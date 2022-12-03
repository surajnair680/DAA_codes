#include <iostream>
#include <string>
using namespace std;

int LCS(string s, string t)
{
    if (s.size() == 0 || t.size() == 0)
    {
        return 0;
    }

    if (s[0] == t[0]) // first character of both strings are same
    {
        return 1 + LCS(s.substr(1), t.substr(1));
    }
    else
    {
        int l1 = LCS(s.substr(1), t.substr(1));
        int l2 = LCS(s, t.substr(1));
        int l3 = LCS(s.substr(1), t);
        return max(l1, max(l2, l3));
    }
}

int LCSDP(string s, string t)
{
    int slen = s.size();
    int tlen = t.size();
    int **output = new int *[slen + 1];
    for (int i = 0; i < slen + 1; i++)
        output[i] = new int[tlen + 1];

    for (int i = 0; i < slen + 1; i++) // filling first column with zeros
    {
        output[i][0] = 0;
    }

    for (int i = 0; i < tlen + 1; i++) // filling first row with zeros
    {
        output[0][i] = 0;
    }

    for (int i = 1; i <= slen; i++)
    {
        for (int j = 1; j <= tlen; j++)
        {
            if (s[slen - i] == t[tlen - j]) // first character of both strings match
            {
                output[i][j] = 1 + output[i - 1][j - 1];
            }
            else
            {
                int a = output[i - 1][j];
                int b = output[i][j - 1];
                int c = output[i - 1][j - 1];
                output[i][j] = max(a, max(b, c));
            }
        }
    }

    for (int i = 0; i < slen + 1; i++)
    {
        for (int j = 0; j < tlen + 1; j++)
        {
            cout << output[i][j] << " ";
        }

        cout << endl;
    }

    return output[slen][tlen];
}

int main()
{
    cout << LCS("abcdefg", "bcfgh") << endl;
    cout << LCSDP("abcdefg", "bcfgh") << endl;

    return 0;
}
