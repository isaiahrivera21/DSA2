#include <string>
#include <vector>
#include <string.h>
#include <iostream>
#include "hash.h"
#include "heap.h"

using namespace std;


//build a constructor 
heap::heap(int capacity):mapping(capacity*2)
  {
    // Allocate space for the nodes (0 slot is not used)
    data.resize(capacity+1);
    this ->capacity = capacity; 
  }

int heap::getPos(node *pn)
{
  int pos = (pn - &data[0]);

  return pos;    
}

void heap::percolateDown(int posCur)
{
  int child; 
  node tmp = data[posCur];

  for(; posCur*2 <= current_size; posCur = child)
  {
    child = posCur * 2; 

    if(child < current_size && data[child + 1].key < data[child].key)
    {
      child++; 
    }

    if(data[child].key < tmp.key)
    {

      data[posCur] = data[child]; 
      mapping.setPointer(data[posCur].id,&data[posCur]);
    }

    else
    {
      break; 
    }
  }
  data[posCur] = tmp; 
  mapping.setPointer(data[posCur].id,&data[posCur]);
  //set pointer
}

void heap::percolateUp(int posCur)
{
  int parent; 
  node tmp = data[posCur]; 

  for(; posCur / 2 > 0; posCur = parent)
  {
    parent = posCur / 2; 

    if(tmp.key < data[parent].key)
    {
      data[posCur] = data[parent]; 
      mapping.setPointer(data[posCur].id,&data[posCur]);
    }
    else
    {
      break; 
    }
  }

  //more stuff
  data[posCur] = tmp; 
  mapping.setPointer(data[posCur].id,&data[posCur]);


}

int heap::insert(const std::string &id, int key, void *pv)
{
  int hole = ++current_size;

  if(hole > capacity)
  {
    return 1; 
  }
  
  if(mapping.contains(id)) // if the id is already in the priority queue
  {
  return 2;
  }

  node newNode; 
  newNode.key = key;
  newNode.id = id; 
  newNode.vp = pv; // should be adress of whare the node should be

  data[hole] = newNode; //should be located in hole
  mapping.insert(newNode.id, &data[hole]);
  // pass the whole by reference

  percolateUp(hole);


  return 0; 
}

int heap::deleteMin(std::string *pId, int *pKey, void *ppData)
{

  //check if it is empty
  if(!(current_size))
  {
    return 1;
  }

  if(ppData != nullptr)
  {
    *(static_cast<void **>(ppData)) = data[1].vp; //cast ppData to a pointer to a void pointer. derefernce it. Assign the void pointer to data.vp
  }
  

  if(pKey != nullptr)
  {
    *(pKey) = data[1].key;
  }

  if(pId != nullptr)
  {
    *(pId) = data[1].id;
  }

  //um need to set whatever is here to lazily delted in the hash table 
  mapping.remove(*(pId));

  data[1] = data[current_size--]; //assign the last element of the array to the heap

  percolateDown(1); //put it in the proper position
  
  return 0; 

}

int heap::setKey(const std::string &id, int key)
{
  //lets use the hash table to search for a node 
  bool b;  
  int prev_key;
  int node_pos;

  if(mapping.contains(id))//this is to see if the string exsist
  {
    //acess the space in the hash table where the id is. use the node pointer to set the new key.

    node *pn = static_cast<node *>(mapping.getPointer(id,&b)); //mapping vp 
    node_pos = getPos(pn); //probably not working 
    prev_key = pn->key; //save the previous key
    pn->key = key; 

    //need to percolate up or down but how do I know which one. If new key is less than perc up. If its greayer then perk down

  if (key < prev_key) 
  {
    percolateUp(node_pos);
  } 
  else 
  {
    percolateDown(node_pos);
  }
  }
  else
  {
    return 1;
  }
  return 0; 
}

int heap::remove(const std::string &id, int *pKey, void *ppData)
{
  bool b; 
  //check if the node exsist
  if(mapping.contains(id)) //ISSUE
  {
  //preform a remove by setting the key to be very small. Then deleting_min

  node *pn = static_cast<node *>(mapping.getPointer(id,&b));
  int posCur = (pn - &data[0]);

  if (ppData != nullptr)
  {
    *(static_cast<void **>(ppData)) = pn->vp; 
  }
  //cast ppData to a pointer to a void pointer. derefernce it. Assign the void pointer to data.vp

  if (pKey != nullptr)
  {
    *(pKey) = pn->key;
  }


  data[posCur] = data[current_size--]; //assign the last element of the array to the heap

  //decide whether to percolate up or down

  if((posCur > 1) && (data[posCur].key < data[posCur/2].key))
  {
    percolateUp(posCur);
  }
  else
  {
    
    percolateDown(posCur);
  }
  return 0;
  }

  else
  {
    return 1;
  } 
}