/*buildings.cpp*/

//
// A collection of buildings in the Open Street Map.
// 
// Prof. Joe Hummel
// Northwestern University
// CS 211: Winter 2023
// 

#include <iostream>
#include <string>
#include <vector>
#include <cassert>

#include "buildings.h"
#include "osm.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;


//
// readMapBuildings
//
// Given an XML document, reads through the document and 
// stores all the buildings into the given vector.
//
void Buildings::readMapBuildings(XMLDocument& xmldoc)
{
  XMLElement* osm = xmldoc.FirstChildElement("osm");
  assert(osm != nullptr);

  //
  // Parse the XML document way by way, looking for university buildings:
  //
  XMLElement* way = osm->FirstChildElement("way");

  while (way != nullptr)
  {
    const XMLAttribute* attr = way->FindAttribute("id");
    assert(attr != nullptr);

    //
    // if this is a building, store info into vector:
    //
    if (osmContainsKeyValue(way, "building", "university"))
    {
      string name = osmGetKeyValue(way, "name");

      string streetAddr = osmGetKeyValue(way, "addr:housenumber")
        + " "
        + osmGetKeyValue(way, "addr:street");

      //
      // create building object, then add the associated
      // node ids to the object:
      //
      long long id = attr->Int64Value();

      Building B(id, name, streetAddr);

      XMLElement* nd = way->FirstChildElement("nd");

      while (nd != nullptr)
      {
        const XMLAttribute* ndref = nd->FindAttribute("ref");
        assert(ndref != nullptr);

        long long id = ndref->Int64Value();

        B.add(id);

        // advance to next node ref:
        nd = nd->NextSiblingElement("nd");
      }

      //
      // add the building to the vector:
      //
      this->MapBuildings.push_back(B);
    }//if

    way = way->NextSiblingElement("way");
  }//while

  //
  // done:
  //
}

//
// accessors / getters
//
int Buildings::getNumMapBuildings() {
  return (int) this->MapBuildings.size();
}


//print *
void Buildings::print( )
{
    for (Building B : MapBuildings) {
        cout << B.ID << ": " << B.Name << ", " << B.StreetAddress << endl;
      }

}

// print building's node & footway
void Buildings::findAndPrint(string name, Nodes &nodes ,Footways &footways)
{
      // 
      // find every building that contains this name:
      //
      for (Building B : MapBuildings)
      {
        // B.Name是string, find()是自带的功能
        if (B.Name.find(name) != string::npos) {  // contains name:

            B.print(nodes ,footways); 
        }
      }
}