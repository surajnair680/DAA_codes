#include<iostream>
#include<vector>

using namespace std;

void generateGraph(vector<vector<int> > &edges, int v)
{
    int edgeCount = 0;

    for(int i=0; i<v; i++)
    {
        for(int j=0; j<v; j++)
        {
            if(i<j)
            {
                edges[edgeCount].push_back(i);
                edges[edgeCount].push_back(j);
                int randomWeight = rand() % (20 - 1 + 1) + 1;
                edges[edgeCount].push_back(randomWeight);
                edgeCount++;
            }
            

        }
    }
}

int main()
{
    int v1 = 8;
    int e1 = v1*(v1-1)/2;
    vector<vector<int> > edges1(e1);

    generateGraph(edges1, v1);

    for(int i=0; i<e1; i++)
    {
        cout << edges1[i][0] << " " << edges1[i][1] << " " << edges1[i][2] << endl;
    }

    return 0;
}