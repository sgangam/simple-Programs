/***
 * Author: Sriharsha Gangam
 * ------------------------
 * */

#include<iostream>
#include<set>
#include<cassert>
#include<cmath>
#include <unordered_map>

int main(int argc, char *argv[]) {
   int dataCenterCount = 0;
   std::cin >> dataCenterCount; // no of data centers
    //  Construct a hash table mapping from an object id to a set of datacenters that contain the object
   std::unordered_map<int, std::set<int>> objectMap; // A hash table containing a set of datacenters.
   for (int id = 1; id <= dataCenterCount ; id++) {
       int objectCount = 0;
       std::cin >> objectCount;
       for (int j = 0; j < objectCount ; j++) {
           int objectId;
           std::cin >> objectId;
           // Is this object present in our hash table?
           std::unordered_map<int, std::set<int>>::iterator it = objectMap.find(objectId);
           if (it == objectMap.end()) { // not found
               std::set<int> dataCenterSet;
               dataCenterSet.insert(id); 
               std::pair<int, std::set<int>> mypair (objectId, dataCenterSet); 
               objectMap.insert(mypair);
           }
           else { // an entry is presnet. Just add the dataCenter Id at the end of this set.
               std::set<int> & dataCenterSet = it->second; // A reference to the set
               dataCenterSet.insert(id); // dataCenterId is always one more than i.
           }
       }
   }

   // Loop over the Object Map. Identify datacenters that do not contain this object.
   for (std::unordered_map<int, std::set<int>>::iterator it = objectMap.begin(); it != objectMap.end(); it++) {
        int objectId = it->first;
        std::set<int> & dataCenterSet = it->second; // A reference to the set
        //dataCenterSet.sort();// sort the set in place.
        int validId = *(dataCenterSet.begin()); // one of the dataCenter Ids which contain the object.
        for (int id = 1 ; id <= dataCenterCount ; id++) {
            if (dataCenterSet.find(id) == dataCenterSet.end()) { //not found
                std::cout << objectId << " " << validId << " " << id << std::endl; // objectId, from, to
            }
        }
   }
   std::cout << "done" << std::endl;

   return 0;
}
