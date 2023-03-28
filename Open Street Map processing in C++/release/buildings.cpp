#include "buildings.h"
#include <cassert>
#include "osm.h"


void Buildings::readMapBuildings(XMLDocument & xmldoc)
{

	XMLElement* osm = xmldoc.FirstChildElement("osm");
	assert(osm != nullptr);

	//
	// Parse the XML document way by way: 
	//
	XMLElement* way = osm->FirstChildElement("way");

	while (way != nullptr)
	{
		 
		// is  a  building
		if (osmContainsKeyValue(way, "building", "university"))
		{
			const XMLAttribute* attrId = way->FindAttribute("id");
			const XMLAttribute* attrVisable = way->FindAttribute("visible");

			assert(attrId != nullptr);
			assert(attrVisable != nullptr);

			long long wid = attrId->Int64Value();
			bool visable = attrVisable->BoolValue();

			string name = osmGetKeyValue(way, "name");
			string streetAddr = osmGetKeyValue(way, "addr:housenumber")
				+ " "
				+ osmGetKeyValue(way, "addr:street");

			Building  b(wid , name, streetAddr); 

			XMLElement* nd = way->FirstChildElement("nd");
			while (nd != nullptr)
			{
				const XMLAttribute* ndref = nd->FindAttribute("ref");
				assert(ndref != nullptr);
				long long id = ndref->Int64Value();
				b.add(id); 

			    // advance to next node ref:
			   nd = nd->NextSiblingElement("nd");
			}


			// This creates just one object "emplace", avoiding 
			// an extra Node copy each time:
			//
			this->MapBuildings.emplace_back( b ); 
		}

	 
		way = way->NextSiblingElement("way");
	}

}

int Buildings::getNumMapBuildings()
{
	return (int)this->MapBuildings.size();
}
