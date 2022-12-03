#include<iostream>
#include<algorithm>
#include<unordered_map>
using namespace std;

int w[10], x[10], d; //input array, bool array to include and disclude element and target sum

void sum_subset(int s, int k, int r) //s=current sum, k=current index, r=remaining sum
{
    static int b=1; //number of subsets
    x[k] = 1;

    if(s+w[k]==d)
    {
        cout << "Subset " << b++ << ": ";
        for(int i=0; i<=k; i++)
        {
            if(x[i]==1)
            {
                cout << w[i] << " ";
            } 
        }
        cout << endl;
    }
    else if(s+w[k]+w[k+1]<=d)
    {
        sum_subset(s+w[k], k+1, r-w[k]);
    }
    if((s+r-w[k]>=d) && (s+w[k+1]<=d))
    {
        x[k]=0;
        sum_subset(s,k+1,r-w[k]);
    }

}

int main()
{
    int n,i,sum=0;
    cout << "Enter number of elements: ";
    cin >> n;
    cout << "Enter the elements:-" << endl;

    for(int i=0; i<n; i++)
    {
        cin >> w[i];
        sum+=w[i];
    }

    sort(w,w+n);

    cout << "Enter the target sum: ";
    cin >> d;

    if(sum<d || w[0]>d)
    {
        cout << "Solution does not exist" << endl;
    }
    else
    {
        sum_subset(0,0,sum);
    }
    
    return 0;
}