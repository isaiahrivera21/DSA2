#ifndef _HEAP_H
#define _HEAP_H


#include "hash.h" 

using namespace std; 
class heap {

public:

  // heap - The constructor allocates space for the nodes of the heap
  // and the mapping (hash table) based on the specified capacity
  //
  heap(int capacity);

  //
  // insert - Inserts a new node into the binary heap
  //
  // Inserts a node with the specified id string, key,
  // and optionally a pointer.  They key is used to
  // determine the final position of the new node.
  //
  // Returns:
  //   0 on success
  //   1 if the heap is already filled to capacity
  //   2 if a node with the given id already exists (but the heap
  //     is not filled to capacity)
  //
  int insert(const std::string &id, int key, void *pv = nullptr);

  //
  // setKey - set the key of the specified node to the specified value
  //
  // I have decided that the class should provide this member function
  // instead of two separate increaseKey and decreaseKey functions.
  //
  // Returns:
  //   0 on success
  //   1 if a node with the given id does not exist
  //
  int setKey(const std::string &id, int key);

  //
  // deleteMin - return the data associated with the smallest key
  //             and delete that node from the binary heap
  //
  // If pId is supplied (i.e., it is not nullptr), write to that address
  // the id of the node being deleted. If pKey is supplied, write to
  // that address the key of the node being deleted. If ppData is
  // supplied, write to that address the associated void pointer.
  //
  // Returns:
  //   0 on success
  //   1 if the heap is empty
  //
  int deleteMin(std::string *pId = nullptr, int *pKey = nullptr, void *ppData = nullptr);

  //
  // remove - delete the node with the specified id from the binary heap
  //
  // If pKey is supplied, write to that address the key of the node
  // being deleted. If ppData is supplied, write to that address the
  // associated void pointer.
  //
  // Returns:
  //   0 on success
  //   1 if a node with the given id does not exist
  //
  int remove(const std::string &id, int *pKey = nullptr, void *ppData = nullptr);

private:
  //
  // current_size - how many elements are currently in the heap
  //
  int current_size = 0;

  //
  // capacity - max amount of items that can be stored on the heap. The user specifies this value. 
  //
  unsigned int capacity;

  //
  // node - a node element that will be present on the heap. 
  //
  // Node is a private nested class containing a string id, 
  // an integer key, and a pointer to void that can
  // point to anything.
  //
  class node{
  public:
    string id {""}; 
    int key; 
    void *vp{nullptr}; 
    node() = default; 
  };

  std::vector<node> data; //data in the heap itself

  //
  // hashTable - hastable class from assignment 1 
  //
  //The program needs to be able to map an id to a node quickly. Since each
  //id can be any arbitrary string, a hash table is useful for this purpose.
  //Searching a heap to find an item with a particular id would require linear
  //time, but a hash table in which each hash entry includes a pointer to the
  //associated node in the heap allows you to find the item in constant average time.
  //
  hashTable mapping; 

  //private member functions 
  void percolateUp(int posCur);
  void percolateDown(int posCur);
  int getPos(node *pn); //first thing after the constructor 

};
#endif //_HEAP_H
