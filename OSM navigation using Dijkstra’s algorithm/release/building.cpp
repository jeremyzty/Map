/*building.cpp*/

//
// A building in the Open Street Map.
// 
// Prof. Joe Hummel
// Northwestern University
// CS 211: Winter 2023
// 

#include <iostream>

#include "building.h"

using namespace std;


//
// constructor
//
Building::Building(long long id, string name, string streetAddr)
  : ID(id), Name(name), StreetAddress(streetAddr)
{
  //
  // the proper technique is to use member initialization list above,
  // in the same order as the data members are declared:
  //
  //this->ID = id;
  //this->Name = name;
  //this->StreetAddress = streetAddr;

  // vector is default initialized by its constructor
}

//
// containsThisNode
//
// Returns true if the building's nodes contains the given node id,
// false if not.
//
bool Building::containsThisNode(long long nodeid)
{
  for (long long id : this->NodeIDs)
  {
    if (nodeid == id)
      return true;
  }

  // 
  // if get here, not found:
  //
  return false;
}

//
// print
// 
// prints information about a building --- id, name, etc. -- to
// the console. The function is passed the Nodes for searching 
// purposes.
//
void Building::print(Nodes& nodes)
{
  cout << this->Name << endl;
  cout << "Address: " << this->StreetAddress << endl;
  cout << "Building ID: " << this->ID << endl;

  // 怎么赋值pair很重！
  pair<double ,double >  location= getLocation(nodes);

  cout << "Approximate location: ("<< location.first <<", "<<  location.second  <<")"<<endl;
  cout << "Nodes:" << endl;
  for (long long nodeid : this->NodeIDs)
  {
    cout << "  " << nodeid << ": ";

    double lat = 0.0;
    double lon = 0.0;
    bool entrance = false;

    bool found = nodes.find(nodeid, lat, lon, entrance);

    if (found) {
      cout << "(" << lat << ", " << lon << ")";

      if (entrance)
        cout << ", is entrance";

      cout << endl;
    }
    else {
      cout << "**NOT FOUND**" << endl;
    }
  }//for
}

//
// adds the given nodeid to the end of the vector.
//
void Building::add(long long nodeid)
{
  this->NodeIDs.push_back(nodeid);
}


pair<double, double> Building::getLocation( Nodes& nodes)
{
     
    double sumLat =0;
    double sumLon =0;    

    // 虽然building里存了NodeIDs vector，但是没有longitude和altitude
    // 需要在nodes的vector里找，用find()
    //
    for( auto id :NodeIDs)
    {
          double lat = 0.0;
          double lon = 0.0;
          bool entrance = false;

          bool found = nodes.find(id, lat, lon, entrance);

          sumLat+= lat;
          sumLon+= lon;
    }

    sumLat/= NodeIDs.size();
    sumLon/= NodeIDs.size();    
    return make_pair(sumLat ,sumLon); // make_pair(A, B)是built-in function
}


 