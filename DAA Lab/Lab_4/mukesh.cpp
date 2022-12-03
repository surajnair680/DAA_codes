#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    int n1, n2;
    cout << "\n Enter the size of first string: ";
    cin >> n1;
    char ch1[n1];
    cout << "\n Enter the characters of first string:";
    for (int i = 0; i < n1; i++)
    {
        cin >> ch1[i];
    }
    cout << "\n Enter the size of second string: ";
    cin >> n2;
    char ch2[n2];
    cout << "\n Enter the characters of second string:";
    for (int i = 0; i < n2; i++)
    {
        cin >> ch2[i];
    }
    cout << "\n first string:";
    for (int i = 0; i < n1; i++)
    {
        cout << ch1[i];
    }
    cout << "\n second string:";
    for (int i = 0; i < n2; i++)
    {
        cout << ch2[i];
    }
    int a[50][50];
    char b[50][50];
    for (int i = 1; i < n1; i++)
    {
        for (int j = 0; j < n2; j++)
        {
            if (i == 0 || j == 0)
            {
                a[i][j] = 0;
            }
        }
    }
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < n2; j++)
        {
            if (ch1[i] == ch2[j])
            {
                a[i][j] = a[i - 1][j - 1] + 1;
                b[i][j] = 'D';
            }
            else if (a[i - 1][j] >= a[i][j - 1])
            {
                a[i][j] = a[i - 1][j];
                b[i][j] = 'U';
            }
            else
            {
                a[i][j] = a[i][j - 1];
                b[i][j] = '-';
            }
        }
    }
    for (int i = 0; i < n1; i++)
    {
        cout << "\n";
        for (int j = 0; j < n2; j++)
        {
            cout << a[i][j] << b[i][j] << "\t";
        }
    }
}