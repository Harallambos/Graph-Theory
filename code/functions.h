#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

//  ---------FUNCTION DECLARATIONS---------

Point getMidPoind(Point p1, Point p2);
FileInputData readFileInputData(char *filename);
Point * readConvexHullData(char *filename, Point * pointsArray);
Triad * readOffFileInputData(char *filename);
Point getTriangleCircumCentre(Point a, Point b, Point c);
int getTriadsArraySize(char *filename);
int getVoronoiPointsArraySize(char *filename);
int getConvexHullPointsArraySize(char *filename);
double getPointsDistance(Point p1, Point p2);
int getCircumCentersArraySize(char *filename);
VoronoiPoint * getVoronoiPointsArray(int voronoiPointsArraySize, Triad * triadsArray, int triadsArraySize, Point * circumCentersArray, int circumCentersArraySize, Point * setPpoints, int numOfPoints);
VoronoiPoint getMinimumRadiusVoronoiPoint(VoronoiPoint * voronoiPointsArray, int voronoiPointsArraySize);
Triad *mergeSort(Triad * triadsArray, int triadsArraySize);
Triad * merge(Triad *left, int leftSize, Triad *right, int rightSize);
//Point getMinimumCircleCenter( VoronoiPoint voronoiPoint);
int Turn(Point p1, Point p2, Point p3);
Point findMinimumSeparatingCircleCenter(VoronoiPoint minVoronoiPoint, Triad * triadsArray, int triadsArraySize, Point * setPpoints,int numOfPoints);
//Edge findMinimumSeparatingCircleCenterEdge (VoronoiPoint minVoronoiPoint, Triad * triadsArray, int triadsArraySize, Point * setPpoints,int numOfPoints);
Point lineIntersectsLine(Line line1, Line line2);
PointsEdge * getSetPedgesArray( Point * setPpoints, int numOfPoints );
PointsEdge * getPolygonEdgesArray( Point * setPpoints, int numOfPoints );
void setDepthToVoronoiPoints( int voronoiPointsArraySize );
int lineIntersectesCircle(Line line, Circle circle);
double apolitiTimi(double x);
int sgn(double x);
int getInternalTangentLine( Point * setPconvexHullPoints, int setPConvexHullPointsArraySize, Point * polygonsConvexHullPoints, int numOfPolygonPoints, int s  );
//Line internalTangent( Point * setPconvexHullPoints, int setPConvexHullPointsArraySize, Point * polygonsConvexHullPoints , int numOfPolygonPoints );
bool pointOnLine(Point point, Line line);
double max(double x, double y);
PointsEdge AlgorithmFunction( PointsEdge * VoronoiDiagramPath,  int VoronoiDiagramPathSize, PointsEdge * PolygonalChain, int PolygonalChainSize, VoronoiPoint s, VoronoiPoint cp);
double pointsDistanceFromLine( Line line, Point point );
void DFS( int v_id, int d , int * preNum_addr, int * postNum_addr);
void setDepthToVoronoiPoints( VoronoiPoint * voronoiPointsArray, int voronoiPointsArraySize, int minVoronoiPoint_id );
Point * getPolygonChainArray( int q1Index, int q2Index, Point * polygonsConvexHullPoints, int numOfPolygonPoints );
Edge * getVoronoiRegion( int pointIndex, int voronoiPointsArraySize );
void getVerticalLine( Line l, Point p );
bool AreNeighborsInVoronoiDiagram(VoronoiPoint vp1, VoronoiPoint vp2);


//========================================================================================================================================================================================================




//Array with voronoi points
//-------------------------
VoronoiPoint * voronoiPointsArray;





//========================================================================================================================================================================================================


//----------FUNCTIONS--------------



//1
// getTriadsArraySize: returns the size of the triads array
// 1 argument: a char pointer to the name of the file
//returs: an "int" witch is the size of the array with the triads
int getTriadsArraySize(char *filename){
    
    FILE *OffFile = fopen(filename, "r");
   
   int dimension;
   int numOfVertices;
   int numOfFacets;
   
   fscanf(OffFile, "%d", &dimension);
   fscanf(OffFile, "%d", &numOfVertices);
   fscanf(OffFile, "%d", &numOfFacets);
   
   int TriadsArraySize = numOfVertices + (2 * numOfFacets) - 3;
   
   fclose(OffFile);
   return TriadsArraySize;   
}

//2
//getVoronoiPointsArraySize: returs the size of the VoronoiPoints array
// 1 argument: a char pointer to the name of the file
//returns: an "int" witch is the size of the array with the VoronoiPoints
int getVoronoiPointsArraySize(char *filename){
    
    FILE *OffFile = fopen(filename, "r");
   
   int dimension;
   int numOfVertices;
   int numOfFacets;
   
   fscanf(OffFile, "%d", &dimension);
   fscanf(OffFile, "%d", &numOfVertices);
   fscanf(OffFile, "%d", &numOfFacets);
   
   fclose(OffFile);
   return numOfFacets;   
}

//3
// getCircumCentersArraySiz: returns the size of the Array with the circum centers
// 1 argument: a char pointer to the name of the file
//returns: an "int" witch is the size of the array with the circum centers
int getCircumCentersArraySize(char *filename){
    
    FILE *OffFile = fopen(filename, "r");
   
   int dimension;
   int numOfVertices;
   int numOfFacets;
   
   fscanf(OffFile, "%d", &dimension);
   fscanf(OffFile, "%d", &numOfVertices);
   fscanf(OffFile, "%d", &numOfFacets);
   fclose(OffFile);
   
   fclose(OffFile);
   return numOfFacets;   
}



//4
//getVoronoiPointsArraySize: returns the size of the Array with the Points of the convex hull of set P
// 1 argument: a char pointer to the name of the file
//returns: an "int" witch is the size of the array with the points of convex hull
int getConvexHullPointsArraySize(char *filename){
    
    FILE *OffFile = fopen(filename, "r");
   
   int numOfConvexHullPoints;
   
   
   fscanf(OffFile, "%d", &numOfConvexHullPoints);
   
   fclose(OffFile);
   return numOfConvexHullPoints;   
}







//5
// getMidPoint : returns the middle point of two given points
// 2 arguments: firts argument is a Point item and second is Point item too.
// returns : a Point item
Point getMidPoind(Point p1, Point p2){
                   
                   double midX;
                   double midY;
                   double x1,y1,x2,y2;
                   x1 = p1.getx();
                   y1 = p1.gety();
                   x2 = p2.getx();
                   y2 = p2.gety();
                   
                   midX = (x2+x1)/2;
                   midY = (y2+y1)/2;
                   Point midPoint(midX, midY);
                   
                   return midPoint;
}

//6
// getTriangleCircumCentre: returns the circum center of three points
// 3 arguments: three Points items
// returns: a Point item tha is the circum center of the tree points given
Point getTriangleCircumCentre(Point a, Point b, Point c){
      
                double x1,y1,x2,y2,x3,y3,u1,u2;
                x1 = a.getx();
                y1 = a.gety();
                x2 = b.getx();
                y2 = b.gety();
                x3 = c.getx();
                y3 = c.gety();

                double d;
                d = 2*(x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2));

                u1 = ( ((pow(x1,2.0) + pow(y1,2.0))*(y2-y3) + (pow(x2,2.0) + pow(y2,2.0))*(y3-y1) + (pow(x3,2.0) + pow(y3,2.0))*(y1-y2) ) ) / d ;
                u2 = ( ((pow(x1,2.0) + pow(y1,2.0))*(x3-x2) + (pow(x2,2.0) + pow(y2,2.0))*(x1-x3) + (pow(x3,2.0) + pow(y3,2.0))*(x2-x1) ) ) / d ;

                Point u(u1,u2);
                return (u);
}



//7
// getPointsDistance : returns the distance between two points
// 2 arguments: 2 Point items
// returns: a double number witch is the distance between the tow points given
double getPointsDistance(Point p1, Point p2){
       
       double distance;
       double x1,y1,x2,y2;
          
       x1 = p1.getx();
       y1 = p1.gety();
       x2 = p2.getx();
       y2 = p2.gety();
                    
       distance = sqrt( pow((x2-x1),2.0) + pow((y2-y1),2.0) );
          
       return distance;      
}



//8
//lineIntersectsLine: returns the intersection Point of 2 lines
//2 arguments: takes 2 Line items
//returns: a Points item witch is the intersection point of the 2 lines given
Point lineIntersectsLine(Line line1, Line line2){
    
    double x1,y1,x2,y2,x3,y3,x4,y4,x,y;
    Point p1 = line1.getPointa();
    Point p2 = line1.getPointb();
    Point p3 = line2.getPointa();
    Point p4 = line2.getPointb();
    
    x1 = p1.getx();
    y1 = p1.gety();
    x2 = p2.getx();
    y2 = p2.gety();
    x3 = p3.getx();
    y3 = p3.gety();
    x4 = p4.getx();
    y4 = p4.gety();
    
    x = ( ((x1*y2 - y1*x2)*(x3-x4)- (x1-x2)*(x3*y4 -y3*x4))/ ( (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4) ) );
    y = ( ((x1*y2 - y1*x2)*(y3-y4)- (y1-y2)*(x3*y4 -y3*x4))/ ( (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4) ) );
    
    Point p(x, y);
    
    if( ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4)) == 0 ){
        //printf("LINES ARE PARALLEL\n");
       // printf("THERE IS NO INTERSECTION POINT\n");
    }
    else{
        // printf("LINES ARE NOT PARALLEL\n");
        // printf("INTERSECTION POINT IS:\n");
        // p.print();
         return p;
    }
    
    
}



//9
// pointOnLine: returns true if the point is on the lne and false if point is not on the line
//2 arguments: first arguments is a Point item and the second is a Lne item 
// reurtns: true if point is n the line, otherwise return false 
bool pointOnLine(Point point, Line line){
    
    double x,y,a,b,c,distance;
    x = point.getx();
    y = point.gety();
    
    a = line.geta();
    b = line.getb();
    c = line.getc();
    
    double temp = a*x  + b*y + c;
    //distance = apolitiTimi(temp / sqrt( pow(a,2) + pow(b,2)) );
                  
    if( temp == 0 ){
        //cout<<"\n Point is on the line \n";
        return true;
    }
    else{
        //cout<<"\n Point is not on the line \n"; 
        return false;
    }
      
     
}


//10
// readFileInputData: This function reads the data from a file and store the data to a FileInputData item
// 1 argument: a char pointer witch is the name of the file we want to read  
//returns: an FileInputData item after it fills it with the data the function read from the file
FileInputData readFileInputData(char *filename){
     
   FILE *pointsFile = fopen(filename, "r");
   int dimension;
   int numOfPoints;
   
   if(pointsFile == NULL){
        printf("Can't open input file! \n");
        exit(1);
   }
   
   fscanf(pointsFile, "%d", &dimension);
   fscanf(pointsFile, "%d", &numOfPoints);
   
   Point * pointsArray;
   pointsArray =(Point *) malloc ( numOfPoints*sizeof(Point) );
   if(pointsArray == NULL){
        printf("Error: out of bounts! \n");
        exit(1);
   }
   
   if( numOfPoints < 3 ){
       printf("To synolo twn shmeiwn prepei na einai >= 3"); 
       exit(0);
   }    
   else{    
     printf("Diastasi xwrou : %d\n", dimension);
     printf("Arithmos simeiwn : %d \n", numOfPoints);
   
     for(int i = 0; i < numOfPoints; i++){
                
       double x, y;              
     
       fscanf(pointsFile, "%lf", &x);
       fscanf(pointsFile, "%lf", &y);
       Point point(x, y);
       pointsArray[i] = point;
       point.print();
       cout<<"\n";                     
     }
   
     FileInputData inputData(dimension, numOfPoints, pointsArray);
     
     fclose(pointsFile); 
     return inputData;
  }    
}


//11
// readConvexHullData :Reads data from a file and store it to a n array with Point items
//2 arguments: first one is a char pointer to the filename and the second is an array with Point items
//returns: an array with Point items that are the points of the convex hull
Point * readConvexHullData(char *filename, Point * pointsArray){
                        
   FILE * pointsConvexHullFile = fopen(filename, "r"); 
   int numOfVertexes; 
   
   if(pointsConvexHullFile == NULL){
        printf("Can't open input file! \n");
        exit(1);
   } 
   
   fscanf(pointsConvexHullFile, "%d", &numOfVertexes);
   Point * convexHullArray;
   convexHullArray = (Point *) malloc ( numOfVertexes*sizeof(Point) );
   if(convexHullArray == NULL){
        printf("Error: out of bounts! \n");
        exit(1);
   }
     
   printf("Arithmos koryfwn: %d\n",numOfVertexes);
   printf("Ta shmeia pou dimiourgoun to kyrto perivlima einai: \n");
   
   
   for(int i = 0; i < numOfVertexes; i++){
                          
     int x;               
     fscanf(pointsConvexHullFile, "%d", &x);
     convexHullArray[i] = pointsArray[x];
     printf("\n");   
     convexHullArray[i].print();                      
   }
   
   fclose(pointsConvexHullFile);
   return convexHullArray;                    
}



//12
// synartisi OffFileInputData diavazei dedomena apo ena arxeio OFF file
Triad * readOffFileInputData(char *filename, Point * circumCentersArray){
     
   FILE *OffFile = fopen(filename, "r");
   
   int dimension;
   int numOfVertices;
   int numOfFacets;
   int numOfEdges;
   //int index;
   //Triad triad;
   //Point circumCenter;
   
   if(OffFile == NULL){
        printf("Can't open input file! \n");
        exit(1);
   }
   
   fscanf(OffFile, "%d", &dimension);
   fscanf(OffFile, "%d", &numOfVertices);
   fscanf(OffFile, "%d", &numOfFacets);
   fscanf(OffFile, "%d", &numOfEdges);
   
   if( numOfVertices < 3 ){
       printf("To synolo twn shmeiwn prepei na einai >= 3"); 
       exit(1);
   }  
   
   int numOfTriads = numOfVertices + 2 * numOfFacets - 3;
   int numOfProducedTriads = 0;
    
     Point * pointsArray;
     pointsArray = (Point *) malloc ( numOfVertices * sizeof(Point) );
     if(pointsArray == NULL){
        printf("Error: out of memory! \n");
        exit(1);
     }
     
     int * indexesArray;
     indexesArray = (int *) malloc ( numOfVertices * sizeof(int) );
     if(indexesArray == NULL){
        printf("Error: out of memory! \n");
        exit(1);
     }    
     
     
     int * circumCentersIndexArray;
     circumCentersIndexArray = (int *) malloc ( numOfFacets * sizeof(int) );
     if(circumCentersIndexArray == NULL){
        printf("Error: out of memory! \n");
        exit(1);
     }
     
     Triad * triadsArray;
     triadsArray = (Triad *) malloc ( numOfTriads * sizeof(Triad) );
     if(triadsArray == NULL){
        printf("Error: out of memory! \n");
        exit(1);
     }
        
     
     for(int i = 0; i < numOfVertices; i++){
                
       double x, y, z;              
       
       fscanf(OffFile, "%lf", &x);
       fscanf(OffFile, "%lf", &y);
       fscanf(OffFile, "%lf", &z);
       
       Point point(x, y);
       
       pointsArray[i] = point;
       indexesArray[i] = i;   
     }
     
     int tempNumOfTriads = 0;
     
     for(int i = 0; i < numOfFacets; i++){
         
         int numOfFacetVertices; 
         fscanf(OffFile, "%d", &numOfFacetVertices);
     
         int facetVertices[numOfFacetVertices];
         for(int j = 0; j < numOfFacetVertices; j++)
             fscanf(OffFile, "%d", &facetVertices[j]); 
      
         Point circumCentre = getTriangleCircumCentre(pointsArray[facetVertices[0]], pointsArray[facetVertices[1]], pointsArray[facetVertices[2]]);
         circumCentersArray[i] = circumCentre;
         circumCentersIndexArray[i] = i;
         
         int firstPoint;
         int previousPoint;
         
         for(int j = 0; j < numOfFacetVertices; j++){
             
             int source;
             int target;
             int pointIndex;
             
             if(j == 0){
                 source = facetVertices[j];
                 firstPoint = source;
             } 
             else {
                 
                 source = previousPoint;
             }
             
             if(j < (numOfFacetVertices - 1)){
                
                target = facetVertices[j + 1];
                
             } 
             else {
                 target = firstPoint;
             }
             
             if(source < target){
                 Triad triad(source, target, circumCentersIndexArray[i]);
                 triadsArray[numOfProducedTriads] = triad;
                 numOfProducedTriads++;
             }
             else{
                 Triad triad(target, source, circumCentersIndexArray[i]);
                 triadsArray[numOfProducedTriads] = triad;
                 numOfProducedTriads++;
             }
             
             previousPoint = target;
         }
         
     }
     
    fclose(OffFile);  
    return triadsArray;                   
}

//13
//getSetPedgesArray: this function return an array of pointsEdge items and its the edges of the convex hull of set P
// 2 arguments: takes an array with Pointitems tha are the points of set P and an "integer" that is the size of this array
//returns: an array with PointsEdge items
PointsEdge * getSetPedgesArray( Point * setPpoints, int numOfPoints ){
           
          PointsEdge * pointsEdgeArray;
          
          pointsEdgeArray = (PointsEdge *) malloc ( numOfPoints * sizeof(PointsEdge) );
          if(pointsEdgeArray == NULL){
              printf("Error: out of memory! \n");
              exit(1);
          }
          
                  
           for( int i = 0; i < numOfPoints; i++ ){
                
                if(i == numOfPoints - 1){
                     Point source = setPpoints[i];
                     Point target = setPpoints[0];
                     
                     PointsEdge edge(source, target);
                     pointsEdgeArray[i] = edge;
                    // pointsEdgeArray[i].print();
                }
                else{
                      
                    Point source = setPpoints[i];
                    Point target = setPpoints[i+1];
                
                    PointsEdge edge(source, target);
                    pointsEdgeArray[i] = edge;
                   // pointsEdgeArray[i].print();
                }    
                
           }
           return pointsEdgeArray;
}


//14
//getPolygonEdgesArray: returns an array of PointsEdge items that are the edges of the polygon Q
//2 arguments : takes an array with Point items that are the points of Polygon and en integer tha is the size of this array
//returns: an array of PointsEdge items 
PointsEdge * getPolygonEdgesArray( Point * setPpoints, int numOfPoints ){
           
           
          PointsEdge * polygonEdgesArray;
          
          polygonEdgesArray = (PointsEdge *) malloc ( numOfPoints * sizeof(PointsEdge) );
          if(polygonEdgesArray == NULL){
              printf("Error: out of memory! \n");
              exit(1);
          } 
          
                  
           for( int i = 0; i < numOfPoints; i++ ){
                
                if(i == numOfPoints - 1){
                     Point source = setPpoints[i];
                     Point target = setPpoints[0];
                     
                     PointsEdge edge(source, target);
                     polygonEdgesArray[i] = edge;
                     //polygonEdgesArray[i].print();
                }
                else{
                      
                    Point source = setPpoints[i];
                    Point target = setPpoints[i+1];
                
                    PointsEdge edge(source, target);
                    polygonEdgesArray[i] = edge;
                    //polygonEdgesArray[i].print();
                }
           }
           return polygonEdgesArray;
}


//15
//mergeSort: returns a sorted array with triads 
//2 arguments: a Triads item array and its size ( the array with the triads is not sorted )
//returs: a sortedTriads items array ( we sort it in a certen way )
Triad *mergeSort(Triad * triadsArray, int triadsArraySize){
    
    if(triadsArraySize <= 1){
        return triadsArray;
    } else {
        
        int leftSize;
        int rightSize;
        
        int middle = triadsArraySize / 2;
        
        if(triadsArraySize % 2 == 0)
            leftSize = rightSize = middle;
        else {
            leftSize = middle;
            rightSize = middle + 1;
        }
        
        Triad *left = (Triad *) malloc( sizeof(Triad) * leftSize );
        Triad *right = (Triad *) malloc( sizeof(Triad) * rightSize );
        
        for(int i = 0; i < middle; i++){
            left[i] = triadsArray[i];
        }
        
        for(int i = middle; i < triadsArraySize; i++){
            right[i - middle] = triadsArray[i];
        }
        
        left = mergeSort(left, leftSize);
        right = mergeSort(right, rightSize);
        
        Triad *result = merge(left, leftSize, right, rightSize);
        
        return result;
    }
}


//16
//merge: taksinomei kai epistrefei pinaka triadwn me taksinomisi merge sort
Triad * merge(Triad *left, int leftSize, Triad *right, int rightSize){
    
    Triad *result = (Triad *) malloc( sizeof(Triad) * (leftSize + rightSize) );
    int resultCurrSize = 0;
    int nextLeftIndex = 0;
    int nextRightIndex = 0;
    
    while(leftSize > 0 || rightSize > 0){
        
        if(leftSize > 0 && rightSize > 0){
            
            if(left[nextLeftIndex].getFirstPointIndex() < right[nextRightIndex].getFirstPointIndex()){
                result[resultCurrSize] = left[nextLeftIndex];
                resultCurrSize++;
                nextLeftIndex++; 
                leftSize--;
                
            } else if(left[nextLeftIndex].getFirstPointIndex() == right[nextRightIndex].getFirstPointIndex()) {
                
                if(left[nextLeftIndex].getLastPointIndex() <= right[nextRightIndex].getLastPointIndex()){
                    result[resultCurrSize] = left[nextLeftIndex];
                    resultCurrSize++;
                    nextLeftIndex++; 
                    leftSize--;
                } else {
                    result[resultCurrSize] = right[nextRightIndex];
                    resultCurrSize++;
                    nextRightIndex++;
                    rightSize--;
                }
                
            } else {
                result[resultCurrSize] = right[nextRightIndex];
                resultCurrSize++;
                nextRightIndex++;
                rightSize--;
            }
            
        } else if(leftSize > 0){
            result[resultCurrSize] = left[nextLeftIndex];
            resultCurrSize++;
            nextLeftIndex++;
            leftSize--;
            
        } else if(rightSize > 0){
            result[resultCurrSize] = right[nextRightIndex];
            resultCurrSize++;
            nextRightIndex++;
            rightSize--;
        }
    }
    
    return result; 
}



//17
//getVoronoiPointsArray: returns an array with VoronoiPoints item array
//7 argumenst: the size of VoronoiPointsArray,  an array withe triads sorted, the size of triads array, an array with the circum centers and its size, an array with the points of set P and its size
//returns: an array with VoronoiPoint items
VoronoiPoint * getVoronoiPointsArray(int voronoiPointsArraySize, Triad * sortedTriadsArray, int triadsArraySize, Point * circumCentersArray, int circumCentersArraySize, Point * setPpoints, int numOfPoints){
    
    VoronoiPoint * voronoiPointsArray;// pinakas me shmeia voronoi
    voronoiPointsArray = (VoronoiPoint *) malloc ( voronoiPointsArraySize * sizeof(VoronoiPoint) );
    if(voronoiPointsArray == NULL){
         printf("Error: out of memory! \n");
         exit(1);
    }
    
    
    double x,y,d;
    for(int i = 0; i < voronoiPointsArraySize; i++){
          x = circumCentersArray[i].getx(); 
          y = circumCentersArray[i].gety(); 
          
          for (int j = 0; j < triadsArraySize ; j++){
              if( i == (sortedTriadsArray[j].getCircumCentreIndex()) ){
                     
                     
                      int pointIndex = sortedTriadsArray[j].getFirstPointIndex();  
                      d = getPointsDistance(circumCentersArray[i], setPpoints[pointIndex]);
             
             }
          }
          VoronoiPoint vp(x, y, d);
          voronoiPointsArray[i] = vp;
    }
    
    
    int prevStepFirstTriadCircumCentreIndex;
    bool normalEdgeInsertedAtPrevStep = false;
    
    for(int i = 0; i < triadsArraySize - 1; i++){
  
            Triad firstTriad = sortedTriadsArray[i];
     
            int firstTriadFirstPointIndex = firstTriad.getFirstPointIndex();
            int firstTriadLastPointIndex = firstTriad.getLastPointIndex();
            int firstTriadCircumCentreIndex = firstTriad.getCircumCentreIndex();
            
            Triad secondTriad = sortedTriadsArray[i + 1];

            int secondTriadFirstPointIndex = secondTriad.getFirstPointIndex();
            int secondTriadLastPointIndex = secondTriad.getLastPointIndex();
            int secondTriadCircumCentreIndex = secondTriad.getCircumCentreIndex();

            if(firstTriadFirstPointIndex == secondTriadFirstPointIndex && firstTriadLastPointIndex == secondTriadLastPointIndex){

                Edge edge(firstTriadFirstPointIndex, firstTriadLastPointIndex, secondTriadCircumCentreIndex, firstTriadCircumCentreIndex);
                voronoiPointsArray[firstTriadCircumCentreIndex].addEdge(edge);
                
                if(i == triadsArraySize - 2){
                    
                    Edge edge(secondTriadFirstPointIndex, secondTriadLastPointIndex, secondTriadCircumCentreIndex, secondTriadCircumCentreIndex);
                    voronoiPointsArray[secondTriadCircumCentreIndex].addEdge(edge);
                }

                prevStepFirstTriadCircumCentreIndex = firstTriadCircumCentreIndex;
                normalEdgeInsertedAtPrevStep = true;

            } else {

                if(!normalEdgeInsertedAtPrevStep){
                    Edge edge(firstTriadFirstPointIndex, firstTriadLastPointIndex, -1, firstTriadCircumCentreIndex);
                    voronoiPointsArray[firstTriadCircumCentreIndex].addEdge(edge);
                    
                    normalEdgeInsertedAtPrevStep = false;

                } else {

                    Edge edge(firstTriadFirstPointIndex, firstTriadLastPointIndex, prevStepFirstTriadCircumCentreIndex, firstTriadCircumCentreIndex);
                    voronoiPointsArray[firstTriadCircumCentreIndex].addEdge(edge);
                    
                    normalEdgeInsertedAtPrevStep = false;
                }
                
                if(i == triadsArraySize - 2){
                    
                        Edge edge(secondTriadFirstPointIndex, secondTriadLastPointIndex, -1, secondTriadCircumCentreIndex);
                        voronoiPointsArray[secondTriadCircumCentreIndex].addEdge(edge);
                }
            }
            
    }
    
    return voronoiPointsArray;
}



//18
// getMinimumDistanceVoronoiPoint: epistrefei to voronoipoint me tin mikroteri aktina
// me ayti tin synartisi vriskoume diladi to Cp kentro tou mikroterou kyklou pou perilamvanei ta shmeia tou synolou P (mikroterou P-circle)
// den exei kapoio lathos i synartisi apla to kentro ayto pou vriskei einai to perikentro me tin mikroteri aktina 
// (perikentra einai ta kentra twn kyklwn poy exoun stin periferia tous ta 3 shmeia tou trigwnou...pou prokyptoun apo tin delauny trigwnopoihsh)
// ta perikentra  telika einai oi komvoi tou diagrammatos voronoi kai epilegoume ayto me tin mikroteri aktina kai theoroume ayto san to Cp
VoronoiPoint getMinimumRadiusVoronoiPoint(VoronoiPoint * voronoiPointsArray, int voronoiPointsArraySize){
      
      double minVoronoiPointRadius;
      int minVoronoiPointRadiusIndex;
      
      minVoronoiPointRadius = voronoiPointsArray[0].getRadius();
      minVoronoiPointRadiusIndex = 0;
      for(int i = 1; i < voronoiPointsArraySize; i++){
                 if( voronoiPointsArray[i].getRadius() < minVoronoiPointRadius ){
                     minVoronoiPointRadius = voronoiPointsArray[i].getRadius();
                     minVoronoiPointRadiusIndex = i;
                 }
      }
      
      return   voronoiPointsArray[minVoronoiPointRadiusIndex];
}





//19
//Turn: returns 1 if the turn of the tree points given is a right turn
//              -1 if the turn of the tree points given is a left turn
//               0 the turn of the tree points given are in the same line
//3 arguments: takes 3 Point items
//returns: an integer 1 if the turn of the tree points given is a right turn
//              -1 if the turn of the tree points given is a left turn
//               0 the turn of the tree points given are in the same line
int Turn(Point p1, Point p2, Point p3){
    
    double x1,y1,x2,y2,x3,y3;
    double det;
    
    x1 = p1.getx();
    y1 = p1.gety();
    x2 = p2.getx();
    y2 = p2.gety();
    x3 = p3.getx();
    y3 = p3.gety();
    
    double Matrix[3][3]={x1,y1,1,x2,y2,1,x3,y3,1};
    
    det = x1*y2 - y1*x2 - x1*y3 + y1*x3 + x2*y3 - y2*x3 ;
    
    if(det > 0){
         return 1;
    }
    else if(det < 0){
         return -1;
    }
    else{
         return 0;
    }
       
}



//20
// findMinimumSeparatingCircleCenter: epistrefei to kentro tou mikroterou kyklou diaxwrismou
//??????????????????????????????????????????????????????????????????????????????????????????????????????
Point findMinimumSeparatingCircleCenter(VoronoiPoint minVoronoiPoint, Triad * triadsArray, int triadsArraySize, Point * setPpoints,int numOfPoints){

    int edgesArraySize = minVoronoiPoint.getEdgesSize();
    Edge * edges;
    edges = (Edge*) malloc (edgesArraySize*sizeof(Edge));
    if( edges == NULL ){
         printf(" ERROR\n ");
         exit(0);
    }
    
    edges = minVoronoiPoint.getEdges();
    
    
    for(int i = 0; i < edgesArraySize; i++){
            
            Edge edge = edges[i];
            int aa = edge.getCurrCircumCenterIndex();
            int bb = edge.getCircumCenterIndex();
            int vv = edge.getFirstPointIndex();
            int uu = edge.getLastPointIndex();
            
            Point a = setPpoints[aa];
            Point b = setPpoints[bb];
            Point v = setPpoints[vv];
            Point u = setPpoints[uu];
            
            if( ( Turn(v, u, a) ) == 0){
                 return a;
            }
            else if( ( Turn(v, u, b) ) == 0){
                 return b;
            }
            else if( ( Turn(v, u, a) ) == ( Turn(v, u, b) ) ){
                 
                 //printf(" EDGE REGECTED \n");
            }
            else{
            
                 double x1,y1,x2,y2,z1,z2;
                 
                 x1 = v.getx(); 
                 y1 = v.gety();
                 x2 = u.getx();
                 y2 = u.gety();
                 
                 z1 = (x1 + y1)/2;
                 z2 = (x2 + y2)/2;
                 
                 Point center(z1,z2);
                 return center;
            }             
    }
         
}



//21
//apolitiTimi: returs the absolute value of a double
//1 argument: takes a double
//returns: a double witch is the absolute value of the double given
double apolitiTimi(double x){
       if(x < 0)
          return -x;
       else if(x > 0)
          return x;
       else 
          return 0;      
}


//22
// sgn: returns -1 if x<0 and returns 1 otherwise 
//1 argument: takes a double
//returns: -1 if double is < 0  and returns 1 atherwise
int sgn(double x){
    if(x<0)
        return -1;
    else
        return 1;     
}


//23
//lineIntersectesCircle: returns 0 if line does not intersect circle
//                               1 if line interscts circle in one point ( that means tha line is tangent tou circle )
//                               2 if line intersects circle in two points
// 2 arguments: one Line item and one Circle item
//returns: an integer 0 if line does not intersect circle
//                               1 if line interscts circle in one point ( that means tha line is tangent tou circle )
//                               2 if line intersects circle in two points   
int lineIntersectesCircle(Line line, Circle circle){

     
    Point p1 = line.getPointa();
    Point p2 = line.getPointb();
    
    double r = circle.getRadius();
    Point center = circle.getCenter();
    
    double distance = pointsDistanceFromLine( line, center );
    
    if( distance > r ){
        cout<<"\n NO INTERSECTION \n";
        return 0;
    }
    else if( distance == r ){
        cout<<"\n LINE TANGENT TO CIRCLE, ONE INTERSECTION POINT \n";
        return 1;
    }
    else{
        cout<<"\n LINE INTERSECTS CIRCLE IN 2 POINTS \n";
        return 2;
    }
    
    
}


//24
// LineIntersectsConvexHull: returns  the intersection point between a line and a convex hull of the set P
// 3 arguments: a Line item , an array with the adges of the convex hull of st P and the size of the array
//returns : a Point item witch isthe intersection point between line and the convex hull of set P
//den douleuei kala epeidei kalei tin pointsPlaceInAnEdge pou den douleuei swsta
int getInternalTangentLine( Point * setPconvexHullPoints, int setPConvexHullPointsArraySize, Point * polygonsConvexHullPoints, int numOfPolygonPoints, int s ){

       //Line l1,l2;
       Point p1, p, p2, q1, q, q2;
       
       for( int i = 0; i < setPConvexHullPointsArraySize; i++ ){
            
            if( i==0 )
                p1 = setPconvexHullPoints[setPConvexHullPointsArraySize-1];
            else
                p1 = setPconvexHullPoints[i-1];
            p = setPconvexHullPoints[i];
            if( i==setPConvexHullPointsArraySize-1 )
                p2 = setPconvexHullPoints[0];
            else
                p2 = setPconvexHullPoints[i+1];

            for( int j = 0; j < numOfPolygonPoints; j++ ){
                 
                 if( j==0 )
                     q1 = polygonsConvexHullPoints[numOfPolygonPoints-1];
                 else
                     q1 = polygonsConvexHullPoints[j-1];
                 q = polygonsConvexHullPoints[j];
                 if( j==numOfPolygonPoints-1 )
                     q2 = polygonsConvexHullPoints[0];
                 else
                     q2 = polygonsConvexHullPoints[j+1];
            
               int t1, t2, t3, t4;
                 
                 t1 = Turn(p, q, p2);
                 t2 = Turn(p, q, q2);                
                 if ( t1 == 0 || t2 == 0 || t1 != -t2 || t1 != s )
                    continue;
                 t3 = Turn(p, q, p1);
                 t4 = Turn(p, q, q1);
                 if ( t3 == -t1 || t4 == -t2 )
                    continue;
                     
                 cout<<"\nTANGENT LINE: ("<<p.getx()<<","<<p.gety();
                 cout<<") - ("<<q.getx()<<","<<q.gety()<<")";
                 cout<<"   (t1 = "<<t1<<")\n";
                 
                 return j;
            }
       }
}





//25
// synartisi DFS : gives depth to all voronoipoints of our voronoi diagram
void DFS( int v_id, int d , int * preNum_addr, int * postNum_addr)
{
     //cout<<"visiting vertex ("<<voronoiPointsArray[ v_id ].getx();
     //cout<<","<<voronoiPointsArray[ v_id ].gety()<<")\n";
     voronoiPointsArray[ v_id ].setDepth(d);
     voronoiPointsArray[ v_id ].setPreNum((*preNum_addr)++);
     
     //voronoiPointsArray[ v_id ].print();
     
     int edgesSize = voronoiPointsArray[ v_id ].getEdgesSize();
     Edge edge;
     
     for( int i = 0; i < edgesSize; i++ ){
          edge = voronoiPointsArray[ v_id ].getEdge(i);
          int ccindex = edge.getCircumCenterIndex();
          if( ccindex >= 0 ){
                //VoronoiPoint neighbor = voronoiPointsArray[ ccindex ];
                //cout<<"neighbor:";
                //neighbor.print();
                if( voronoiPointsArray[ ccindex ].getDepth() < 0 ){
                    //cout<<"\nfrom ("<<voronoiPointsArray[ v_id ].getx()<<","<<voronoiPointsArray[ v_id ].gety()<<") --> ";
                    //cout<<"("<<neighbor.getx()<<","<<neighbor.gety()<<")\n";
                    DFS(  ccindex, d+1 , preNum_addr, postNum_addr);
                }
          }
     }
     
     voronoiPointsArray[ v_id ].setPostNum((*postNum_addr)++);
}




//26
// setDepthToVoronoiPoints: sets the depth = -1 to every VoronoiPOint of the array and then calls DFS function so tha we can give depth to all voronoi points
//3 arguments: an array of VoronoiPoint items and an integer witch is the size of the array an a VoronoiPoint item that is the minimum voronoi point
//Void : does not return anything
void setDepthToVoronoiPoints( int voronoiPointsArraySize, int minVoronoiPoint_id )
{
     int preNum=0, postNum=0;

     DFS( minVoronoiPoint_id, 0, &preNum, &postNum);    
     
      for(int i = 0; i < voronoiPointsArraySize; i++){//i set all VoronoiPoints depth = -1
             voronoiPointsArray[i].print();    
     }
     
}


/*

//27
// synartisi pou epistrefei tin alisida tou kyrtoy perivlimatos tou polygonou..pou vrisketai anamesa sta 2 shmeia 
Point * getPolygonChainArray( Point q1, Point q2, Point * polygonsConvexHullPoints, int numOfPolygonPoints ){
       
       int q1Index, q2Index;
       
       for( int i = 0; i < numOfPolygonPoints; i++ ){
            
            double x1 = polygonsConvexHullPoints[i].getx();
            double y1 = polygonsConvexHullPoints[i].gety();
            double x2 = q1.getx();
            double y2 = q1.gety();
            double x3 = q2.getx();
            double y3 = q2.gety();
            
            if(x1 == x2 && y1 == y2){
                  q1Index = i;
            }
            
            if(x1 == x3 && y1 == y3){
                  q2Index = i;
            }    
       }
       
       Point * result = NULL;
       
       if(q1Index < q2Index){
                  
                  result = (Point *) malloc( sizeof(Point) * ( (q2Index - q1Index) + 1) );
                  int j = 0;
                  
                  for(int i = q1Index; i <= q2Index; i++){
                          
                          result[j++] = polygonsConvexHullPoints[i];
                          
                  }
                  
                  for(int i = 0; i < ( (q2Index - q1Index) + 1 ); i++)
                      result[i].print();
       } else {
              
              result = (Point *) malloc( sizeof(Point) * ( (numOfPolygonPoints - q1Index) + q2Index + 1) );
              int j = 0;
              
              for(int i = q1Index; i < numOfPolygonPoints; i++){
                      
                      result[j++] = polygonsConvexHullPoints[i];
              }
              
              for(int i = 0; i <= q2Index; i++){
                      
                      result[j++] = polygonsConvexHullPoints[i];
              }
              
              for(int i = 0; i < ((numOfPolygonPoints - q1Index) + q2Index + 1); i++)
                      result[i].print();
       }
       return result;
} 


*/


//27
// synartisi pou epistrefei tin alisida tou kyrtoy perivlimatos tou polygonou..pou vrisketai anamesa sta 2 shmeia 
Point * getPolygonChainArray( int q1Index, int q2Index, Point * polygonsConvexHullPoints, int numOfPolygonPoints ){
       
       Point * result = NULL;
       
       if(q1Index < q2Index){
                  
                  result = (Point *) malloc( sizeof(Point) * ( (q2Index - q1Index) + 1) );
                  int j = 0;
                  
                  for(int i = q1Index; i <= q2Index; i++){
                          
                          result[j++] = polygonsConvexHullPoints[i];
                          
                  }
                  
                  for(int i = 0; i < ( (q2Index - q1Index) + 1 ); i++)
                      result[i].print();
       } else {
              
              result = (Point *) malloc( sizeof(Point) * ( (numOfPolygonPoints - q1Index) + q2Index + 1) );
              int j = 0;
              
              for(int i = q1Index; i < numOfPolygonPoints; i++){
                      
                      result[j++] = polygonsConvexHullPoints[i];
              }
              
              for(int i = 0; i <= q2Index; i++){
                      
                      result[j++] = polygonsConvexHullPoints[i];
              }
              
              for(int i = 0; i < ((numOfPolygonPoints - q1Index) + q2Index + 1); i++)
                      result[i].print();
       }
       return result;
} 





//28
//max: function that returns the maximum value of 2 doubles
//2 arguments: takes 2 doubles
//returns: a double witch is the maximum of the 2 doubles given
double max(double x, double y){
       if( x > y )
          return x;
       else if( x < y )
          return y;
       else
          return x;     
}




//29
//pointsDistanceFromLine: returns the distance between a point and a line
//2 arguments: a line and a point 
//returns: a double witch is the distance of a Point and a Line
double pointsDistanceFromLine( Line line, Point point ){
       
    double x,y,a,b,c,distance;
    x = point.getx();
    y = point.gety();
    
    a = line.geta();
    b = line.getb();
    c = line.getc();
    
    double temp = a*x  + b*y + c;
    distance = apolitiTimi(temp) / sqrt( a*a + b*b) ; 
    
    return distance;
       
}


//30
//getVoronoiRegion: returns an array with edges that is the edges of the voronoi region of Point with the index given
Edge * getVoronoiRegion( int pointIndex , int voronoiPointsArraySize ){
    
    int edgesSize;
    Edge * VoronoiRegionEdges;
    int VoronoiRegionEdgesSize = 0;
   
   
    cout<<"lalallalalalalallalalalall";
                  
    for(int i = 0; i < voronoiPointsArraySize; i++ ){
            edgesSize = voronoiPointsArray[i].getEdgesSize(); 
            //edges = voronoiPointsArray[i].getEdges();
            for( int j = 0; j < edgesSize; j ++ ){
                 if(  voronoiPointsArray[i].getEdge(j).getFirstPointIndex() == pointIndex || voronoiPointsArray[i].getEdge(j).getLastPointIndex() == pointIndex ){    
                         VoronoiRegionEdges[ VoronoiRegionEdgesSize ] = voronoiPointsArray[i].getEdge(j);
                         VoronoiRegionEdgesSize++;  
                 }   
            }           
    }
    
    /*
    
    Edge * VoronoiRegionEdges = (Edge *)malloc( VoronoiRegionEdgesSize * sizeof(Edge) );
    if(VoronoiRegionEdges == NULL){
        printf("Error: out of memory! \n");
        exit(1);
    }
    
    */
    
    
    for( int i = 0; i < VoronoiRegionEdgesSize; i++ ){
            
        VoronoiRegionEdges[i].print();     
    }
       
    return VoronoiRegionEdges;              
}



//31
void getVerticalLine( Line line, Point p ){
     
    double lineFactor, verticalLineFactor;
    lineFactor = line.getLineFactor();
    
    verticalLineFactor = -1/lineFactor;
    
    double a,b,c;
    
    a = 1;
    b = -verticalLineFactor;
    c = -(p.gety()) + (verticalLineFactor * p.getx() );
     
    cout<< a <<"*y + " << b << "*x + " << c << " = 0 \n" ;

}






/*
//32
Point intersectionPointOfLineAndVoronoiRegion( Line line, Edge * voronoiRegion, int voronoiregionSize, Point * setPpoints ){
      
      Point intersectionPoint;
      Line edgeLine;
      Point p1,p2;
      
      for( int i = 0; i < voronoiregionSize; i++ ){
           
           intersectionPoint = lineIntersectsLine(line, Line line2);
      }
}

*/




//32 
// AreNeighborsInVoronoiDiagram: returns true if points are neighbor or false if they are not
bool AreNeighborsInVoronoiDiagram(VoronoiPoint vp1, VoronoiPoint vp2){
     
     if( apolitiTimi(vp1.getDepth() - vp2.getDepth()) == 1 )
        return true;
     else
        return false;   
}




//33
// synartisi tou algorithmou mas
//den edxw ftiaksei polla pragmata akoma
PointsEdge AlgorithmFunction( VoronoiPoint * monopati,  int monopatiSize, PointsEdge * PolygonalChain, int PolygonalChainSize, VoronoiPoint s, VoronoiPoint cp){
           
           //1://vima 1
           VoronoiPoint u = s;
           Point uu(u.getx(), u.gety());
           VoronoiPoint v = cp;
           Point vv(v.getx(), v.getx());
           //2://vima 2
           int a = 0;
           int b = PolygonalChainSize;
           //3://vima3
           if( (AreNeighborsInVoronoiDiagram(u, v) == true) && (b = a+1) ){
               
               PointsEdge centersEdge(uu, vv);
               
               Point p1 = PolygonalChain[b].getSource();
               Point p2 = PolygonalChain[b].getTarget();
               PointsEdge segment(p1, p2);
               //4://vima 4
               return centersEdge; 
               //return segment;
           }//5:// vima 5 "end if"
           else {
                cout<<" POINTS ARE NOT NEIGHBORS ";
                exit(0);
           }
           
           
           /*
           
           
               //6: //vima 6
                VoronoiPoint z = FindPointBetween(u, v);// find point between( pws aliws tha to kanoume????????????????????????????????????)
                int j = (a + b)/2; // to kato orio
                //7://vima 7
                for(int i = 0; i < PolygonalChainSize; i++){    
                      if( i == j){   
                         PointsEdge ej(PolygonalChain[i].getSource(), PolygonalChain[i].getTarget());
                         Line lj(PolygonalChain[i].getSource(), PolygonalChain[i].getTarget());
                      }   
                }
                //8://vima 8
                if( b > a+1 ){
                    //9://vima 9
                    double r = z.getRadius(); // actina
                    double d = pointsDistanceFromLine( lj, z ); //distance Between point z and line lj
                    Line l(ej.getSource(), ej.getTarget());
                    double D = pointsDistanceFromLine( l, z );  // distance between point z and line ej
                }
                //10://vima 10
                else{
                     //11://vima 11
                    double r = z.getRadius(); // actina
                    double d = pointsDistanceFromLine( lj, z );; //distance Between point z and line lj
                    Line l(ej.getSource(), ej.getTarget());
                    double D = pointsDistanceFromLine( l, z ); // distance between point z and line ej  
                }//12://vima 12
                
                //13://vima 13
                if( r == d ){//then C(z) is a separating circle
                    double x = z.getx();
                    double y = z.gety();
                    Point p(x, y);// Point 
                    //14://vima 14
                    u = p; // u = z
                    goto 3;//return to step 3    ????????????????????????????????
                }
                //15://vima 15
                else{
                     //16://vima 16
                     if( r > D ){// then C(z) is not a separating circle
                          double x = z.getx();
                          double y = z.gety();
                          Point p(x, y);// Point 
                          //17://vima 17
                          v = p; // u = z
                          goto 3;//return to step 3    ????????????????????????????????
                     }
                     //18://vima 18
                     else{
                          
                          //19://vima 19
                          if(  ){
                               //20://vima 20
                               b = max(j, a+1);
                               
                          }
                          //21://vima 2
                          else{
                               //22://vima 22
                               a = j;S
                          }
                          //23:// vima 23
                          
                          //24://vima 24
                          goto 3;
                          
                     }//25://vima 25
                     
                }//26://vima 26
                
          */      
}










