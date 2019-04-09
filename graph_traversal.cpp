#include<iostream>
#include<list>
#include<stdio.h>
#include<string>
#include<vector>

using namespace std;

const int NODE_COUNT = 11;

void displayGraph(const vector<vector<int>> & g)
{
    printf("Nodes: %ld\n", g.size());
    for (size_t i = 0; i < g.size(); i++)
    {
        vector<int> l = g[i];
        cout << i  << ": ";

        for (auto it = l.begin(); it != l.end(); it++)
        {
            cout << *it << " ";
        }

        cout << endl;
    }
}

vector<vector<int>> createGraph(int nodes)
{
    vector<vector<int>> graph;
    vector<int> node;

    for (int i = 0; i < nodes; i++)
    {
        graph.push_back(node);
    }

    return graph;
}

bool addConnection(vector<vector<int>> & graph, const int src, const int dst)
{
    if (src < 0 || src > graph.size() ||
        dst < 0 || dst > graph.size())
    {
        printf("src/dst node not present!\n");
        return false;
    }

    graph[src].push_back(dst);
    graph[dst].push_back(src);
    //printf("Connecting %d and %d\n", src, dst);

    return true;
}

void displayPath(const int dist[], const int pred[], const int src, const int dst)
{
    // vector path stores the shortest path 
    vector<int> path;
    int crawl = dst;
    path.push_back(crawl);
    while (pred[crawl] != -1) 
    {
        path.push_back(pred[crawl]);
        crawl = pred[crawl];
    }

    // distance from source is in distance array 
    cout << "Shortest path length is : "
        << dist[dst];

    // printing path from source to destination 
    cout << "\nPath is::\n";
    for (int i = path.size() - 1; i >= 0; i--)
        cout << path[i] << " ";
}

bool traverse(const vector<vector<int>> & graph, const int src, const int dst)
{
    int dist[NODE_COUNT];
    int pred[NODE_COUNT];

    // a queue to maintain queue of vertices whose 
    // adjacency list is to be scanned as per normal 
    // DFS algorithm 
    list<int> queue;

    // boolean array visited[] which stores the 
    // information whether ith vertex is reached 
    // at least once in the Breadth first search 
    bool visited[NODE_COUNT];

    // initially all vertices are unvisited 
    // so v[i] for all i is false 
    // and as no path is yet constructed 
    // dist[i] for all i set to infinity 
    for (int i = 0; i < NODE_COUNT; i++) 
    {
        visited[i] = false;
        dist[i] = INT_MAX;
        pred[i] = -1;
    }

    // now source is first to be visited and 
    // distance from source to itself should be 0 
    visited[src] = true;
    dist[src] = 0;
    queue.push_back(src);

    // standard BFS algorithm 
    while (!queue.empty()) 
    {
        int u = queue.front();
        queue.pop_front();
        for (int i = 0; i < graph[u].size(); i++)
        {
            if (visited[graph[u][i]] == false)
            {
                visited[graph[u][i]] = true;
                dist[graph[u][i]] = dist[u] + 1;
                pred[graph[u][i]] = u;
                queue.push_back(graph[u][i]);

                // We stop BFS when we find 
                // destination. 
                if (graph[u][i] == dst)
                {
                    displayPath(dist, pred, src, dst);
                    return true;
                }
            }
        }
    }

    return false;
}

// Main
int main()
{
    vector<vector<int>> graph;
    graph = createGraph(NODE_COUNT);

    // Add edges
    addConnection(graph, 0, 1);
    addConnection(graph, 0, 2);


    addConnection(graph, 2, 6);
    addConnection(graph, 2, 7);

    addConnection(graph, 3, 4);
    addConnection(graph, 3, 5);
    addConnection(graph, 3, 6);

    addConnection(graph, 4, 8);

    addConnection(graph, 5, 9);
    addConnection(graph, 5, 10);
    
    addConnection(graph, 7, 8);

    // Display
    cout << "Graph:" << endl;
    displayGraph(graph);


    bool pathExists = traverse(graph, 1, 10);
    if (!pathExists)
        printf("No path exists!\n");


    getchar();
    return 0;
}
