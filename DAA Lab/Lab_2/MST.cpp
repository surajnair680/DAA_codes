#include<iostream>
#include<chrono>
#include<vector>
#include<algorithm>
#include<climits>

using namespace std;


//---------------Kruskal's algorithm------------------

//Comparator to sort the edges
bool cmp(vector<int> &a, vector<int> &b)
{
    return a[2] < b[2];
}

//To initialize parent array and rank array
void makeSet(vector<int> &parent, vector<int> &rank, int n)
{
    for(int i=0; i<n; i++)
    {
        parent[i] = i; //Initially every node is parent of itself
        rank[i] = 0; //Initially rank of every node is 0
    }
}

//To find parent of a node
int findParent(vector<int> &parent, int node)
{
    if(parent[node]==node) return node;

    parent[node] = findParent(parent, parent[node]); //Ask for parent of a node 'x' -> Node 'x' asks for parent of its parent node and so on (recursion)

    return parent[node]; //update parent of node so that information is stored for future use (path compression)
}

//To perform union operation by updating parent and rank array
void unionSet(int u, int v, vector<int> &parent, vector<int> &rank)
{
    u = findParent(parent, u);
    v = findParent(parent, v);

    if(rank[u] < rank[v])
    {
        parent[u] = v;
    }
    else if(rank[v] < rank[u])
    {
        parent[v] = u;
    }
    else
    {
        parent[v] = u;
        rank[u]++;
    }
}

//Print MST and total weight of MST
void MST_using_kruskal(vector<vector<int> > &edges, int n)
{
    sort(edges.begin(), edges.end(), cmp);

    vector<int> parent(n);
    vector<int> rank(n);
    makeSet(parent, rank, n); //initialize parent array and rank array

    int minWeight = 0;

    cout << endl <<  "Printing MST using Kruskal's algorithm:-" << endl; 

    for(int i=0; i<edges.size(); i++) //Iterating through all edges
    {
        int u = findParent(parent, edges[i][0]); //parent of first node of current edge
        int v = findParent(parent, edges[i][1]); //parent of second node of current edge

        
        if(u!=v) //if both nodes of current edge do not have same parents
        {
            minWeight += edges[i][2]; //Add weight of current edge to minWeight
            unionSet(u, v, parent, rank);

            //Print the edge only if union operation is performed
            cout << edges[i][0] << " " << edges[i][1] << " " << edges[i][2] << endl;
        }

    }

    cout << endl << "Total Weight of MST = " << minWeight << endl;

}






//---------------Prims's algorithm----------------------

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

    cout << endl << endl << "Printing MST using Prim's:-" << endl;

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

//--------------Function to generate complete graph-----------

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

    int v2=15;
    int e2=v2*(v2-1)/2;
    vector<vector<int> > edges2(e2);
    generateGraph(edges2, v2);

    int v3=20;
    int e3=v3*(v3-1)/2;
    vector<vector<int> > edges3(e3);
    generateGraph(edges3, v3);

    cout << "------------------------------------------------------------" << endl;
    cout << endl << "Printing graph with 8 vertices " << endl;
    for(int i=0; i<e1; i++)
    {
        cout << edges1[i][0] << " " << edges1[i][1] << " " << edges1[i][2] << endl;
    }

    cout << endl;
    auto begin = chrono::high_resolution_clock::now();
    MST_using_prim(edges1, v1);
    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    cout << endl;
    cout << "Time taken to compute MST using Prim's algorithm: ";
    printf("%.10f", elapsed.count() * 1e-3);
    cout << "ms" << endl;

    cout << endl;
    begin = chrono::high_resolution_clock::now();
    MST_using_kruskal(edges1, v1);
    end = chrono::high_resolution_clock::now();
    elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    cout << endl;
    cout << "Time taken to compute MST using Kruskal's algorithm: ";
    printf("%.10f", elapsed.count() * 1e-3);
    cout << "ms" << endl;

    cout << "------------------------------------------------------------" << endl;
    cout << endl << "Printing graph with 15 vertices " << endl;
    for(int i=0; i<e2; i++)
    {
        cout << edges2[i][0] << " " << edges2[i][1] << " " << edges2[i][2] << endl;
    }

    cout << endl;
    begin = chrono::high_resolution_clock::now();
    MST_using_prim(edges2, v2);
    end = chrono::high_resolution_clock::now();
    elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    cout << endl;
    cout << "Time taken to compute MST using Prim's algorithm: ";
    printf("%.10f", elapsed.count() * 1e-3);
    cout << "ms" << endl;

    cout << endl;
    begin = chrono::high_resolution_clock::now();
    MST_using_kruskal(edges2, v2);
    end = chrono::high_resolution_clock::now();
    elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    cout << endl;
    cout << "Time taken to compute MST using Kruskal's algorithm: ";
    printf("%.10f", elapsed.count() * 1e-3);
    cout << "ms" << endl;

    cout << "------------------------------------------------------------" << endl;
    cout << endl << "Printing graph with 20 vertices " << endl;
    for(int i=0; i<e3; i++)
    {
        cout << edges3[i][0] << " " << edges3[i][1] << " " << edges3[i][2] << endl;
    }

    cout << endl;
    begin = chrono::high_resolution_clock::now();
    MST_using_prim(edges3, v3);
    end = chrono::high_resolution_clock::now();
    elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    cout << endl;
    cout << "Time taken to compute MST using Prim's algorithm: ";
    printf("%.10f", elapsed.count() * 1e-3);
    cout << "ms" << endl;

    cout << endl;
    begin = chrono::high_resolution_clock::now();
    MST_using_kruskal(edges3, v3);
    end = chrono::high_resolution_clock::now();
    elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    cout << endl;
    cout << "Time taken to compute MST using Kruskal's algorithm: ";
    printf("%.10f", elapsed.count() * 1e-3);
    cout << "ms" << endl;

    return 0;
}

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








// cout << "Enter number of edges: ";
    // int e;
    // cin >> e;
    // cout << "Enter number of vertices: ";
    // int n;
    // cin >> n;
    // cout << "Enter input in following format:-" << endl;
    // cout << "First vertex,  " << "Second vertex,  " << "Weight of edge" << endl;

    // vector<vector<int> > edges(e);

    // for(int i=0; i<e; i++)
    // {
    //     int first_vertex, second_vertex, weight;
    //     cin >> first_vertex >> second_vertex >> weight;
    //     edges[i].push_back(first_vertex);
    //     edges[i].push_back(second_vertex);
    //     edges[i].push_back(weight);
    // }