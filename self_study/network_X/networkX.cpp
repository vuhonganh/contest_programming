//MAIN IDEA: using BFS 

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <queue>

using namespace std;

#define REP(i, n) for(int i = 0; i < (n); ++i)

#define VAR(v, x) __typeof(x) v = x

#define FOREACH(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)

#define TRACE(x) if(debug) cout << #x << " = " << x << endl;

typedef pair<int, int > ii;

typedef vector<int> vi;

typedef vector<ii> vii;

#define INF 1000000000

bool debug = false;
bool checkRead = true;

//done shortcut
////////////////

int V; //nb of vertices
int src, dst; //source and destination
int u, v;
vector<vii> AdjLists; //adjacent list (each index represents a vertex, the list contened at this index is all the neighbour (idx, weight) of this vertex) 
vi dists;
void readInput()//for each test case
{
  //init the AdjLists
  //if(!AdjLists.empty()) AdjLists.clear();does not need because assign already removed the content of AdjLists
  int check;
  check = scanf("%d", &V); assert(check == 1);
  
  AdjLists.assign(V, vii());
  dists.assign(V, INF);

  int nbNeighBor;
  REP(i, V)
    {
      check = scanf("%d %d", &u, &nbNeighBor); assert(check == 2);
      REP(j, nbNeighBor)
	{
	  check = scanf("%d", &v); assert(check == 1);
	  AdjLists[u].push_back(ii(v, 1)); //add pair(idx, weight)
	}	
    }
  check = scanf("%d %d", &src, &dst); assert(check == 2);
}

void BFS()
{
  dists[src] = 0;
  queue<int> Q;
  Q.push(src);
  
  while(!Q.empty())
    {
      int cur = Q.front(); Q.pop();
      REP(i, ( (int) (AdjLists[cur].size())))
	{
	  ii nextV = AdjLists[cur][i];
	  if(dists[nextV.first] == INF) //V is not discovered yet
	    {
	      dists[nextV.first] = dists[cur] + 1;
	      Q.push(nextV.first);
	    }
	}
    }

  //done BFS
  
  printf("%d %d %d\n", src, dst, dists[dst]-1);
}

int main()
{
  int check;
  int nbCases;
  check = scanf("%d", &nbCases); assert(check == 1);
  while(nbCases--)
    {
      readInput();
      BFS();
      if(nbCases)
	printf("\n");
    } 
  return 0;
}

