#include<iostream>
#include<vector>
#include<climits>
using namespace std;

int findMinVertex(int *weights, bool *visited, int n)
{
    int minVertex = -1;
    for (int i = 0; i < n; i++)
    {
        if (!visited[i] && (minVertex == -1 || weights[i] < weights[minVertex]))
        {
            minVertex = i;
        }
    }
    return minVertex;
}

void MST_using_prim(vector<vector<int> > edges, int n)
{
    int *parent = new int[n];
    int *weights = new int[n];
    bool *visited = new bool[n];

    for(int i=0; i<n; i++)
    {
        visited[i] = false;
        weights[i] = INT_MAX;
        parent[i] = -1;
    }

    weights[0] = 0;

    for(int i=0; i<n-1; i++)
    {
        int minVertex = findMinVertex(weights, visited, n);
        cout << minVertex << endl;
        visited[minVertex] = true;
        
        // Scan all adjacent unvisited nodes and update weights array and parent array accordingly
        for(int j=0; j<edges.size(); j++)
        {
            if(edges[j][0]==minVertex && !visited[edges[j][1]])
            {
                if(edges[j][2] < weights[edges[j][1]])
                {
                    weights[edges[j][1]] = edges[j][2];
                    parent[edges[j][1]] = minVertex;
                }
            }

            if(edges[j][1]==minVertex && !visited[edges[j][0]])
            {
                if(edges[j][2] < weights[edges[j][0]])
                {
                    weights[edges[j][0]] = edges[j][2];
                    parent[edges[j][0]] = minVertex;
                }
            }
        }
    }

    cout << endl << endl << "Printing MST:-" << endl;

    for(int i=1; i<n; i++)
    {
        cout << i << " " << parent[i] << " " << weights[i] << endl;
    }

    int minCost = 0;
    for(int i=0; i<n; i++)
    {
        minCost += weights[i];
    }

    cout << "Total cost of MST = " << minCost << endl;
}


int main()
{
    cout << "Enter number of edges: ";
    int e;
    cin >> e;
    cout << "Enter number of vertices: ";
    int n;
    cin >> n;
    cout << "Enter input in following format:-" << endl;
    cout << "First vertex,  " << "Second vertex,  " << "Weight of edge" << endl;

    vector<vector<int> > edges(e);

    for(int i=0; i<e; i++)
    {
        int first_vertex, second_vertex, weight;
        cin >> first_vertex >> second_vertex >> weight;
        edges[i].push_back(first_vertex);
        edges[i].push_back(second_vertex);
        edges[i].push_back(weight);
    }

    MST_using_prim(edges, n);

    return 0;
}

//Prim's algorithm -> Consider any node and select the minimum edge connected to it and do the same for subsequent nodes

//graph example (Total weight of MST = 10)
/*
7 -> edges
5 -> vertices (0 to 4)
0 1 1
1 2 3
0 2 7
0 3 10
2 3 4
0 4 5
3 4 2
*/