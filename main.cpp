#include <iostream>
#include "Graph.h"
#include <string>

using namespace std;

int main()
{
    Graph<int> graph(false);

    graph.AddEdge(10, 20);
    graph.AddEdge(10, 30);
    graph.AddEdge(10, 70);
    graph.AddEdge(10, 80);
    graph.AddEdge(10, 90);
    graph.AddEdge(10, 100);
    graph.AddEdge(10, 110);
    graph.AddEdge(20, 50);
    graph.AddEdge(30, 60);
    graph.AddEdge(30, 60);
    graph.AddEdge(40, 60);
    graph.AddEdge(50, 51);
    graph.AddEdge(52, 51);
    graph.AddEdge(60, 61);
    graph.AddEdge(60, 62);

    graph.DisplayGraphDepthFirst();
    graph.DisplayGraphBreadthFirst();
    graph.Seralize(string("out.txt"));
    
    //Graph<int> graph2(false);
    //graph2.Deseralize(string("out.txt"));
    //graph2.DisplayGraphNodes();

    return 0;
}