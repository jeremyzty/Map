/*main.cpp*/

//
// Program to input Nodes (positions), Buildings and Footways
// from an Open Street Map file.
// 
// Prof. Joe Hummel
// Northwestern University
// CS 211: Winter 2023
// 

#include <iostream>
#include <string>
#include <iomanip>
#include <queue>
#include "building.h"
#include "buildings.h"
#include "footway.h"
#include "footways.h"
#include "node.h"
#include "nodes.h"
#include "osm.h"
#include "tinyxml2.h"
#include "graph.h"
#include "dist.h"


using namespace std;
using namespace tinyxml2;


void initG(graph &G ,Nodes &nodes, Footways &footways ) ;

void sanityCheck(graph &G ,Footways &footways ,long long id);

// 注意是buildings不是building
//
void navigate( graph &G , Buildings & buildings , Footways &footways,  Nodes &nodes);

vector<long long> Dijkstra(graph& G, 	long long startV, map<long long, double>& distances, map<long long, long long>&  prev);


 
//
// main
//
int main()
{
  cout << setprecision(12);


  XMLDocument xmldoc;
  Nodes nodes;
  Buildings buildings;
  Footways footways;
  
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
  // 2. read the nodes, which are the various known positions on the map:
  //
  nodes.readMapNodes(xmldoc);

  //
  // NOTE: let's sort so we can use binary search when we need 
  // to lookup nodes.
  //
  nodes.sortByID();

  //
  // 3. read the university buildings:
  //
  buildings.readMapBuildings(xmldoc);

  //
  // 4. read the footways, which are the walking paths:
  //
  footways.readMapFootways(xmldoc);



  graph  G;
  initG(G ,nodes,footways);


  //
  // 5. stats
  //
  cout << "# of nodes: " << nodes.getNumMapNodes() << endl;
  cout << "# of buildings: " << buildings.getNumMapBuildings() << endl;
  cout << "# of footways: " << footways.getNumMapFootways() << endl;
  cout << "# of graph vertices: " << G.NumVertices() << endl;
  cout << "# of graph edges: " << G.NumEdges() << endl;


  //
  // now let the user for search for 1 or more buildings:
  //
  while (true)
  {
    string name;

    cout << endl;
    cout << "Enter building name, * to list, @ to navigate, or $ to end>" << endl;

    getline(cin, name);

    if (name == "$") {
      break;
    }
    else if (name == "*") {
      buildings.print();
    }
    else if (name == "!") {
       sanityCheck(G , footways ,986532630);
    } 
    else if (name == "@") {
       navigate(G, buildings ,footways ,nodes);
    }
    else {
      buildings.findAndPrint(name, nodes, footways);
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


void initG(graph &G ,Nodes &nodes, Footways &footways )
{ 
    // fill the vector<long long> vertices. pair.first is NodeID
    for ( auto& pair : nodes )  // nodes? 为什么不是nodes.MapNodes?
    { 
      G.addVertex(  pair.first ); 
    }


     for ( Footway & f : footways.MapFootways )
    {  
      for(size_t j=0; j<f.NodeIDs.size()-1;++j) // 2个点，只会循环1次。3个点循环2次。
      {
          long long id1=  f.NodeIDs[j]; 
          
          double  lat1,   lon1; 
          bool  isEntrance1;
          nodes.find( id1,  lat1,   lon1, isEntrance1);

          long long id2=  f.NodeIDs[j+1]; 
          
          double  lat2,   lon2; 
          bool  isEntrance2;
          nodes.find( id2,  lat2,   lon2, isEntrance2);

          double dist=0;

          dist=distBetween2Points(  lat1,   lon1,    lat2,   lon2);
          G.addEdge( id1 , id2, dist ); // 往返

          dist=distBetween2Points(  lat2,   lon2,    lat1,   lon1); 
          G.addEdge( id2 , id1, dist );  // 往返        
      }

    }  
}


void sanityCheck(graph &G ,Footways &footways ,long long id)
{
  cout<<"Graph check of Footway ID "<<id<<endl;
  
   

    for ( Footway & f : footways.MapFootways ) // 所有footways
    {  
      if( f.ID  ==  id) // 找到id对应的那条footway
      {
          // 相邻两点之间是往返的
          for(size_t j=0; j<f.NodeIDs.size()-1;++j) 
          {
            long long id1=  f.NodeIDs[j]; 
            long long id2=  f.NodeIDs[j+1]; 

            double dist;
            G.getWeight(id1,id2, dist ); 
            cout<<"  Edge:("<<id1<<", "<<id2<<", "<<dist<<")"<<endl;
            G.getWeight(id2,id1, dist ); 
            cout<<"  Edge:("<<id2<<", "<<id1<<", "<<dist<<")"<<endl; 
           
          } 
          
          break;
      }

    }
    
}


 void navigate( graph &G , Buildings & buildings , Footways &footways,  Nodes &nodes)
 {
   
    cout<<"Enter start building name (partial or complete)>"<<endl;
    string start;
    getline(cin, start);
    Building bs = buildings.find(start); 
    if( bs.ID == 0)
    {
      cout<<"**Start building not found"<<endl;
      return;
    }

    // 获得起始building的approxiamte 位置
    // nodes是全部node的vector集合，因为要find latitude和longitude 
    // 
    pair<double ,double >    locS= bs.getLocation(nodes); 
    cout << "  Name: " << bs.Name << endl; 
    cout << "  Approximate location: ("<< locS.first <<", "<<  locS.second  <<")"<<endl;

    // 起始
    // 获得离起始building最近的footway的id，具体的点和距离
    // findMinDist()通过parameter来返回，返回以下三个变量
    Footway    s_fw(0) ; // 哪条footway
    long long  s_nid; // footway中的哪个节点
    double s_minDist; // building的locations离node 的距离
    footways.findMinDist( nodes ,locS.first , locS.second ,s_fw ,s_nid,s_minDist);
    cout<<"  Closest footway ID "<<s_fw.ID<<", node ID "<<s_nid<<", distance "<<s_minDist<<endl;

    ////////////////////////////////////////////////////////////////////

    cout<<"Enter destination building name (partial or complete)>"<<endl;
    string dest;
    getline(cin, dest);
    Building bd = buildings.find(dest); 
    if( bd.ID == 0)
    { 
      cout<<"**Destination building not found"<<endl;
      return;
    }   

    pair<double ,double > locD= bd.getLocation(nodes);
    cout << "  Name: " << bd.Name << endl; 
    cout << "  Approximate location: ("<< locD.first <<", "<<  locD.second  <<")"<<endl;
 
    // 目的地
    Footway    d_fw(0) ; 
    long long  d_nid;
    double d_minDist;
    footways.findMinDist( nodes ,locD.first , locD.second ,d_fw ,d_nid,d_minDist);
    cout<<"  Closest footway ID "<<d_fw.ID<<", node ID "<<d_nid<<", distance "<<d_minDist<<endl;


    vector<long long > visited; // visited过的node ID
    map<long long, double> distances;  // 总距离。k 每个目的节点ID，v 距离startV的距离

    // 上一个前置node，因为路是双向的。k current节点， v 它的上一个节点
    map<long long, long long>  prev; 
    long long startV = s_nid; // 起始Node ID
    visited = Dijkstra(G, startV, distances ,prev);

    cout<<"Shortest weighted path:"<<endl;

    if(distances[d_nid] < INF )
    {
            cout<<"  # nodes visited: "<<visited.size()<<endl; 
            cout<<"  Distance: "<<distances[d_nid]<<" miles"<<endl;  


            vector<long long > path;
            long long n = d_nid;
            while (  n > 0 )
            {
                // insert, 每次插入位置是开头begin，插入desti nodeID
                path.insert( path.begin() , n); 
                n = prev[n]; // Dijkstra找到的前置节点
            }

            cout<<"  Path: ";
            for( size_t i =0;i< path.size();++i)
            { 
              cout<<path[i];

              if( i <path.size() -1) cout<<"->";
            }
            cout<<endl;
    }
    else
    {
          cout<<"**Sorry, destination unreachable"<<endl;
    }
   

 }


class  prioritize
{
public:
	bool  operator() (const pair< long long, double >& p1, const pair< long long, double >& p2) const
	{
    // if value p1 > value p2 return true -> swap -> 值大的放在后面
		if (p1.second > p2.second) return true;
		else if (p1.second < p2.second) return false;
		else {
			// values the same, look at key:
			return p1.first > p2.first;
			// smaller keys first:
		}
	}
};

//
// Dijkstra: 
//
vector<long long> Dijkstra(graph& G, 	long long startV, map<long long, double>& distances ,map<long long, long long>&  prev)
{

	vector<long long>  visited;
  
  // priority_queue 是一个排序过的vector，
  // 每个vector的格子里存着一个pair
  // pair的k是当前Node ID，v是这个节点与起始节点的距离
  //
	priority_queue<
    pair<long long, double >,         // (key, value) pair
    vector<pair<long long, double >>, // store pairs in a vector
    prioritize >  unvisitedQueue;     // prioritize function

  // 把所有的vertices都提取出来，并存储到vector<long long> vec里
  // 把map<long long, double> distances 里每个节点到startV的距离都先摸认为INF
  //
	vector<long long> vec = G.getVertices();
	for (size_t i = 0; i < vec.size(); ++i) 
	{
		distances[vec[i]] = INF;
	}


	distances[startV] = 0;
  prev[startV]=0;
	unvisitedQueue.push(pair<long long, double>(startV, 0)); // priority_queue

	  
	while (!unvisitedQueue.empty())
	{
		auto p = unvisitedQueue.top(); // 返回给p的是一个pair<long long, double>
		unvisitedQueue.pop();

		long long  cur = p.first; // pair<long long, double>, p.first是Node ID

		// 看看当前的Node ID是否已经visited过了
		bool  flag = false;
		for (size_t i = 0; i < visited.size(); ++i)
		{
			if (visited[i] == cur)
			{
				flag = true;
			}
		} 
		if (flag) continue; // visited过了，跳过本次循环


    // 没visited过
		visited.push_back(cur);

    // neis存储着curNode的邻居节点
    // nodeIDs, set是一个有序的集合（数学）
    // 顺序是根据k来定义，k由小到大
    // 由于每次while loop都会重新定义set<long long> neis，
    // 所以每次开始都是空的
    //
		set<long long> neis = G.neighbors(cur); 

    // 遍历neis里每一个节点，用iterator it， 
    // *it表示它存的值 long long nodeID
    //
		for (auto it = neis.begin(); it != neis.end(); ++it)
		{

			double  weight = 0;
			G.getWeight(cur, *it, weight); // 以parameter的方式返回weight，*it是longlong node ID
			//cout<<*it<<"  " << weight<<endl; 

      // 如果发现了更短的距离，即distances[cur] + weight
      //
			if (distances[cur] + weight < distances[*it]) 
			{
         // 更新该邻居节点和startV之间的距离
				 distances[*it] = distances[cur] + weight;
         // 记录路径
         prev[*it]= cur ;
			}
      // 把该邻居节点放到unvisited里
      // 以pair的方式，因为是k ID，v distance
      // distance是它和startV的距离
      //
			unvisitedQueue.push(pair<long long, double>(*it, distances[*it]));

		}



	}


	return visited;
}