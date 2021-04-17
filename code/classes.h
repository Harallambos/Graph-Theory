#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

//  ---------CLASSES---------



//1
// class Point: this is a class for the points of set P, every point has 2 cordinates x and y
//----------------------------
class Point{ 
      
  private:         
    double x;
    double y;      
  public:
       // constructor
       Point(){     
          x = y = 0;           
       } 
       // constructor
       Point(double a, double b){ 
           
          x = a;
          y = b; 
          
       }
       // Extractors
        double getx(){  
           return x; 
        }
        double gety(){ 
           return y; 
        }   
       // print point
       void print(){    
           printf("(%.1lf, %.1lf)", x, y); 
       }
       // Move the existing point
       void move(double a, double b){
           x += a;
           y += b;
       }              
};


//2
// class Edge: this is a class for the edges of Voronoi diagram
//---------------------------------------------------------------
class Edge{
      private:
               int firstPointIndex;
               int lastPointIndex;
               int circumCenterIndex;
               int currCircumCenterIndex;
               Edge * neighbour;
              
      public:
             // empty constructor
             Edge(){
 
             }
             //constructor
             Edge(int fp, int lp, int cci, int ccci){
                    firstPointIndex = fp;
                    lastPointIndex = lp;
                    circumCenterIndex = cci;
                    currCircumCenterIndex = ccci;
                    neighbour = NULL;
             } 
             // get first point index
             int getFirstPointIndex(){
                   return firstPointIndex;
             }
             //get last point index
             int getLastPointIndex(){
                   return lastPointIndex;
             } 
             //get circum centers index
             int getCircumCenterIndex(){
                 return circumCenterIndex;
             }
             // get current circum center index
             int getCurrCircumCenterIndex(){
                 return currCircumCenterIndex;
             } 
             // get neighbour edge
             Edge *getNeighbour(){
                 return neighbour;
             }
             //set neigbour edge
             void setNeighbour(Edge *n){
                 neighbour = n;
             }
             //print the Edge
             void print(){
                    cout<<"( "<< firstPointIndex << ", " << lastPointIndex << ", " << circumCenterIndex << ", " << currCircumCenterIndex<<" )";  
              }             
};


//3
//clas PointsEdge : this class makes an edge from 2 points. This class is used for the edges of the convex hull of set P and the convex hull of the polygon Q
//------------------------------------------------------------------------------------------------------------------------------------------------------------
class PointsEdge{
      
      private:
             Point source; 
             Point target;
             
      public:
             // empty constructor
             PointsEdge(){
                          
             }
             //constructor
             PointsEdge(Point p1, Point p2){            
                  source = p1;
                  target = p2;         
             }
             // get source point
            Point getSource(){
                  return source;
             }
             //get target point
            Point  getTarget(){
                  return target;
             }
             // print PointsEdge
             void print(){
                  source.print();
                  printf("--->");
                  target.print();
                  printf("\n");     
             }           
};



//4
// class voronoi point: is used for the vertexes of the Voronoi diagram. We cll them VoronoiPoints
//-------------------------------------------------------------------------------------------------
class VoronoiPoint{ 
      
  private:         
    double x;
    double y;
    double radius; 
    int depth; 
    int prenum;
    int postnum; 
    Edge *edges;
    int edgesSize;
    
       
  public:
       // empty constructor  
       VoronoiPoint(){
                      
       }  
       // constructor
       VoronoiPoint(double a, double b, double r){ 
           x = a;
           y = b;
           radius = r;  
           depth = -1;
           prenum = -1;
           postnum = -1;              
           edgesSize = 0;
           edges = (Edge *) malloc( sizeof(Edge) );                         
       } 
       
       // Extractors
       
       //get x of VoronoiPoint
        double getx(){  
           return x; 
        }
        //get y of VoronoiPoint
        double gety(){ 
           return y; 
        }
        // get radius of the circle with center VoronoiPoint 
        double getRadius(){ 
           return radius; 
        }   
        //get depth . We give VoronoiPoint depth because we need it for the search in the path ps.
        int getDepth(){ 
           return depth; 
        }
        //set depth
        void setDepth(int x){
             depth = x;
        }
        int getPreNum(){ 
           return prenum; 
        }
        //set depth
        void setPreNum(int x){
             prenum = x;
        }
        int getPostNum(){ 
           return postnum; 
        }
        //set depth
        void setPostNum(int x){
             postnum = x;
        }
        // add Edge
        void addEdge(Edge edge){
        
           if(edgesSize == 0){
            
               edges[0] = edge;
               edgesSize++;
            
           } else {
        
               Edge prevEdge = edges[edgesSize];
            
               edges = (Edge *) realloc(edges, (edgesSize + 1) * sizeof(Edge));
               edges[edgesSize] = edge;
            
               prevEdge.setNeighbour(&edge);
            
               edgesSize++;
           }
       }
       
    // get Edges
    Edge *getEdges(){
        return edges;
    }
    //get Edge with this index 
    Edge getEdge(int index){
        return edges[index];
    }
    //print VoronoiPoint
    void print(){ 
        cout<<"( "<< x <<" , "<< y <<" ) radius = "<<radius;
        cout<<"  depth = "<< depth << "  preNum = "<< prenum << "  postNum = "<< postnum;
        cout<<"\n";
        int size = getEdgesSize();
        for(int i = 0; i < size; i++){
                cout<<"---> ";  
                edges[i].print();
        }
        cout<<"\n";  
    }
    // get Edges size
    int getEdgesSize(){
           return edgesSize;    
    }                     
};


//5
// class FileInputData: this is a class witch is used to collect all the data from a specified file we give to the program
//-------------------------------------------------------------------------------------------------------------------------
class FileInputData{
      
      private:
              int dimension;
              int numOfPoints;
              Point * pointsArray;
              
      public:
             // constructor
             FileInputData(int d, int nop, Point * p){
                           dimension = d;
                           numOfPoints = nop;
                           pointsArray = p;
                           
             }
             // get dimension
             int getDimension(){
                 return dimension;
             }
             //get number of points
             int getNumOfPoints(){
                 return numOfPoints;
             }
             // get points array
             Point * getPoints(){
                   return pointsArray;
             }
             //print the class FileInputData
             void print(){
                  printf("\n\ndimension: %d\n", dimension);
                  printf("number of points: %d\n", numOfPoints);
                  for(int i = 0; i < numOfPoints; i++){
                        pointsArray[i].print();
                        cout<<"\n"; 
                  } 
             }                       
};


//6
//class Triad: this is a class we use to make a array from triads witch we sort with "merge sort" and we can find the VoronoiPoints from this array
//-------------------------------------------------------------------------------------------------------------------------------------------------
class Triad{
      
      private:
              int firstPointIndex;
              int lastPointIndex;
              int circumCentreIndex;
      public:
             //empty constructor
             Triad(){
                      
             }
             //constructor
             Triad(int fp, int lp, int cc){
                        
                   firstPointIndex = fp;
                   lastPointIndex = lp;
                   circumCentreIndex = cc;     
                      
             }
             //get first point index
             int getFirstPointIndex(){
                 return firstPointIndex;
             }
             //get last point index
             int getLastPointIndex(){
                 return lastPointIndex;
             }
             //get circum center index
             int getCircumCentreIndex(){
                 return circumCentreIndex;
             }
             //print triad
             void print(){
                  
                  printf("  %d   %d   %d\n", firstPointIndex, lastPointIndex, circumCentreIndex);
             }           
};


//7
// class Line: we use this class to store a line. Every line is made by 2 Points. The equation of the line is ax + by + c = 0
//-----------------------------------------------
class Line{
      private:
              Point p1;
              Point p2;
              double a;
              double b;
              double c; 
              double lineFactor;
      public:
             //constructor
             Line(Point q1, Point q2){
                    p1 = q1;
                    p2 = q2;

                     a = p1.gety() - p2.gety();
                     b = p2.getx() - p1.getx();
                     c = -a*p1.getx() - b*p1.gety();
                     lineFactor = ( p2.gety() - p1.gety() ) / ( p2.getx() - p1.getx() );           
             }
             
             //get first point that makes the line
             Point getPointa(){
                   return p1;
             }
             //get second point that makes the line
             Point getPointb(){
                   return p2;
             }
             //get "a" from a line
              double geta(){           
                     return a;      
              }
              //get "b" from a line
              double getb(){       
                     return b;      
              }
              // get "c" from a line
              double getc(){        
                     return c;      
              }
              // get lines factor
              double getLineFactor(){   
                     return lineFactor;
              }
               
              // says if a point is on the line or not
              bool pointOnTheLine(Point p){
                  
                  double x,y,a,b,c;
                  x = p.getx();
                  y = p.gety();
                  a = geta();
                  b = getb();
                  c = getc();
                  
                  double distance = (a*x  + b*y + c)/ sqrt( pow(a,2) + pow(b,2) );
                  
                  if( distance == 0 ){
                      return true;
                  }
                  else{
                       return false;
                  }
              } 
                   
              //print line Ax + By + C = 0
              void print(){                
                     double a,b,c;    
                     a = geta();
                     b = getb();
                     c = getc();   
                     
                     if( a == 0)              
                         cout << "\n y = " << -(c/b) << "\n";
                     else if( b == 0 )
                         cout << "\n x = " << -(c/a) << "\n";
                     else                
                         cout << "\n " << a << "x + " << b << "y + " << c << " = 0 \n";
              }  
                 
              //print line y = lx + c
              void print2(){                
                   
                   double bb;
                   bb = -lineFactor * p1.getx() + p1.gety() ; 
                   if( lineFactor == 0 ) 
                       cout << "\n y = " << bb << " \n";  
                   else                                
                       cout << "\n y = " << lineFactor << "*x + " << bb << " \n";
              }        
};



//8
// class Circle: this class is used to store circles. Every  circle has a Point witch is its center and a double witch is its radius.
//--------------------------------------------------
class Circle{
      
      private:
              Point center;
              double radius;
      public:
             //constructor
             Circle(Point c, double r){
                    center = c;
                    radius = r;  
             }
             //get center
             Point getCenter(){
                    return center;
             }
             //get radius
             double getRadius(){
                    return radius;
             }
             //print circle
             void print(){
                  
                  double r = radius;
                  double x = center.getx();
                  double y = center.gety();
                  
                  cout<<"\n";
                  cout << "(x - "<<x<<")^2 + (y - "<<y<<")^2 = "<<r<<"^2"; 
             }    
};
