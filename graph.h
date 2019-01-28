#pragma once
#include <iostream>
#include<string>
#include<vector>
#include<map>
#include<list>

using namespace std;

/* Structure of an Edge. */
typedef struct Edge_tag
{
    int src;
    int dst;
    int weight;
}Edge_t;

/* Structure of Node data */
typedef struct Node_tag
{
    int nodeId;
    char *nodeName;
    int degree;
}Node_t;

/******************************************************************************************/
class Graph
{
private:
    vector<list<Edge_t*>> m_adjacencyList;
    int m_nodeCount;
    map<int, Node_t*> m_nodeMap;  // Map of node ID and node Data

    /* Private functions */
    Node_t* createNode(char *nodeName);
    int findIdFromNodeName(char *nodeName);
    Node_t* findNodeDataFromNodeId(int nodeId);
    Node_t *Graph::findNodeDataFromNodeName(char *nodeName);

public:
    Graph();
    ~Graph();
    int addVertex(char *nodeName);
    int addEdge(char *src, char *dst, int weight);
    int removeEdge(char *src, char *dst);
    void displayGraph();
    void displayNodeDetails();
    int size();
    int getNumConnections(char *nodeName);
};