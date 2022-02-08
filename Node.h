#ifndef NODE_HXX
#define NODE_HXX

#include <iostream>
#include <vector>

static const bool DEBUG = true;


template <class T>
class Node
{
public:
    Node(const T& val) 
    { 
        m_val = val; 

        if (DEBUG)
            std::cout << " Node: Create node [" << m_val << "]\n";
    }

    //--------------------------------------------------------------------------------------------------
    // Setter/Getter for node value
    //--------------------------------------------------------------------------------------------------
    void SetValue(const T& val) { m_val = val; }
    T GetValue() const { return m_val; }

    //--------------------------------------------------------------------------------------------------
    // Add a child to the list of children
    //--------------------------------------------------------------------------------------------------
    void AddChild(Node* node)
    {
        if (!IsChildPresent(node))
        {
            if (DEBUG)
                std::cout << " Node: Add child [" << m_val << "]  <-- [" << node->GetValue() <<"]\n";

            m_children.emplace_back(node);
        }
    }
    
    //--------------------------------------------------------------------------------------------------
    std::vector<Node*> GetChildren() { return m_children; }

    //--------------------------------------------------------------------------------------------------
    // Checks whether the given node exists in the list of children
    //--------------------------------------------------------------------------------------------------
    bool IsChildPresent(const Node* node)
    {
        return (FindChildWithValue(node->GetValue()) != nullptr);
    }

    //--------------------------------------------------------------------------------------------------
    // Finds a child node with given value. Returns nullptr if not found
    //--------------------------------------------------------------------------------------------------
    Node* FindChildWithValue(const T& val)
    {
        for (const auto& child : m_children)
        {
            if (child->GetValue() == val)
                return child;
        }

        return nullptr;
    }

private:
    std::vector<Node*> m_children;
    T m_val;
};

#endif