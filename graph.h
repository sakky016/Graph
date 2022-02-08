#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include <fstream>
#include <functional>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>



template <class T>
class Graph
{
public:
    //--------------------------------------------------------------------------------------------------
    Graph(bool isDirectedGrah)
    {
        m_rootNode = nullptr;
        m_isDirectedGraph = isDirectedGrah;
    }


    //--------------------------------------------------------------------------------------------------
    ~Graph()
    {
        // Free memory
        for (const auto& entry : m_nodeMap)
        {
            delete entry.second;
        }
    }

    //--------------------------------------------------------------------------------------------------
    Node<T>* CreateNode(const T& nodeVal)
    {
        Node<T>* node = FindNodeWithValue(nodeVal);
        if (node == nullptr)
        {
            // Create new node
            node = new Node<T>(nodeVal);

            if (m_rootNode == nullptr)
                m_rootNode = node;

            StoreNodeInMap(node);
        }
        else
        {
            if (DEBUG)
                std::cout << "Graph: Node already present [" << node->GetValue() << "]\n";
        }

        return node;
    }

    //--------------------------------------------------------------------------------------------------
    void AddEdge(const T& nodeVal1, const T& nodeVal2)
    {
        if (nodeVal1 == nodeVal2)
        {
            // Invalid operation
            return;
        }

        // Create nodes if required
        Node<T>* node1 = CreateNode(nodeVal1);
        Node<T>* node2 = CreateNode(nodeVal2);

        node1->AddChild(node2);

        if (!m_isDirectedGraph)
        {
            node2->AddChild(node1);
        }
    }


    //--------------------------------------------------------------------------------------------------
    void Seralize(const std::string& outputFile)
    {
        if (DEBUG)
            std::cout << "\nGraph: Writing graph to file " << outputFile << "\n";

        std::ofstream stream(outputFile);
        for (const auto& entry : m_nodeMap)
        {
            stream << entry.first << " ";
            for (const auto& child : entry.second->GetChildren())
            {
                stream << child->GetValue() << " ";
            }
            stream << std::endl;
        }

    }


    //--------------------------------------------------------------------------------------------------
    void Deseralize(const std::string& inputFile)
    {
        if (DEBUG)
            std::cout << "\nGraph: Reading graph from file " << inputFile << "\n";

        std::string line;
        std::ifstream stream(inputFile);
        while (getline(stream, line)) 
        {
            std::vector<std::string> tokens = Split(line, ' ');
            std::string nodeVal = tokens[0];
            //Node<T>* node = CreateNode(nodeVal);

            if (DEBUG)
                std::cout << nodeVal << ": ";


            for (int i = 1; i < tokens.size(); i++)
            {
                std::string childNodeVal = tokens[i];
                //AddEdge(nodeVal, childNodeVal);

                if (DEBUG)
                    std::cout << childNodeVal << " ";
            }
            std::cout << std::endl;
        }
    }


    //--------------------------------------------------------------------------------------------------
    Node<T>* FindNodeWithValue(const T& val)
    {
        auto it = m_nodeMap.find(val);
        if (it != m_nodeMap.end())
        {
            return it->second;
        }

        return nullptr;
    }

    //--------------------------------------------------------------------------------------------------
    void DisplayGraphDepthFirst()
    {
        std::set<T> visited;
        std::cout << "\n\nDepth First Traversal. Entries: " << Size() << std::endl;
        TraverseDepthFirst(m_rootNode, visited);
    }

    //--------------------------------------------------------------------------------------------------
    void DisplayGraphBreadthFirst()
    {
        std::cout << "\n\nBreadth First Traversal. Entries: " << Size() << std::endl;
        TraverseBreadthFirst(m_rootNode);
    }


    //--------------------------------------------------------------------------------------------------
    size_t Size()
    {
        return m_nodeMap.size();
    }


private:
    //--------------------------------------------------------------------------------------------------
    void DisplayNode(Node<T> *node)
    {
        std::cout << node->GetValue() << " ";
    }

    //--------------------------------------------------------------------------------------------------
    void TraverseBreadthFirst(Node<T>* node)
    {
        if (node == nullptr)
            return;


        std::set<T> visited;
        std::queue<Node<T>*> nodeVisitQ;
        nodeVisitQ.push(node);

        while (!nodeVisitQ.empty())
        {
            Node<T>* nodeToDisplay = nodeVisitQ.front();
            nodeVisitQ.pop();

            visited.insert(nodeToDisplay->GetValue());
            DisplayNode(nodeToDisplay);

            for (const auto& child : nodeToDisplay->GetChildren())
            {
                if (visited.find(child->GetValue()) == visited.end())
                {
                    // This node is not yet visited, add it to queue
                    nodeVisitQ.push(child);
                }
            }
        }
    }
        
    //--------------------------------------------------------------------------------------------------
    void TraverseDepthFirst(Node<T>* node, std::set<T> & visited)
    {
        if (node == nullptr)
            return;


        if (visited.find(node->GetValue()) != visited.end())
        {
            // Node already visited
            return;
        }

        visited.insert(node->GetValue());
        DisplayNode(node);

        for (auto& child : node->GetChildren())
        {
            TraverseDepthFirst(child, visited);
        }
    }

    //--------------------------------------------------------------------------------------------------
    void StoreNodeInMap(Node<T>* node)
    {
        m_nodeMap[node->GetValue()] = node;
    }

    //--------------------------------------------------------------------------------------------------
    std::vector<std::string> Split(const std::string& input, const char& delimiter)
    {
        std::vector<std::string> tokens;

        std::stringstream ss(input);
        std::string token;
        while (std::getline(ss, token, delimiter))
        {
            tokens.push_back(token);
        }

        return tokens;
    }


    //--------------------------------------------------------------------------------------------------
    // Private member variables
    //--------------------------------------------------------------------------------------------------
    Node<T>* m_rootNode;
    bool m_isDirectedGraph;
    std::unordered_map<T, Node<T>*> m_nodeMap;
};

#endif