#include "random.h"
#include "graph.h"
#include <iostream>

#define VERTICES 50000
#define EDGES 10000
#define EDGE_REMOVAL_ATTEMPTS 0
#define NAME_SIZE 2



int main()
{
    Graph g;
    RandomGenerator rng;

    int i = 0;
    char *name = (char *)malloc((NAME_SIZE * sizeof(char)) + 1);
    vector<char *> vertices;

    /* Vertices */
    while (i < VERTICES)
    {
        name = rng.generateRandomString(NAME_SIZE, false, false);
        vertices.push_back(name);
        //printf("ADD NODE: %s\n", name);
        g.addVertex(name);        
        i++;
    }

    /* Edges */
    i = 0;
    while (i < EDGES)
    {
        unsigned int index1 = rng.generateRandomNumber(g.size());
        unsigned int index2 = rng.generateRandomNumber(g.size());

        if (index1 != index2)
        {
            //printf("ADD EDGE: %s %s\n", vertices[index1], vertices[index2]);
            g.addEdge(vertices[index1], vertices[index2], 1);
            i++;
        }
        //i++;
    }


    /* Display graph details */
    g.displayNodeDetails();
    g.displayGraph();

#if 0
    /* Remove edges */
    i = 0;
    while (i < EDGE_REMOVAL_ATTEMPTS)
    {
        unsigned int index1 = rng.generateRandomNumber(g.size());
        unsigned int index2 = rng.generateRandomNumber(g.size());
        //printf("REMOVE EDGE: %s %s\n", vertices[index1], vertices[index2]);
        int retval = g.removeEdge(vertices[index1], vertices[index2]);
        if (retval < 0)
        {
            //printf("\n\n** INFO: removeEdge: Connection %s and %s not found!\n\n", vertices[index1], vertices[index2]);;
        }
        else
        {
            //printf("Removed connection %s and %s\n", vertices[index1], vertices[index2]);
        }

        i++;
    }

    /* Display graph details */
    g.displayNodeDetails();
    g.displayGraph();

    cout << "Connections to " << vertices[2] << ": "<<g.getNumConnections(vertices[2]) << endl;
    cout << "Connections to " << "Sam" << ": " << g.getNumConnections("Sam") << endl;

#endif

    /* Free the vertices local vector */
    while (i < vertices.size())
    {
        free(vertices[i]);
        vertices[i] = nullptr;
        i++;
    }

    getchar();
    return 0;
}