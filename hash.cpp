
#include <string>
#include <vector>
#include <string.h>
#include <iostream>
#include "hash.h"

using namespace std;

hashTable::hashTable(int size = 0)
{
    capacity = getPrime(size);
    data.resize(capacity); 
}

// USE FIND POS
bool hashTable::contains(const std::string &key)
{
  // Check if the specified key is in the hash table.
  // If so, return true; otherwise, return false.
  //Checks slot according to hash number then linearly probes until an empty slot is encountered 

  // If I can find its position then it exsist 
  int curpos = findPos(key); 
  if(curpos < 0)
  {
    return false; 
  }
  else
  {
    return true; 
  }

  // int hash_number = hash(key);  
  // std::vector<hashItem>::iterator it;
  // if( (!(data[hash_number].isOccupied))  | (data[hash_number].isDeleted))
  // {
  //   return false; 
  // }

  // for(it = data.begin()+hash_number; it->isOccupied != false; it++)
  // {
  //   if((it->key==key))
  //   {
  //     return true; 
  //   }
  // }

  //add code to loop back and check the begging of the hash table
  return false; 
}

int hashTable::hash(const std::string &key)
{
  int hashVal = 0; 

  for(int i = 0; i < key.length();i++)
  {
    hashVal = 37* hashVal + key[i];
  }
  hashVal %= capacity;  
  if(hashVal < 0)
  {
    hashVal += capacity; 
  }
  return hashVal; 
  //taken from DSAII textbook
}

int hashTable::insert(const std::string &key, void *pv)
{
  // data is of type: hash item

    //if we have more than half of the capacity filled rehash and make sure it was succesful 
  if(filled + 1 >= (capacity/2))
  {
    if(!rehash())
    {
      return 2; 
    }
  }

  int hash_number = hash(key);

  hashItem hash_obj;
  hash_obj.key = key; 
  hash_obj.isOccupied = true;
  hash_obj.pv = pv; 
  int count = 0; 

  if(contains(hash_obj.key))
  {
    return 1; 
  }

  //check if the current slot we want to place our key into is occupied 
  if(!(data[hash_number].isOccupied))
  {
    data[hash_number] = hash_obj; 
    filled++; 
    return 0; 
  }
  else
  {
    for(std::vector<hashItem>::iterator it = data.begin()+hash_number; it != data.end(); it++)
    {
      if(!(it->isOccupied))
      {
        data[hash_number+count] = hash_obj; 
        filled++; 
        return 0; 
      }
      count++; 
    } 
  }
  return 0;
}


//FIX ISSUE WHERE WE HAVE TO LOOP BACK TO BEGGINING OF HASH TABLE
int hashTable::findPos(const std::string &key)
{
  int hash_number = hash(key);
  int count = 0;
  int position = 0;  
  for(std::vector<hashItem>::iterator it = data.begin()+hash_number; it != data.end(); it++)
    {
      if((it->key == key) && (it->isDeleted != true)) //if its the key we are looking for  
      {
        position = hash_number + count; 
        return position; 
      }
      count++; 
    } 

  if(position == 0) //should be zero if no pos 
  {
    for(std::vector<hashItem>::iterator it = data.begin(); it != data.end()-hash_number; it++)
    {
      count = 0; //reset count
      if((it->key == key) && (it->isDeleted != true)) //if its the key we are looking for  
      {
        position = hash_number + count; 
        return position; 
      }
      count++; 
    } 
  }

    return -1; 
}

//account fot not inserting deleted items 
bool hashTable::rehash()
{
  capacity = getPrime(capacity * 2); //should guarantee you get the next prime number 
  std::vector<hashItem> old_data = data;
  //temp contains my old hash table 
  try
  {
    data.resize(capacity);
     // resize the original 
    //loop through the copy of the original vector and reinsert 
    //use hash function to reinsert 
    for(int j=0; j < data.size(); j++)
    {
      data[j].isOccupied = false; //reset the hash table so we can replace stuff 
      data[j].key = ""; 
      data[j].isDeleted = false; 
    }
    //copy everything over
    for(int k=0; k <old_data.size();k++)
    {
      if(old_data[k].isDeleted != true)
      {
      insert(old_data[k].key,old_data[k].pv); 
      }
    }
  }
  catch(std::bad_alloc& ba)
  {
    return false; 
  }
  return true; 
}

unsigned int hashTable::getPrime(int size)
{
    //array of hash numbers that are predefined
    //hash values taken from (https://planetmath.org/goodhashtableprimes)
    unsigned int hash_primes[7] = {49157,98317,196613,393241,786433,1572869,3145739};

    //iterate through the array. If size is less than keep iterating. If size is bigger return prime
    for(int i = 0; i < sizeof(hash_primes); i++ )
    {
        if(size < hash_primes[i])
        {
            return hash_primes[i]; 
        }
    }
    return 0; 
}

int hashTable::getCapacity() {
  return capacity;
}

int hashTable::getfilled() {
  return filled;
}

bool hashTable::remove(const std::string &key)
{
  //idea find the location 
  //set its field to delete
  int pos; 
  if(contains(key))
  {
    pos = findPos(key); 
    data[pos].isDeleted = true; //Lazy Deletion
    return true; 
  }

  return false; 
}

int hashTable::setPointer(const std::string &key, void *pv)
{
  int pos; 
  if(contains(key))
  {
    pos = findPos(key); 

    data[pos].pv = pv; //this will probably be a ptr to a node 

    return 1; 
  }
  return 0; 
}

void * hashTable::getPointer(const std::string &key, bool *b)
{
  int pos; 
  if(contains(key))
  {
  pos = findPos(key);

  // cout << data[pos].pv << endl;
  *b = true; 
  return data[pos].pv;

  }
  else
  {
    return nullptr; 
  }

  //figure out how to set bool ptrs 
}


