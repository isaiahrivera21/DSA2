//page 355 in book 
#include "hash.h"
#include "heap.h"
#include <list>

using namespace std; 

//time to think :skull: 

// I want to represent the following graph 
/*
v1 v2 2
v1 v4 1
v2 v4 3
v2 v5 10
v3 v1 4
v3 v6 5
v4 v3 2
v4 v5 2
v4 v6 8
v4 v7 4
v5 v7 6
v7 v6 1
*/

class Graph
{


public:


    // any supporting functions to construct the grpah 

    Graph(int capacity);

    void DisplayGraph() const;

    /*
    To locate a node corresponding to a source vertex that has been seen before, use the getPointer member function of the hash table.
    */

    /*
    Whenever a new vertex is encountered, add an entry with the new vertex id to the hash table
    use the void pointer in the hash table to point to the new graph node
    Insert a node into the linked list. In the other two data structure set everything up accordingly 
    */
    //function 1: insert node
    int insertNode(const std::string &nodeSource,const std::string &nodeDst,int cost); 

    
    // function 4: Dikstra Algo (no idea what you should return. maybe a string containing the correct sequence. Maybe nothing)
    void DijkstraAlgotithm(const std::string &nodeSource); 

    // I need a function for displaying stuff
    void output(); 

    bool containsNode(const std::string &nodeName); 


    


    

private:

    // current_size - how many elements are currently in the heap
    int current_size = 0;

    // capacity - max amount of items that can be stored on the heap. The user specifies this value. 
    unsigned int capacity;

    //the heap
    heap q; 

    //the hashtable 
    hashTable map; 


    // function 3: get node (could be private)
    // void *getNode(const std::string &key, bool *b = nullptr); //may not even be necessary 

    //private nested class containing the nodes 
    class Node{
    public:
        std::string nodeName{""};
        bool known{false};  //for Dikstra
        unsigned int d{1000000000}; 
        Node* p{NULL}; 

        struct Edge
        {
           unsigned int cost; 
           Node *p_node; 
        };
        
        std::list <struct Edge*> adjacency_list;
        Node() = default; 
    };

    std::list<Node*> node_list; 
};