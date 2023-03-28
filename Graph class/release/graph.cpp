#include "graph.h" 


 
  //
  // constructor:
  //
 graph::graph()
 { 

	 EdgeCount = 0; 
 }

  //
  // NumVertices
  //
  // Returns the # of vertices currently in the graph.
  //
 int  graph::NumVertices() const
 {
	 return  Vertices.size();
 }

  //
  // NumEdges
  //
  // Returns the # of edges currently in the graph.
  //
 int  graph::NumEdges() const
 {
	 return EdgeCount;
 }

  //
  // addVertex
  //
  // Adds the vertex v to the graph if there's room, and if so
  // returns true.  If the graph is full, or the vertex already
  // exists in the graph, then false is returned.
  //
 bool  graph::addVertex(string v)
 { 
	 auto it = Vertex2Index.find(v);
     //already have the v
     if( it != Vertex2Index.end() )
     {
        return false;
     } 
      // Vertices node的index和Edges的index是对应一样的
      //
	  Vertex2Index.insert(make_pair(v, Vertices.size()));
	  Vertices.push_back(v); 
      // ？？ 是不是插入空map？？
	  Edges.push_back( map<int ,double>() ); 

	  return true;
 }

  //
  // addEdge
  //
  // Adds the edge (from, to, weight) to the graph, and returns
  // true.  If the vertices do not exist or for some reason the
  // graph is full, false is returned.
  //
  // NOTE: if the edge already exists, the existing edge weight
  // is overwritten with the new edge weight.
  //
 bool graph::addEdge(string from, string to, double weight)
 {
    auto it1 = Vertex2Index.find(from); 
    auto it2 = Vertex2Index.find(to);
    if( it1 == Vertex2Index.end()  ||  it2 == Vertex2Index.end())
    {
        return false;
    }   

    int  f = it1->second; // from
    int  t = it2->second; // to

     auto &e = Edges[f]; // e指向vector格子里的树
     if( e.find(t) == e.end() ) // 如果没这条路之前
     {
	     EdgeCount++;
     }
	 e[t] = weight; // []插入

	 return true;
 }

  //
  // getWeight
  //
  // Returns the weight associated with a given edge.  If 
  // the edge exists, the weight is returned via the reference
  // parameter and true is returned.  If the edge does not 
  // exist, the weight parameter is unchanged and false is
  // returned.
  //
 bool   graph::getWeight(string from, string to, double& weight) const 
 {

        auto it1 = Vertex2Index.find(from); 
        auto it2 = Vertex2Index.find(to);
        if( it1 == Vertex2Index.end()  ||  it2 == Vertex2Index.end())
        {
            return false;
        }  
     
   
	   int  f = it1->second;
	   int  t = it2->second;

       auto e =  Edges[f]; // e指向那棵树

       auto it3=e.find(t); // to
       if(  it3 == e.end() )
       { 
           return false;
       } 

       weight = it3->second;
	   return true;
 }

  //
  // neighbors
  //
  // Returns a set containing the neighbors of v, i.e. all
  // vertices that can be reached from v along one edge.
  // Since a set is returned, the neighbors are returned in
  // sorted order; use foreach to iterate through the set.
  //
 set<string>  graph::neighbors(string v)  const
 {
     set<string> s;
    
    // map 
    // 1. 是树
    // 2. 每个节点都是一个pair
    //
	 auto it = Vertex2Index.find(v);
     if( it != Vertex2Index.end() )
     {
            int f = it->second;

            auto& m= Edges[f]; // m指向树，[]是at
            // 把int 转化为string
            // transform applies a function([]) to a range(begin end)
            // and store the result in another range(inserter)
            //
            transform (m.begin(), m.end(),  
            inserter(s, s.end()),  // use iterator to store value in the container
            // 是map的类型 pair<int , double>&  p
            [this ]( const  pair<int , double>&  p) 
            { 
                return  Vertices[ p.first ];
            });

     } 

	
	 return s;

 }

  //
  // getVertices
  //
  // Returns a vector containing all the vertices currently in
  // the graph.
  //
 vector<string>  graph::getVertices() const
 {
	 return Vertices;
 }

  //
  // print
  // 
  // Prints the internal state of the graph for debugging purposes.
  //
  // Example:
  //    graph<string,int>  G(26);
  //    ...
  //    G.dump(cout);  // dump to console
  //
 void  graph::print(ostream& output) const
 {
 
        output << "# of vertices:"<< NumVertices()<<endl; 
        output << "**Vertices: ";

        for (string v : Vertices)
        {
            output << v << " ";
        }

        output << endl;

        output << "# of vertices:"<< NumEdges()<<endl; 
        output << "**Edges: ";

        for (string v : Vertices)
        {
            set<string> nei  =  neighbors(v);

            for (string n : nei)
            {
                double weight;
                
                if (getWeight(v, n, weight))
                {
                    output << "(" << v << "," << n << "," << weight << ") ";
                }
                else
                {
                    output << "(" << v << "," << n << "," << "???" << ") ";
                }
            }
        }

        output << endl;

 }
 