/*main.cpp*/

//
// HEADER COMMENT
//

#include <iostream>
#include <string>

#include "building.h"
#include "footway.h"
#include "node.h"
#include "nodes.h"
#include "osm.h"
#include "tinyxml2.h"
#include "buildings.h"

using namespace std;
using namespace tinyxml2;


int main()
{
  XMLDocument xmldoc;
  Nodes nodes;
  Buildings buildings;
  
  cout << "** NU open street map **" << endl;

  string filename;

  cout << endl;
  cout << "Enter map filename> " << endl;
  getline(cin, filename);

  //
  // 1. load XML-based map file 
  //
  if (!osmLoadMapFile(filename, xmldoc))
  {
    // failed, error message already output
    return 0;
  }
  
  //
  // 2. read the nodes, which are positions on the map:
  //
  nodes.readMapNodes(xmldoc); 
  // sort  nodes
  nodes.sortByID();
   
  //
  // 3. read the buildings contained in the map:
  //
  //
  buildings.readMapBuildings(xmldoc);

  //
  // 4. read the footways / paths on the map:
  //
  //
  // TODO!
  //


  //
  // 5. stats
  //
  cout << "# of nodes: " << nodes.getNumMapNodes() << endl;

  //
  // TODO: output other stats for buildings and footways:
  //
  cout << "# of buildings: " << buildings.getNumMapBuildings() << endl;
  //
  // now let the user for search for 1 or more buildings:
  //
  while (true)
  {
    string name;

    cout << endl;
    cout << "Enter building name (partial or complete), or * to list, or $ to end> " << endl;

    getline(cin, name);  // use getline() because user may type multiple words:

    if (name == "$") {
      break;
    }
    else if (name == "*")
    {
      //
      // TODO: list all the buildings in the order they appear in the
      // vector (which is the order they appear in the map file):
      //
		for ( int  i = 0; i < buildings.getNumMapBuildings(); i++)
		{
			Building &b = buildings.MapBuildings[i];
			cout << b.ID <<": "<< b.Name << ", "<< b.StreetAddress << endl;
		}


    }
    else {
      // 
      // find every building that CONTAINS name string, output in the 
      // order they appear in the vector (which is the order they appear
      // in the map file):
      //

      // 
      // TODO: use string's find() function to see if building name
      // contains the name string input by the user. NOTE that find()
      // returns string::npos if NOT found --- it's not a boolean
      // function, but instead returns "no position" if not found.
      //

		for (int i = 0; i < buildings.getNumMapBuildings(); i++)
		{
			Building &b = buildings.MapBuildings[i];
			int pos = b.Name.find(name) ; // 锁定这个目标building b

			if (pos >= 0)
			{
				cout << b.Name<<endl;
				cout << "Address: " << b.StreetAddress << endl;
				cout << "Building ID: " << b.ID << endl;

				cout << "Nodes:" << endl;
                // read 目标building b里的所有nodes
				for (size_t  j = 0; j< b.NodeIDs.size(); j++)
				{
					long   long  nid = b.NodeIDs[j];

					double  lat;
					double  lon; 
					bool  isEntrance;
					bool isFind= nodes.find( nid  ,lat,lon , isEntrance);
					if (isFind)
					{
						cout << "  " << nid << ": " << "(" << lat << ", " << lon << ")";
						if (isEntrance)
						{
							cout << ", is entrance";
						}
						cout << endl;
					}
					else
					{
						cout << "  "<< nid<< ": "<<"** NOT FOUND **"<<endl;
					} 
				}
			}
		}

    }
  }//while

  //
  // done:
  //
  cout << endl;
  cout << "** Done  **" << endl;
  cout << "# of calls to getID(): " << Node::getCallsToGetID() << endl;
  cout << "# of Nodes created: " << Node::getCreated() << endl;
  cout << "# of Nodes copied: " << Node::getCopied() << endl;
  cout << endl;

  return 0;
}
