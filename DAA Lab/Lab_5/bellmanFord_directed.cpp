#include<iostream>
#include<vector>
#include<climits>
using namespace std;

void bellmanFord_Matrix(int v, int e, int **graphMatrix)
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
        cout << "vertex" << "  " << "distance from source(0)" << endl;
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

void bellmanFord_EdgeList(int v, int e, vector<vector<int> > &edgeList)
{
    vector<int> distance(v, INT_MAX);
    distance[0] = 0; //distance from source to source

    for(int i=0; i<v; i++)
    {
        //traverse on edge list
        for(int j=0; j<e; j++)
        {
            int u = edgeList[j][0]; //first vertex
            int v = edgeList[j][1]; //second vertex
            int wt = edgeList[j][2]; //weight or distance

            if(distance[u]!=INT_MAX && (distance[u] + wt < distance[v]))
            {
                distance[v] = distance[u] + wt;
            }
        }
    }

    //Check for negative cycle
    bool flag = false;
    for(int j=0; j<e; j++)
    {
        int u = edgeList[j][0]; //first vertex
        int v = edgeList[j][1]; //second vertex
        int wt = edgeList[j][2]; //weight or distance

        if(distance[u]!=INT_MAX && (distance[u] + wt < distance[v]))
        {
            flag = true;
        }
    }

    if(!flag)
    {
        cout << "vertex" << "  " << "distance from source(0)" << endl;
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

void takeGraphInputAsEdgelist(vector<vector<int> > &edgeList, int e)
{
    for(int i=0; i<e; i++)
    {
        cout << "Enter first vertex: ";
        int fv;
        cin >> fv;
        edgeList[i].push_back(fv);
        cout << "Enter the second vertex: ";
        int sv;
        cin >> sv;
        edgeList[i].push_back(sv);
        cout << "Enter the weight: ";
        int weight;
        cin >> weight;
        edgeList[i].push_back(weight);


        cout << endl;
    }
}

void takeGraphInputAsMatrix(int **graphMatrix, int e)
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

    //Using matrix representation
    int **graphMatrix = new int*[v];
    for (int i = 0; i < v; i++)
    {
        graphMatrix[i] = new int[v];
        for (int j = 0; j < v; j++)
        {
            graphMatrix[i][j] = 0;
        }
    }

    takeGraphInputAsMatrix(graphMatrix,e); //take graph matrix input
    bellmanFord_Matrix(v,e,graphMatrix); //print shortest distance from source to rest of the vertices

    //Using edge list representation
    /* 
    vector<vector<int> > edgeList(e); //vector of e edgeList
    takeGraphInputAsEdgelist(edgeList,e); //take graph edge list input
    bellmanFord_EdgeList(v,e,edgeList); //print shortest distance from source to rest of the vertices
    */

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