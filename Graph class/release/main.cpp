#include <iostream>
#include "gtest/gtest.h"
#include "graph.h"

using namespace std;

TEST(testing, test01)
{
   graph G;

  ASSERT_TRUE(G.NumVertices() ==0 );   
  ASSERT_TRUE(G.NumEdges() ==0 );   

  ASSERT_TRUE( G.addVertex("A") ); 
  ASSERT_TRUE(G.NumVertices() ==1);  

  ASSERT_TRUE( G.addVertex("A") == false);  
  ASSERT_TRUE(G.NumVertices() ==1);  

  ASSERT_TRUE( G.addVertex("B") );
  ASSERT_TRUE(G.NumVertices() ==2);  

  ASSERT_TRUE( G.addVertex("C") );
  ASSERT_TRUE(G.NumVertices() ==3);  
  
  ASSERT_TRUE( G.addVertex("D") ); 
  ASSERT_TRUE( G.addVertex("B")  == false);
  ASSERT_TRUE( G.addVertex("E") ); 
  ASSERT_TRUE( G.addVertex("F") ); 
  ASSERT_TRUE( G.addVertex("G") ); 
  ASSERT_TRUE( G.addVertex("H") ); 
  ASSERT_TRUE( G.addVertex("I") );   
  ASSERT_TRUE( G.addVertex("J") ); 
  ASSERT_TRUE( G.addVertex("I") == false); 
 
  ASSERT_TRUE(G.NumVertices() ==10 );   


   ASSERT_TRUE(G.addEdge( "A" ,"B" , 0.23)); 
   ASSERT_TRUE(G.NumEdges() ==1 );  
   ASSERT_TRUE(G.addEdge( "B" ,"A" , -0.03));
   ASSERT_TRUE(G.NumEdges() ==2);   
   ASSERT_TRUE(G.addEdge( "A" ,"C" , 100));  
   ASSERT_TRUE(G.NumEdges() ==3 );   
   ASSERT_TRUE(G.addEdge( "B" ,"C" , -100));  
   ASSERT_TRUE(G.addEdge( "E" ,"F" , 5000));
   ASSERT_TRUE(G.addEdge( "E" ,"H" , 40));  
   ASSERT_TRUE(G.addEdge( "G" ,"A" , -10000));         
   ASSERT_TRUE(G.addEdge( "J" ,"I" , 0.99));
   ASSERT_TRUE(G.addEdge( "D" ,"H" , 60));  
   ASSERT_TRUE(G.addEdge( "J" ,"C" , -90));   
   ASSERT_TRUE(G.addEdge( "B" ,"H" ,  0));
   ASSERT_TRUE(G.addEdge( "H" ,"F" , 80));  
   ASSERT_TRUE(G.addEdge( "F" ,"C" , 30));   

   ASSERT_TRUE(G.NumEdges() ==13 );   
   
}

TEST(testing, test02)
{
  graph G;

  ASSERT_TRUE( G.addVertex("A") );  
  ASSERT_TRUE( G.addVertex("B") );
  ASSERT_TRUE( G.addVertex("C") );
  ASSERT_TRUE( G.addVertex("D") );  
  ASSERT_TRUE( G.addVertex("E") ); 
  ASSERT_TRUE( G.addVertex("F") ); 
  ASSERT_TRUE( G.addVertex("G") ); 
  ASSERT_TRUE( G.addVertex("H") ); 
  ASSERT_TRUE( G.addVertex("I") );   
  ASSERT_TRUE( G.addVertex("J") ); 
  ASSERT_TRUE( G.addVertex("K") ); 


   ASSERT_TRUE(G.NumVertices() ==11 );   

 
   ASSERT_TRUE(G.NumEdges() ==0 );   
   ASSERT_TRUE(G.addEdge( "A" ,"A" , 0));   
   ASSERT_TRUE(G.NumEdges() ==1 );   
   ASSERT_TRUE(G.addEdge( "A" ,"B" , 0.23)); 
   ASSERT_TRUE(G.NumEdges() ==2 );   
   ASSERT_TRUE(G.addEdge( "B" ,"A" , -0.45));  
  ASSERT_TRUE(G.NumEdges() == 3 );   


   double aa=100;
   ASSERT_TRUE(G.getWeight( "A" ,"A" , aa )  );
   ASSERT_TRUE( aa == 0);

   double ab=0;
   ASSERT_TRUE(G.getWeight( "A" ,"B" , ab )  );
   ASSERT_TRUE( ab == 0.23 );
 
   double ba=0;
   ASSERT_TRUE(G.getWeight( "B" ,"A" , ba )  );
   ASSERT_TRUE( ba == -0.45 );   


   ASSERT_TRUE(G.addEdge( "Z" ,"A" , -0.03) == false );
    
   ASSERT_TRUE(G.NumEdges() ==3 );   
   ASSERT_TRUE(G.addEdge( "C" ,"Y" , -0.03) == false );
   ASSERT_TRUE(G.NumEdges() ==3 );   
   ASSERT_TRUE(G.addEdge( "Q" ,"Z" , -0.03) == false ); 
   ASSERT_TRUE(G.NumEdges() ==3 );   


   ASSERT_TRUE(G.addEdge( "A" ,"C" , 100));  
   ASSERT_TRUE(G.NumEdges() == 4 );   
   ASSERT_TRUE(G.addEdge( "B" ,"C" , -100));  
   ASSERT_TRUE(G.addEdge( "E" ,"F" , 5000));
   ASSERT_TRUE(G.addEdge( "E" ,"H" , 40));  
   ASSERT_TRUE(G.addEdge( "G" ,"A" , -10000));         
   ASSERT_TRUE(G.addEdge( "J" ,"I" , 0.99));
   ASSERT_TRUE(G.addEdge( "D" ,"H" , 60));  
   ASSERT_TRUE(G.addEdge( "J" ,"C" , -90));   
   ASSERT_TRUE(G.addEdge( "B" ,"H" ,  0));
   ASSERT_TRUE(G.addEdge( "H" ,"F" , 80));  
   ASSERT_TRUE(G.addEdge( "F" ,"C" , 30));   
  ASSERT_TRUE(G.NumEdges() ==14 );   

   double ga=0;
   ASSERT_TRUE(G.getWeight( "G" ,"A" , ga )  );
   ASSERT_TRUE( ga == -10000 );   

   ASSERT_TRUE(G.addEdge( "G" ,"A" , 222)); 
   ASSERT_TRUE(G.NumEdges() ==14 );   
   ASSERT_TRUE(G.getWeight( "G" ,"A" , ga )  );
   ASSERT_TRUE( ga ==  222 );  


   double ch=0;
   ASSERT_TRUE(G.getWeight( "C" ,"H" ,  ch )  == false);
   ASSERT_TRUE( ch ==  0 ); 

   double xa=0;
   ASSERT_TRUE(G.getWeight( "X" ,"A" ,  xa )  == false);
   ASSERT_TRUE( xa ==  0 );  

   double az=0;
   ASSERT_TRUE(G.getWeight( "A" ,"Z" ,  az )  == false);
   ASSERT_TRUE( az ==  0 ); 

   double xz=0;
   ASSERT_TRUE(G.getWeight( "X" ,"Z" ,  xz )  == false);
   ASSERT_TRUE( xz ==  0 ); 

  ASSERT_TRUE(G.NumEdges() ==14 );   

}




TEST(testing, test03)
{
  graph G;


  vector<string> v =  G.getVertices();
  ASSERT_TRUE( v.size() == 0);

  set<string> n =G.neighbors("A");
  ASSERT_TRUE( n.size() == 0);

  ASSERT_TRUE( G.addVertex("A") );  
  ASSERT_TRUE( G.addVertex("B") );
  ASSERT_TRUE( G.addVertex("C") );
  ASSERT_TRUE( G.addVertex("D") );  
  ASSERT_TRUE( G.addVertex("E") ); 
  ASSERT_TRUE( G.addVertex("F") ); 
  ASSERT_TRUE( G.addVertex("G") ); 
  ASSERT_TRUE( G.addVertex("H") ); 
  ASSERT_TRUE( G.addVertex("I") );   
  ASSERT_TRUE( G.addVertex("J") ); 
  ASSERT_TRUE( G.addVertex("K") ); 

   ASSERT_TRUE(G.NumVertices() ==11 );   

  vector<string> v2 =  G.getVertices();
  ASSERT_TRUE( v2.size() == 11);
  for(  size_t i=0;i< v2.size(); ++i)
  {
    char c = 'A'+ i;
    string str ;
    str.push_back(c);
    ASSERT_TRUE(   v2[i] ==  str) ;
  }
   ASSERT_TRUE(G.addEdge( "B" ,"B" , 100));  
   ASSERT_TRUE(G.addEdge( "B" ,"C" , -100)); 
   ASSERT_TRUE(G.addEdge( "B" ,"A" , -0.45));  


   ASSERT_TRUE(G.addEdge( "A" ,"A" , 0.12));  
   ASSERT_TRUE(G.addEdge( "A" ,"C" , 0.34)); 
   ASSERT_TRUE(G.addEdge( "A" ,"B" , 0.23)); 

 
   ASSERT_TRUE(G.addEdge( "C" ,"F" , 40));    
   ASSERT_TRUE(G.addEdge( "C" ,"J" , 5000));
   ASSERT_TRUE(G.addEdge( "C" ,"K" , 40));  
   ASSERT_TRUE(G.addEdge( "C" ,"E" , 5000));
   ASSERT_TRUE(G.addEdge( "C" ,"G" , 5000));
   ASSERT_TRUE(G.addEdge( "C" ,"H" , 40));   

     ASSERT_TRUE(G.NumEdges() ==12 );   
 
   set<string> n2 =G.neighbors("A");
   ASSERT_TRUE( n2.size() == 3);
   auto  it = n2.begin();
   ASSERT_TRUE( *  it ==  "A");
   ASSERT_TRUE( * (++it) ==  "B");
   ASSERT_TRUE( * (++it) ==  "C");  

   set<string> n3 =G.neighbors("C");
   ASSERT_TRUE( n3.size() == 6);
   auto  it3 = n3.begin();
   ASSERT_TRUE( *  it3 ==  "E");
   ASSERT_TRUE( * (++it3) ==  "F"); 
  ASSERT_TRUE( * (++it3) ==  "G"); 
  ASSERT_TRUE( * (++it3) ==  "H"); 
  ASSERT_TRUE( * (++it3) ==  "J"); 
  ASSERT_TRUE( * (++it3) ==  "K"); 

  set<string> n4=G.neighbors("D");
  ASSERT_TRUE( n4.size() == 0);



}





TEST(testing, test04)
{
  graph G;


  vector<string> v =  G.getVertices();
  ASSERT_TRUE( v.size() == 0);

  set<string> n =G.neighbors("A");
  ASSERT_TRUE( n.size() == 0);

  ASSERT_TRUE( G.addVertex("A") );  
  ASSERT_TRUE( G.addVertex("B") );
  ASSERT_TRUE( G.addVertex("C") );
  ASSERT_TRUE( G.addVertex("D") );  
  ASSERT_TRUE( G.addVertex("E") ); 
  ASSERT_TRUE( G.addVertex("F") ); 
  ASSERT_TRUE( G.addVertex("G") ); 
  ASSERT_TRUE( G.addVertex("H") ); 
  ASSERT_TRUE( G.addVertex("I") );   
  ASSERT_TRUE( G.addVertex("J") ); 
  ASSERT_TRUE( G.addVertex("K") ); 
  ASSERT_TRUE( G.addVertex("L") ); 
  ASSERT_TRUE( G.addVertex("M") ); 
  ASSERT_TRUE( G.addVertex("N") );  
  

   ASSERT_TRUE(G.NumVertices() ==14 );   

  vector<string> v2 =  G.getVertices();
  ASSERT_TRUE( v2.size() == 14);
  for(  size_t i=0;i< v2.size(); ++i)
  {
    char c = 'A'+ i;
    string str ;
    str.push_back(c);
    ASSERT_TRUE(   v2[i] ==  str) ;
  }
  
   ASSERT_TRUE(G.addEdge( "B" ,"B" , 100));  
   ASSERT_TRUE(G.addEdge( "B" ,"C" , -100)); 
   ASSERT_TRUE(G.addEdge( "B" ,"A" , -0.45));  


   ASSERT_TRUE(G.addEdge( "A" ,"A" , 0.12));  
   ASSERT_TRUE(G.addEdge( "A" ,"C" , 0.34)); 
   ASSERT_TRUE(G.addEdge( "A" ,"B" , 0.23)); 

   ASSERT_TRUE(G.addEdge( "C" ,"N" , 40));  
   ASSERT_TRUE(G.addEdge( "C" ,"L" , 5000));
   ASSERT_TRUE(G.addEdge( "C" ,"M" , 40));   
   ASSERT_TRUE(G.addEdge( "C" ,"F" , 40));  
   ASSERT_TRUE(G.addEdge( "C" ,"A" , 5000));
   ASSERT_TRUE(G.addEdge( "C" ,"J" , 5000));
   ASSERT_TRUE(G.addEdge( "C" ,"K" , 40));  
   ASSERT_TRUE(G.addEdge( "C" ,"I" , 5000));
   ASSERT_TRUE(G.addEdge( "C" ,"E" , 5000));
   ASSERT_TRUE(G.addEdge( "C" ,"G" , 5000));
   ASSERT_TRUE(G.addEdge( "C" ,"H" , 40));   

   ASSERT_TRUE(G.NumEdges() ==17 );   
  

   set<string> n3 =G.neighbors("C");
   ASSERT_TRUE( n3.size() == 11);
   auto  it3 = n3.begin();
   ASSERT_TRUE( *  it3 ==  "A");
   ASSERT_TRUE( * (++it3) ==  "E"); 
  ASSERT_TRUE( * (++it3) ==  "F"); 
  ASSERT_TRUE( * (++it3) ==  "G"); 
  ASSERT_TRUE( * (++it3) ==  "H"); 
  ASSERT_TRUE( * (++it3) ==  "I"); 

  set<string> n4=G.neighbors("Z");
  ASSERT_TRUE( n4.size() == 0);

  G.print(cout);



}


TEST(testing, test05)
{
  graph G;

  int N = 1000000;
  for( int i =0;i< N;++i)
  {
     string v = to_string(i); 
     G.addVertex( v ) ;    
  }

   ASSERT_TRUE(  G.NumVertices() ==   N);  
   
   /*
   for( int i =0;i< N-1;++i)
  {
     string f = to_string(i);  
     string t = to_string(i+1);
     G.addEdge( f, t , 100 ) ;    
  } 

  ASSERT_TRUE(  G.NumEdges() ==   N-1);

  */
}



int main()
{
    ::testing::InitGoogleTest();

    //
    // run all the tests, returns 0 if they
    // all pass and 1 if any fail:
    //
    int result = RUN_ALL_TESTS();

    return result;
}

