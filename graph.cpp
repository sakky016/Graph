#include"graph.h"

/****************************************************************************************/
/* Constructor */
Graph::Graph()
{
    m_nodeCount = 0;

}

/****************************************************************************************/
/* Destructor */
Graph::~Graph()
{

}

/****************************************************************************************/
/* Create a new vertex node and fill the details */
Node_t* Graph::createNode(char *nodeName)
{
    Node_t *newnode = (Node_t *)malloc(sizeof(Node_t));
    if (newnode == nullptr)
    {
        return newnode;
    }

    newnode->degree = 0;
    newnode->nodeId = m_nodeCount;
    int len = strlen(nodeName);
    len++;
    newnode->nodeName = (char *)malloc(len * sizeof(char));
    if (newnode->nodeName == nullptr)
    {
        printf("\n\n** ERROR: createNode: Malloc failure for nodeName\n\n");
        abort();
    }

    strncpy_s(newnode->nodeName, len, nodeName, len);
    return newnode;
}

/****************************************************************************************/
int Graph::addVertex(char *nodeName)
{
    /* Check if this vertex is already present */
    if (findIdFromNodeName(nodeName) >= 0)
    {
        //printf("\n\n** INFO: Vertex %s already present\n", nodeName);
        return -1;
    }

    /* Create a new Vertex node */
    Node_t *vertexNode = createNode(nodeName);
    if (vertexNode == nullptr)
    {
        printf("\n\n** ERROR: addVertex: Unable to create vertex node\n\n");
        abort();
    }

    list<Edge_t*> dummyList;
    dummyList.push_back(nullptr);           // Create an empty list
    m_adjacencyList.push_back(dummyList);   // Create adjacency list graph

    m_nodeCount++;
    m_nodeMap[vertexNode->nodeId] = vertexNode;
    
    return 0;
}

/****************************************************************************************/
int Graph::addEdge(char *src, char *dst, int weight)
{
    // Find nodeId from nodeName
    int srcId = findIdFromNodeName(src);
    int dstId = findIdFromNodeName(dst);

    /* Check if this edge already present */
    list<Edge_t*>::iterator it = m_adjacencyList[srcId].begin();
    Edge_t *edge = *it;
    if (edge == nullptr)
    {
        //printf("Dummy edge!\n");
        it++;
    }

    while (it != m_adjacencyList[srcId].end())
    {
        Edge_t *edge = *it;

        if (edge->dst == dstId)
        {
            //printf("\n\n** INFO: Edge %s and %s already present\n", src, dst);
            return -1;
        }

        it++;
    }// End of while 


    /* Create a new edge */
    edge = (Edge_t *)malloc(sizeof(Edge_t));
    if (edge == nullptr)
    {
        printf("\n\n** ERROR: addEdge: Malloc failure\n\n");
        abort();
    }

    *edge = { srcId, dstId, weight };

    if (srcId >= 0 && dstId >= 0 && srcId != dstId)
    {
        m_adjacencyList[srcId].push_back(edge);

        // Update the degree of this src node
        Node_t *srcNode = findNodeDataFromNodeId(srcId);
        srcNode->degree++;

        return 0;
    }
    else
    {
        //printf("\n**INFO: Cannot create edge for %s and %s\n", src, dst);
        if (srcId < 0)
        {
            //printf("  INFO: %s vertex not present\n\n", src);
        }

        if (dstId < 0)
        {
            //printf("  INFO: %s vertex not present\n\n", dst);
        }
        return -1;
    }

    
}

/****************************************************************************************/
int Graph::removeEdge(char *src, char *dst)
{
    /* Check if a connection exists between these 2 nodes */
    int srcId = findIdFromNodeName(src);
    int dstId = findIdFromNodeName(dst);

    if (srcId < 0 || dstId < 0)
    {
        //printf("\n\n** INFO: removeEdge: No connection exists between %s and %s\n\n", src, dst);
        return -1;
    }

    if (srcId == dstId)
    {
        //printf("\n\n** INFO: removeEdge: Invalid edge removal!\n");
        return -1;
    }
    
    list<Edge_t*>::iterator it = m_adjacencyList[srcId].begin();
    Edge_t *edge = *it;
    if (edge == nullptr)
    {
        //printf("Dummy edge!\n");
        it++;
    }

    while (it != m_adjacencyList[srcId].end())
    {
        Edge_t *edge = *it;
        Node_t *sNode = findNodeDataFromNodeId(edge->src);
        Node_t *dNode = findNodeDataFromNodeId(edge->dst);
        
        //printf("Checking %s and %s...\n", sNode->nodeName, dNode->nodeName);
        if (edge->dst == dstId)
        {
            //printf("  Found!\n");
            it = m_adjacencyList[srcId].erase(it);
            //printf("  Removed\n");
            sNode->degree--;
            return 0;
        }

        it++;
    }// End of while 

    return -1;
}

/****************************************************************************************/
/* Display vertices and edges of the graph */
void Graph::displayGraph()
{
    if (size() <= 0)
    {
        printf("\nGraph empty!\n\n");
        return;
    }

    int i = 0;
    int j = 0;
    list<Edge_t*>::iterator it;  // Iterator for the edges.
    printf("\n\nGraph Adjacency List:\n");
    printf("------------------------\n");

    for (i = 0; i < size(); i++) // Vertices 
    {
        list<Edge_t*> list = m_adjacencyList[i];  // List of nodes connected to this vertex
        it = list.begin();
        Node_t *vertex = findNodeDataFromNodeId(i);            // This vertex
        int numEdges = m_adjacencyList[i].size();              // Number of nodes connected to this vertex
        printf("%s[%3d] --> ", vertex->nodeName, vertex->nodeId);

        while (it != list.end())
        {
            Edge_t* edge = *it;
            
            if (edge)
            {
                Node_t *node = findNodeDataFromNodeId(edge->dst);
                printf("%s[%d]   ", node->nodeName, node->nodeId);
            }
            else
            {
                //printf(" X\n");
            }
            it++;
        } // End of while
        printf("\n");
    }

}

/****************************************************************************************/
void Graph::displayNodeDetails()
{
    int i = 0;

    printf("\n\nNode details:\n");
    printf("----------------------------------------------------\n");
    printf("Node ID   Node Name             Degree\n");
    printf("----------------------------------------------------\n");
    for (i = 0; i < size(); i++)
    {
        Node_t *node = findNodeDataFromNodeId(i);
        printf("%3d       %-20s %3d\n", node->nodeId, node->nodeName, node->degree);
    }
    printf("\n\n");
}

/****************************************************************************************/
/* Finds nodeId corresponding to nodeName. Returns -1 if not found. */
int Graph::findIdFromNodeName(char *nodeName)
{
    map<int, Node_t*>::iterator it = m_nodeMap.begin();

    while (it != m_nodeMap.end())
    {
        if (strcmp(it->second->nodeName, nodeName) == 0)
        {
            return it->first;
        }

        it++;
    }

    //printf("\n\n** INFO: findIdFromNodeName: No node found with name %s\n ", nodeName);
    return -1;
}

/****************************************************************************************/
Node_t* Graph::findNodeDataFromNodeId(int nodeId)
{
    if (nodeId < 0 || nodeId > size())
    {
        return nullptr;
    }
    else
    {
        return m_nodeMap[nodeId];
    }
}

/****************************************************************************************/
Node_t *Graph::findNodeDataFromNodeName(char *nodeName)
{
    return findNodeDataFromNodeId(findIdFromNodeName(nodeName));
}

/****************************************************************************************/
int Graph::size()
{
    return m_nodeCount;
}

/****************************************************************************************/
/* Returns the number of connections to this node or -1 if node not found. */
int Graph::getNumConnections(char *nodeName)
{
    Node_t *node = findNodeDataFromNodeName(nodeName);
    if (node)
    {
        return node->degree;
    }
    else
    {
        printf("\n\n** INFO: Node %s not found ", nodeName);
        return -1;
    }
}