//MAIN idea: sort edges and use union find (while joining 2 ends point of edge (from low to high cost)

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <cassert>
#include <stack>
#include <deque>
#include <set>


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
typedef vector<vi> vvi;
bool debug = true;
int checkRead;
//done shortcut
////////////////

struct edge
{
  int x;
  int y;
  int d;
  
  bool operator<(const edge &o) const
  {
    return (d < o.d);    
  }
};

int nbV, nbE;
vvi paths;//array of vertices: each vertices contain the index of path 
vector <edge> edges;
int nbPaths;
int si, ti, di;

//for union find
vi id;
vi sz;

//for result
vi res;
bool readIn()
{
  checkRead = scanf("%d", &nbV); if(checkRead == EOF) return false;
  checkRead = scanf("%d", &nbE); assert(checkRead == 1);
 
  edge e;
  edges.assign(nbE, e);
  
  //union find init part
  id.assign(nbV, 0);
  REP(i, nbV) id[i] = i;
  sz.assign(nbV, 1);
  //done union find init part  

  REP(i, nbE)
    {
      checkRead = scanf("%d %d %d", &si, &ti, &di); assert(checkRead == 3);      
      si--; ti--;
      
      edge ei = {si, ti, di};
      edges[i] = ei;
    }
 
  checkRead = scanf("%d", &nbPaths); assert(checkRead == 1);
  res.assign(nbPaths, 0);
  vi a;
  paths.assign(nbV, a);
    
  REP(i, nbPaths)
    {
      checkRead = scanf("%d %d", &si, &ti); assert(checkRead == 2);
      si--; ti--;

      paths[si].push_back(i);
      paths[ti].push_back(i);
    }
  sort(edges.begin(), edges.end());

  return true;
}

void printEdges()
{
  if(!debug) return;


  printf("start print edges\n");
  REP(i, nbE)
    {
      edge e = edges[i];
      printf("(%d, %d) with cost %d\n", e.x+1, e.y+1, e.d);
      
    }
  printf("done print edges\n\n");
}

void printPaths()
{
  if(!debug) return;
  
  printf("start print paths\n");
  REP(i, nbV)
    {
      vi a = paths[i];
      if(a.size() == 0)
	printf("vertice %d is neither start or end point of any path", i+1);
      else
	{
	  printf("vertice %d is either start or end point of these path: ", i+1);
	  REP(j, (int) a.size())
	    {
	      printf("%d ", a[j]);
	    }
	}
      printf("\n");
    }
  printf("done print paths\n\n");
}

int find(int x)
{
  while (id[x] != x)
    {
      x = id[x];
    }
  return x;
}

void unite(int x, int y)
{
  int repX = find(x);
  int repY = find(y);

  if(repX == repY) return;
  
  if(sz[repX] > sz[repY])
    {
      sz[repX] += sz[repY];
      id[repY] = repX;
    }
  else
    {
      sz[repY] += sz[repX];
      id[repX] = repY;
    }
}

void uniteYtoX(int repX, int repY)
{
  sz[repX] += sz[repY];
  id[repY] = repX;
}
void uniteXtoY(int repX, int repY)
{
  sz[repY] += sz[repX];
  id[repX] = repY;
}

void solve()
{
  REP(i, nbE)
    {
      int repX = find(edges[i].x);
      int repY = find(edges[i].y);
      int danger = edges[i].d;
      
      if(repX == repY) continue;
      
      if(sz[repX] > sz[repY])
	{
	  FOREACH(j, paths[repY])//for each id path in set Y
	    {
	      vector<int>::iterator it = find(paths[repX].begin(), paths[repX].end(), *j);
	      if(it != paths[repX].end())//if found the same path id in set X
		{
		  //update the answer for this path and delete it from set X
		  res[*j] = danger;
		  paths[repX].erase(it);
		}
	      else//if not, need to add this path id to X and update Y to X later
		{
		  paths[repX].push_back(*j);
		  
		}
	    }
	  uniteYtoX(repX, repY);
	}
      else
	{
	  FOREACH(j, paths[repX])//for each id path in set X
	    {
	      vector<int>::iterator it = find(paths[repY].begin(), paths[repY].end(), *j);//search it in set Y
	      if(it != paths[repY].end())//if found the same path id in set Y
		{
		  //update the answer for this path and delete it from set X
		  res[*j] = danger;
		  paths[repY].erase(it);
		}
	      else
		{
		  paths[repY].push_back(*j);
		}
	    }	  	  
	  uniteXtoY(repX, repY);
	}      
    }  
}

void printRes()
{
  REP(i, nbPaths)
    {
      printf("%d\n", res[i]);
    }
}


int main()
{
  if(readIn())
    {
      solve();
      printRes();
    }
  
  while(readIn())
    {
      //printEdges();
      //printPaths();
      printf("\n");
      solve();
      printRes();
    }
  return 0;
}
