#include <string>
#include <vector>
#include <string.h>
#include <iostream>
#include "graph.h"
#include "hash.h"
#include "heap.h"
#include <list> 
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

//can only call the heap when we need it. The hash resizes so were good on that
Graph::Graph(int capacity = 0)
: q(capacity),
  map(capacity)
{
   //constructor needs to set the capacity of the queue and heap 
   this -> capacity = capacity; 
}

void Graph::DisplayGraph() const {
    // Display the header
    std::cout << std::setw(15) << "Node Name" << std::setw(10) << "d" << std::setw(10) << "Known" << std::setw(15) << "p" << std::setw(20) << "Adjacency List" << std::endl;

    // Display each node
    for (const auto& node : node_list) {
        // Display node information
        std::cout << std::setw(15) << node->nodeName << std::setw(10) << node->d << std::setw(10) << std::boolalpha << node->known << std::setw(15) << node->p << std::setw(20);
        
        // Display adjacency list
            for (const auto& edge : node->adjacency_list) {
            std::cout << "(Cost:" << edge->cost << " Dst:" << edge->p_node->nodeName << ") ";
            
        }
        std::cout << std::endl;
    }
}


int Graph::insertNode(const std::string &nodeSource, const std::string &nodeDst, int cost) 
{
    bool b; 
    bool c; 
    Node* src;
    Node* dst;
    Node::Edge* edge; 

    if(!map.contains(nodeSource))
    {
        src = new Node; 
        src->nodeName = nodeSource; 
        node_list.push_back(src); 
        q.insert(nodeSource, src->d, src); 
        map.insert(nodeSource, src); 

    }

    if(!map.contains(nodeDst))
    {
        dst = new Node;
        dst->nodeName = nodeDst;
        node_list.push_back(dst);
        q.insert(nodeDst, dst->d, dst); 
        map.insert(nodeDst, dst); 
    }

    Node *src_pn = static_cast<Node*>(map.getPointer(nodeSource, &b));
    Node *dst_pn = static_cast<Node*>(map.getPointer(nodeDst, &c));
    if(b & c)
    {
        edge = new Node::Edge; 
        edge->cost = cost; 
        edge->p_node = dst_pn; 
        src_pn ->adjacency_list.push_back(edge); 
        
    }
    return 0;
}

// Weighted
void Graph::DijkstraAlgotithm(const std::string &nodeSource)
{
    bool b; 
    int d_v; 
    string node_string;
    Node *p; 
    int known_cnt = 0; 
    //Step 1: For even vertex in the graph I need to set d_v = inf and known = false. This is done already in the construction of the graph

    //Step 2. Set the starting vertex = 0 and p_s = NULL
    Node *s = static_cast<Node*>(map.getPointer(nodeSource, &b));
    s->d = 0; 
    s->p = NULL; 
    q.setKey(s->nodeName,s->d);


    //Step 3. A while loop that has unknown verticies. 
    while(known_cnt<node_list.size())
    {
        q.deleteMin(&node_string,&d_v,&p); 
        Node *v = static_cast<Node*>(p); 
        // cout << "Popped "<<v->nodeName<<"\n"; 
        if(v->known == false)
        {
            v->known = true; 
            known_cnt++; 

            //iterate through everything in the adjacency list
            for(const auto& edge : v->adjacency_list)
            {
                
                if(v->d + edge->cost < edge->p_node->d)
                {
                    edge->p_node->d = v->d + edge->cost; 
                    
                    q.setKey(edge->p_node->nodeName,v->d + edge->cost);
                    edge->p_node->p = v; 
                }
            }
        }

    }
        // cout << "\n---------------------------------\n";
        // DisplayGraph(); 
        // cout << "\n---------------------------------\n"; 
}

void Graph::output()
{
    Node *cnt; 
    string outFile; 
    std::cout << "Enter name of output file: " << endl; 
    std::cin >> outFile; 
    std::ofstream outf(outFile); // Use ofstream directly
    // fstream outf;
    
    // outf.open(outFile ,ios::out);
    std::streambuf* coutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(outf.rdbuf());


    for (const auto& node : node_list) 
    {
        // Display node names and d information
        if(node->d >= 1000000000) { std::cout << node->nodeName << ": " << "NO PATH" << endl;}
        else
        {
            if(node->p == 0)
            {
                std::cout << node->nodeName << ": " << node->d << " [" << node->nodeName << "]" << endl;

            }
            else
            {
                std::cout << node->nodeName << ": " << node->d;
                cnt = node;
                std::list<string> nodeNames;
                while(cnt->p!=0)
                {
                    nodeNames.push_front(cnt->nodeName); 
                    cnt = cnt -> p; 
                }
                if(cnt->p == 0)
                {
                    nodeNames.push_front(cnt->nodeName);  
                }
                std:: cout << " ["; 
                for(const auto& name : nodeNames)
                {
                    if(name != cnt->nodeName) {std::cout << ", " << name; }
                    else {std::cout << name;}
                }
                std::cout << "]" << std::endl;
            }
            
        } 
    }
    std::cout.rdbuf(coutBuffer);
    outf.close();

}

bool Graph::containsNode(const std::string &nodeName)
{
    return map.contains(nodeName); 
}