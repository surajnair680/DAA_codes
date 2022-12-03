#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

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

    cout << endl <<  "Printing MST:-" << endl; 

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

    MST_using_kruskal(edges, n);

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