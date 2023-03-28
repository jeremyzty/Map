/*buildings.h*/

//
// A collection of buildings in the Open Street Map.
// 
// Prof. Joe Hummel
// Northwestern University
// CS 211: Winter 2023
// 

#pragma once

#include <vector>

#include "footway.h"
#include "nodes.h"
#include "tinyxml2.h" 

using namespace std;
using namespace tinyxml2;

 
//
// Keeps track of all the Footways in the map.
//
class Footways
{
public:
  vector<Footway> MapFootways;

  //
  // readMapBuildings
  //
  // Given an XML document, reads through the document and 
  // stores all the buildings into the given vector.
  //
  void readMapFootways(XMLDocument& xmldoc);

  //
  // accessors / getters
  //
  int getNumMapFootways();


  //print 
  void print( );


  // find and print
  void findIntersect(  vector<long long> &NodeIDs  , vector<Footway> &vec);

};


