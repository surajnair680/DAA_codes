#include<iostream>
#include<vector>
#include<climits>
using namespace std;

void bellmanFord(int v, int e, int **graphMatrix)
{
    int distance[v];
    
    for(int i=0; i<v; i++)
    {
        distance[i] = INT_MAX;
    }
    
    distance[0] = 0;

    //Minimize n-1 times
    for(int k=0; k<v; k++)
    {
        //traverse on edgeList
        for(int i=0; i<v; i++)
        {
            for(int j=0; j<v; j++)
            {
                if(graphMatrix[i][j]!=0) //If edge exists
                {
                    int u = i;
                    int v = j;
                    int wt = graphMatrix[i][j];
                    if(distance[u]!=INT_MAX && (distance[u] + wt < distance[v]))
                    {
                        distance[v] = distance[u] + wt;
                    }

                }
            }

        }

    }
   
    bool flag = false;
    for(int k=0; k<v; k++)
    {
        for(int i=0; i<v; i++)
        {
            
            for(int j=0; j<v; j++)
            {
                if(graphMatrix[i][j]!=0) //If edge exists
                {
                    int u = i;
                    int v = j;
                    int wt = graphMatrix[i][j];
                    if(distance[u]!=INT_MAX && (distance[u] + wt < distance[v]))
                    {
                        flag = true;
                    }

                }
            }

        }
    }

    if(!flag)
    {
        cout << "vertex" << "  " << "shortest distance from source(0)" << endl;
        for(int i=0; i<v; i++)
        {
            cout << i << "       " << distance[i] << endl;
        }
    }
    else
    {
         cout << "Negative cycle detected. Therefore shortest distance cannot be found." << endl;
    }
}

void takeGraphInput(int **graphMatrix, int e)
{
    for (int i = 0; i < e; i++)
    {
        int f, s, weight;
        cout << "First vertex: ";
        cin >> f;
        cout << "Second vertex: ";
        cin >> s;
        cout << "Enter weight: ";
        cin >> weight;
        graphMatrix[f][s] = weight;
        graphMatrix[s][f] = 0;
        cout << endl;
    }
}

int main()
{

    cout << "Enter number of vertices: ";
    int v;
    cin >> v;
    cout << "Enter number of edges: ";
    int e;
    cin >> e;

    int **graphMatrix = new int*[v];
    for (int i = 0; i < v; i++)
    {
        graphMatrix[i] = new int[v];
        for (int j = 0; j < v; j++)
        {
            graphMatrix[i][j] = 0;
        }
    }

    takeGraphInput(graphMatrix,e); //take graph matrix input
    bellmanFord(v,e,graphMatrix); //print shortest distance from source to rest of the vertices
    
    return 0;
}












/*
Condition for Bellman ford algorithm:-
1. Can contain negative edgeList.
2. Should not contain negative cycle.

Steps:-
1. Perform distance minimization n-1 times.
2. Perform distance minimization one more time
   If distance gets updated, negative cycle exists and shortest path cannot be found.
*/

/*
6
9
0 1 6
0 2 4
0 3 5
1 4 -1
2 1 -2
2 4 3 
3 2 -2
3 5 -1
4 5 3
*/

/* Negative cycle example
4
5
0 1 4
0 2 5
2 1 7
1 3 7
3 2 -15
*/