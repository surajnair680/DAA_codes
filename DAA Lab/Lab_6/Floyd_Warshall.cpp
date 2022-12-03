#include<iostream>
using namespace std;
const int INF = 1e9;

void Floyd_Warshall(int **graph, int v)
{
    for(int k=1; k<=v; k++)
    {
        for(int i=1; i<=v; i++)
        {
            for(int j=1; j<=v; j++)
            {
                if(graph[i][k]+graph[k][j]<graph[i][j])
                {
                    graph[i][j] = graph[i][k] + graph[k][j];
                }
                 
            }
        }
    }

    //Printing the result

    cout << endl << "Printing the result matrix..." << endl << endl;
    cout << "  | ";
    for(int i=1; i<=v; i++) cout << i << "  ";
    cout << endl;
    for(int i=1; i<=v; i++) cout << "----";
    cout << endl;

    for(int i=1; i<=v; i++)
    {
        cout << i << " | ";

        for(int j=1; j<=v; j++)
        {
            cout << graph[i][j] << "  ";
        }

        cout << endl;
    }

    cout << endl;

    cout << "vertex 1" << "     " << "vertex 2" <<  "  " << "   shortest path between vertex 1 and vertex 2" << endl;
    for(int i=1; i<=v; i++)
    {
        for(int j=1; j<=v; j++)
        {
            cout << i << "             " << j << "             " <<  graph[i][j] << endl;
        }
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

    int **graph = new int *[v+1];
    for (int i = 0; i <= v; i++)
    {
        graph[i] = new int[v+1];
        for (int j = 0; j <= v; j++)
        {
            graph[i][j] = INF;
        }
    }

    cout << "Enter graph data in the following format" << endl;
    cout << "First vertex" << ", " << "Second vertex" << ", " << "weight of edge" << endl << endl;

    for (int i = 1; i <= e; i++)
    {
        int f, s, weight;
        cin >> f;
        cin >> s;
        cin >> weight;
        graph[f][s] = weight;
    
    }

    for(int i=0; i<=v; i++) //diagonal elements are zero
    {
        graph[i][i] = 0;
    }


    Floyd_Warshall(graph, v);

    for (int i = 0; i <= v; i++)
    {
        delete[] graph[i];
    }

    delete[] graph;
    
    return 0;
}

//example graph 1
/*
1 4 7
4 1 2
3 1 5
2 3 2
2 1 8
1 2 3
3 4 1
*/

//example graph 2
/*
1 3 3
2 1 2 
3 2 7
3 4 1
4 1 6
*/