//XARALAMPOS DALLAS A.M. 801
// PROGRAMMA GIA TON ALGORITHMO TWN ALUPIS, BARBA KAI LANGERMAN

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <fstream>

#include "classes.h"
#include "functions.h"

#define vertex 1          // if an edge has edgeType = 1 then this is an inside edge o voronoi  diagram ( it has 2 limit points )
#define infinity 0        // if an edge has edgeType = 0 then it is an infimity edge of voronoi diagram ( goes from one point to infinity)


//========================================================================================================================================================================================================


using namespace std;



//========================================================================================================================================================================================================




//  ---------MAIN---------










int main(int argc, char *argv[]){
 
    
   
    
   printf("\n\nSet P Data :\n\n");
   FileInputData setPData = readFileInputData(argv[1]); //read the data from the file SetOfPoints.txt and take the cordinates of the points       
   int numOfPoints = setPData.getNumOfPoints();
   Point * setPpoints = setPData.getPoints(); // store the points into an array eith points
      
   printf("\n\n\nPolygon Data :\n\n");
   FileInputData polygonData = readFileInputData(argv[2]); // read the data from the file PolygonPoints.txt and take the points that are the vertexes of the polygon
   int numOfPolygonPoints = polygonData.getNumOfPoints();
   Point * setOfPolygonPoints = polygonData.getPoints(); // store the points to an array with the points of the polygon
   
   printf("\n\n\n");
   
   string pathToQhullBin = "C:/cygwin/home/programs/ptyxiaki/qhull-2012.1/bin/";
   string pathToCygwinHome = "C:/cygwin/home/programs/ptyxiaki/";
   
   int sysCommandCodeQconvex;
     
   string qconvexPoints = pathToQhullBin + "qconvex Fx < " + pathToCygwinHome + argv[1] + " > " + pathToCygwinHome + "PointsConvexHull.txt";
   
   sysCommandCodeQconvex = system( qconvexPoints.c_str() );
   printf("%d\n", sysCommandCodeQconvex);
   
   string qconvexPolygon = pathToQhullBin + "qconvex Fx < " + pathToQhullBin + argv[2] + " > " + pathToCygwinHome + "PolygonConvexHull.txt";
   
   sysCommandCodeQconvex = system( qconvexPolygon.c_str() );
   printf("%d\n", sysCommandCodeQconvex);
   
   int sysCommandCodeQvoronoi;
   string qdelaunay = pathToQhullBin + "qdelaunay Qu o < " + pathToCygwinHome + argv[1] + " > " + pathToCygwinHome + "fDT_off.txt";
   
   sysCommandCodeQvoronoi = system( qdelaunay.c_str() );
   printf("%d\n", sysCommandCodeQvoronoi);
   
   
   
   
   Point * setPconvexHullPoints = readConvexHullData("PointsConvexHull.txt", setPpoints); //diavazw tis korifes tou kyrtou perivlimatos twn shmeiwn apo to arxeio PointsConvexHull.txt pou dimiourgise i entoli qconvex kai epistrefw pinaka me tis koryfes tou kyrtou perivlimatos twn shmeiwn
   int setPConvexHullPointsArraySize;
   setPConvexHullPointsArraySize = getConvexHullPointsArraySize("PointsConvexHull.txt"); 
   printf("\n\n\n");
   Point * polygonsConvexHullPoints = readConvexHullData("PolygonConvexHull.txt", setOfPolygonPoints);  // diavazw tis korifes tou polygonou apo to arxeio PolygonConvexHull.txt  kai epistrefw pinaka me shmeia ta opoia einai oi koryfes tou kyrtou perivlimatos tou polygwnou                                                
   printf("\n\n\n");
   
   
   
   printf("\nPINAKAS AKMWN TOY KYRTOY PERIVLIMATOS TOY SYNOLOY P\n");
   printf("-----------------------------------------------------\n\n");
   
   PointsEdge  * setPedgesArray; // array with the edges of the convex hull of set P
   setPedgesArray = getSetPedgesArray(setPconvexHullPoints, setPConvexHullPointsArraySize);
   
   for(int i = 0; i < setPConvexHullPointsArraySize; i++ ){
          setPedgesArray[i].print(); 
   }
   
   printf("\n\n\n");
   
   printf("\nPINAKAS AKMWN TOY KYRTOY PERIVLIMATOS TOY POLYGONOY Q\n");
   printf("-----------------------------------------------------\n\n");
   
   PointsEdge  * polygonEdgesArray;   // array with the edges of the convex hull of the Polygon Q
   polygonEdgesArray = getPolygonEdgesArray(polygonsConvexHullPoints, numOfPolygonPoints);
   
   for(int i = 0; i < numOfPolygonPoints; i++ ){
          polygonEdgesArray[i].print(); 
   }
       
   cout<<"\n\n\n";
   
   printf("\nPINAKAS PERIKENTRWN\n");
   printf("---------------------\n\n");
   
   int circumCentersArraySize = getCircumCentersArraySize("fDT_off.txt"); 
   Point * circumCentersArray; // array with the circum centers
   circumCentersArray = (Point *) malloc ( circumCentersArraySize * sizeof(Point) );
   if(circumCentersArray == NULL){
        printf("Error: out of memory! \n");
        exit(1);
   }
   
   
   int triadsArraySize = getTriadsArraySize("fDT_off.txt");
   Triad * triadsArray = readOffFileInputData("fDT_off.txt", circumCentersArray); // array with the triads
   
    
   for(int i = 0; i < circumCentersArraySize; i++){//print array with circumCenters
           circumCentersArray[i].print();
           printf("\n");
   }
   
   
   printf("\n\n\n");
   
   printf("\nPINAKAS TRIADWN\n");
   printf("-----------------\n\n");
   
   for(int i = 0; i < triadsArraySize; i++){ //print array with triads       
         triadsArray[i].print();  
   }
   
   printf("\n\n\n");
   
   printf("\nTAKSINOMIMENOS PINAKAS TRIADWN\n");
   printf("--------------------------------\n\n");
   
   Triad * sortedTriadsArray;// sorted array with triads
   sortedTriadsArray = (Triad *) malloc ( triadsArraySize * sizeof(Triad) );
   if(sortedTriadsArray == NULL){
        printf("Error: out of memory! \n");
        exit(1);
   }
   
   sortedTriadsArray = mergeSort(triadsArray, triadsArraySize); //we use the funcion mergeSort to sort the array with the triads
   
   for(int i = 0; i < triadsArraySize; i++){
           sortedTriadsArray[i].print();
   }

   printf("\n\n\n");
 
   printf("\nPINAKAS SHMEIWN VORONOI\n");
   printf("--------------------------\n\n");
   
   int voronoiPointsArraySize = getVoronoiPointsArraySize("fDT_off.txt");
   voronoiPointsArray = getVoronoiPointsArray(voronoiPointsArraySize, sortedTriadsArray, triadsArraySize, circumCentersArray, circumCentersArraySize, setPpoints, numOfPoints);// Array with VoronoiPoints
   
   for(int i=0; i<voronoiPointsArraySize; i++){  
         voronoiPointsArray[i].print(); 
   }       
  
   printf("\n\n\n");
   
   printf("PERIKENTRO ME MIKROTERI AKTINA PERIGEGRAMENOU KYKLOU \n");
   printf("---------------------------------------------------- \n");
   
   VoronoiPoint minVoronoiPoint = getMinimumRadiusVoronoiPoint(voronoiPointsArray, voronoiPointsArraySize);// Voronoi Point with the smallest radius
   minVoronoiPoint.print();
   
   printf("\n\n\n");
   
   
   printf("TO KENTRO TOY MIKROTEROY KYKLOY DIAXWRISMOU \n");
   printf("------------------------------------------- \n");
   
   // Cp(minimumSeparatingCircleCenter) : center of the minimum circle enclosing set P
   Point minimumSeparatingCircleCenter = findMinimumSeparatingCircleCenter(minVoronoiPoint, sortedTriadsArray, triadsArraySize, setPpoints, numOfPoints);
   minimumSeparatingCircleCenter.print();
   
   cout<<"\n\n\n";
  
  printf("KANOUME DFS STO PINNAKA ME TA VORONOI POINTS KAI VAZOUME SE KATHENA APO AFTA VATHOS\n");
  printf("------------------------------------------------------------------------------------ \n");
  
  setDepthToVoronoiPoints( voronoiPointsArraySize, 0 );
  
  cout<<"\n\n\n";
  
  printf("OI DYO ESWTERIKES EFAPTOMENES METAKSI TOU POLYGONOU Q KAI TOU SYNOLOY P EINAI\n");
  printf("------------------------------------------------------------------------------ \n");
  
  int i1, i2;//ta shmeia tou perivlhmatos tou polygonoy pou temnoun oi 2 eswterikes efaptomenes
  int j1,j2;//ta shmeia tou kyrtou perivlimatos twn shmeiwn pou temnoun oi eswterikes efaptomenes
  
  i1 = getInternalTangentLine( setPconvexHullPoints, setPConvexHullPointsArraySize, polygonsConvexHullPoints, numOfPolygonPoints, 1 );
  cout<<"i1 = "<<i1<<"\n";
  i2 = getInternalTangentLine( setPconvexHullPoints, setPConvexHullPointsArraySize, polygonsConvexHullPoints, numOfPolygonPoints, -1 );
  cout<<"i2 = "<<i2<<"\n";
  
  j1 = getInternalTangentLine( polygonsConvexHullPoints, numOfPolygonPoints, setPconvexHullPoints, setPConvexHullPointsArraySize, 1 );
  cout<<"j1 = "<<j1<<"\n";
  j2 = getInternalTangentLine( polygonsConvexHullPoints, numOfPolygonPoints, setPconvexHullPoints, setPConvexHullPointsArraySize, -1 );
  cout<<"j2 = "<<j2<<"\n";
  
  cout<<"\n\n\n";
  
  printf("VRISMOUME THN ALYSIDA QQ' TOY KYRTOY PERIVLIMATOS TOY POLYGONOU\n");
  printf("---------------------------------------------------------------- \n");
    
  cout<<"\n\n"; 
  Point * polygonChainArray = getPolygonChainArray( i1, i2, polygonsConvexHullPoints, numOfPolygonPoints );
  
  cout<<"\n\n\n";
  
  printf("EFAPTOMENA SHMEIA TOU KYRTOY PERIVLIMATOS ME TIS ESWTERIKES EFAPTOMENES\n");
  printf("------------------------------------------------------------------------ \n");
  
  cout<<"shmeia kyrtou perivlhmatos shmeiwn\n";
  Point p1 = setPconvexHullPoints[j1];
  p1.print();
  Point p2 = setPconvexHullPoints[j2];
  p2.print();
  
  cout<<"\n\n";
  
  cout<<"shmeia kyrtou perivlhmatos polygonou\n";
  Point p3 = polygonsConvexHullPoints[i1];
  p3.print();
  Point p4 = polygonsConvexHullPoints[i2];
  p4.print();
  
  cout<<"\n\n\n";
  
  printf("EKSISWSEIS ESWTERIKWN EFAPTOMENWN\n");
  printf("---------------------------------- \n");
  
  Line internalTangent1(p1, p3);
  internalTangent1.print();
  internalTangent1.print2();
  Line internalTangent2(p2, p4);
  internalTangent2.print();
  internalTangent2.print2();
  
  cout<<"\n\n\n";
  
  //printf("KATHETES TWN ESWTERIKWN EFAPTOMENWN\n");
  //printf("------------------------------------ \n");
  
  
  //getVerticalLine( internalTangent1, p1 );
  
  
  VoronoiPoint s(-1.2, 0.8, 5.0);
  VoronoiPoint y = voronoiPointsArray[1];
  VoronoiPoint x = voronoiPointsArray[4];
  VoronoiPoint cp = voronoiPointsArray[0];
  
  printf("MONOPATI PS STO DIAGRAMA VORONOI\n");
  printf("-------------------------------- \n");
  
  VoronoiPoint monopati[3] = {y,x,cp};// pinakas me shmeia tou monopatiou ps
  for(int i = 0; i < 3; i++){
          monopati[i].print();
  }
  
  cout<<"\n\n\n";
  
  printf("ALYSIDA QQ' TOY POLYGONOY Q\n");
  printf("--------------------------- \n");
  
  Point q1(5.0, 10.0); 
  Point q2(5.0, 5.0);
  Point q3(7.0, 3.0);
  
  Point alysida[3] = {q1, q2, q3};//pinakas me shmeia ths alysidas qq' toy polygonoy
  
  PointsEdge edge3(q1, q2);
  PointsEdge edge4(q2, q3);
  
  PointsEdge alysidaAkmwn[2] = {edge3, edge4};
  for(int j = 0; j < 2; j++){
          alysidaAkmwn[j].print();
          cout<<"\n";
  }
  
  cout<<"\n\n\n";
  
  printf("AKMH POY PERIEXEI TO KENTRO C*\n");
  printf("------------------------------ \n");
  
  PointsEdge akmiMeToKentro = AlgorithmFunction(monopati, 2, alysidaAkmwn, 2, cp, y);
  akmiMeToKentro.print();
  
  cout<<"\n\n\n";
  
  
}
