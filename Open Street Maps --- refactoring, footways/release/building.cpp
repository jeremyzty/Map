/*building.cpp*/

//
// A building in the Open Street Map.
// 
// Prof. Joe Hummel
// Northwestern University
// CS 211: Winter 2023
// 

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
// adds the given nodeid to the end of the vector.
//
void Building::add(long long nodeid)
{
	this->NodeIDs.push_back(nodeid);
}


// print node
void Building::print(Nodes& nodes, Footways &footways)
{

	cout << Name << endl;
	cout << "Address: " << StreetAddress << endl;
	cout << "Building ID: " << ID << endl;

	cout << "Nodes:" << endl;
	// 对于在building NodeIDs这个container里的node
	// 在building NodeIDs里找到node ID
	for (long long nodeid : NodeIDs) 
	{
		cout << "  " << nodeid << ": ";

		double lat = 0.0;
		double lon = 0.0;
		bool entrance = false;

		// 在全部nodes中搜索具体信息
		// 根据building 中的node ID，在nodes中找到对应的全部node信息，lat lon entrance
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


	cout << "Footways that intersect:" << endl;

	vector<Footway> vec; // 把符合条件的footway id存在这个vector里
	footways.findIntersect(NodeIDs, vec);
	if (vec.size() > 0)
	{
		for (Footway f : vec)
			cout << "  " << "Footway " << f.ID << endl;
	}
	else
	{
		cout << "  " << "None" << endl;
	}
}