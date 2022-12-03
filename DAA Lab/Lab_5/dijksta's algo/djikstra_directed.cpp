#include <iostream>
#include<climits>
using namespace std;

int findMinVertex(int *distance, bool *visited, int v)
{
    int minVertex = -1;
    for(int i=0; i<v; i++)
    {
        //if current vertex is not visited, update the minVertex. If the current vertex is the first vertex, it becomes the minimum vertex
        if(!visited[i] && (minVertex==-1 || distance[i] < distance[minVertex])) 
        {
            minVertex = i;
        }
    }

    return minVertex;
}

void dijkstra(int **edges, int v)
{
    int *distance = new int[v];
    bool *visited = new bool[v];

    for(int i=0; i<v; i++)
    {
        distance[i] = INT_MAX;
        visited[i] = false;
    }

    distance[0] = 0;

    for(int i=0; i<v-1; i++)
    {
        int minVertex = findMinVertex(distance, visited, v);
        visited[minVertex] = true;
        for(int j=0; j<v; j++)
        {
            if(edges[minVertex][j]!=0 && !visited[j]) //if there is an edge between minVertex and current vertex and current vertex is not visited
            {
                int dist = distance[minVertex] + edges[minVertex][j];
                distance[j] = min(dist,distance[j]);

            }
        }
    }

    cout << "vertex" << "  " << "distance from source(0)" << endl;
    for(int i=0; i<v; i++)
    {
        cout << i << "       " << distance[i] << endl;
    }

    delete[] visited;
    delete[] distance;
}

int main()
{
    cout << "Enter number of vertices: ";
    int v;
    cin >> v;
    cout << "Enter number of edges: ";
    int e;
    cin >> e;

    int **edges = new int *[v];
    for (int i = 0; i < v; i++)
    {
        edges[i] = new int[v];
        for (int j = 0; j < v; j++)
        {
            edges[i][j] = 0;
        }
    }

    for (int i = 0; i < e; i++)
    {
        int f, s, weight;
        cout << "First vertex: ";
        cin >> f;
        cout << "Second vertex: ";
        cin >> s;
        cout << "Enter weight: ";
        cin >> weight;
        edges[f][s] = weight;
        edges[s][f] = 0;
        cout << endl;
    }

    dijkstra(edges, v);

    for (int i = 0; i < v; i++)
    {
        delete[] edges[i];
    }

    delete[] edges;
    
    return 0;
}

/*
6
9
0 1 1
1 2 2
2 3 1
0 5 5
5 4 2
4 3 2
1 5 2
1 4 1
2 3 4
*/

/* negative edge graph
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
