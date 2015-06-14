//main idea: enumeration: while considering a new position to put a ballon, need to check the radius maximum it can have by satisfait constraint to the box and not overlap other ballons 

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <cassert>
#include <stack>
#include <deque>
#include <set>
#include <stdio.h>
#include <string.h>
#include <math.h>
using namespace std;

#define REP(i, n) for(int i = 0; i < (n); ++i)

#define FOR(i, a, b) for(int i = (a), i < (b); ++i)

#define VAR(v, x) __typeof(x) v = x

#define FOREACH(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)

#define TRACE(x) if(debug) cout << #x << " = " << x << endl;

#define INF 1000000000 
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

bool debug = false;
int checkRead;
//done shortcut
////////////////

#define MAX_SZ 6

struct Point
{
  int x, y, z;
  double r;
};
 
Point Points[MAX_SZ];
Point corner0, corner1;
int nbPoints;
int x, y, z;
bool inUsed[MAX_SZ];

double maxVol;
double volBox;


double min(double a, double b)
{
	if(a < b) return a;
	else return b;
}

bool inBox(int x, int y, int z)
{
  return ( min(corner0.x, corner1.x) < x && x < max(corner0.x, corner1.x) 
	   && min(corner0.y, corner1.y) < y && y < max(corner0.y, corner1.y) 
	   && min(corner0.z, corner1.z) < z && z < max(corner0.z, corner1.z));         
}


//find the maximum radius that ballon put at idxPoint could have 
double findRadius(int idxPoint)
{
  Point cur = Points[idxPoint];
  double rad = abs(cur.x - corner0.x);
  rad = min(rad, abs(cur.x - corner1.x));
  rad = min(rad, abs(cur.y - corner0.y));
  rad = min(rad, abs(cur.y - corner1.y));
  rad = min(rad, abs(cur.z - corner0.z));
  rad = min(rad, abs(cur.z - corner1.z));
  //done find max radius possible to the box plane
  
  REP(i, nbPoints)
    {
      if(!inUsed[i] || i == idxPoint) continue;
      //distance from cur to i
      double di = sqrt( (double) (cur.x - Points[i].x) * (cur.x - Points[i].x) + (cur.y - Points[i].y) * (cur.y - Points[i].y) + (cur.z - Points[i].z) * (cur.z - Points[i].z) );
      rad = min(rad, di - Points[i].r);//two ballons can not overlap each other
    }
  return rad;
}

void run(int nbDone, double curVol)
{
  if(nbDone == nbPoints)
    {
      if(curVol > maxVol) maxVol = curVol;
      return;
    }
  
  REP(i, nbPoints)
    {
      if(!inUsed[i])
	{
	  inUsed[i] = true;
	  double rad = findRadius(i);
	  Points[i].r = rad;
	  if(rad > 0)//this point is feasible to set a balloon
	    run(nbDone + 1, curVol + (4.0 / 3.0 * M_PI * rad * rad * rad));
	  else
	    run(nbDone + 1, curVol);
	  //go here i.e. it's done for this point (complete one enumeration) -> reset for the next enumeration
	  inUsed[i] = false;
	}
    }
  
}

bool readIn()
{
  checkRead = scanf("%d", &nbPoints); assert(checkRead == 1);
  if(nbPoints == 0)
    return false;

  checkRead = scanf("%d %d %d", &x, &y, &z); assert(checkRead == 3);
  corner0 = {x, y, z, 0};
  checkRead = scanf("%d %d %d", &x, &y, &z); assert(checkRead == 3);
  corner1 = {x, y, z, 0};
  
  int nbPointsInBox = 0;
  REP(i, nbPoints)
    {
      checkRead = scanf("%d %d %d", &x, &y, &z); assert(checkRead == 3);
      if(inBox(x, y, z))
	{
	  Points[i] = {x, y, z, 0};
	  ++nbPointsInBox;
	}
    }
  nbPoints = nbPointsInBox;
  memset(inUsed, false, sizeof(inUsed));

  //init
  maxVol = 0;
  volBox = abs((double)(corner0.x-corner1.x)*(corner0.y - corner1.y)*(corner0.z - corner1.z));
  return true;
}

void printPoint(Point p)
{
  printf("(%d, %d, %d, %f)\n", p.x, p.y, p.z, p.r); 
}

void printInput()
{
  REP(i, nbPoints)
    {
      printPoint(Points[i]);
    }
}

int main()
{
  int iBox = 1;
  while(readIn())
    {      
      //printInput();      
      run(0, 0.0);
      printf("Box %d: %d\n\n", iBox, (int) round(volBox - maxVol));
      iBox++; 
    }
  return 0;
}
