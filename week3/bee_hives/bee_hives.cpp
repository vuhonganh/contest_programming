//MAIN IDEA: the problem is equivalent to: given an undirected graph, find the shortest length cycle
//so, can use BFS to solve (each time find a node already visited equivalent to find a cycle in undirected graph) -> compute the length of cycle each time

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <cassert>

using namespace std;

#define REP(i, n) for(int i = 0; i < (n); ++i)

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

int V, E; //nb vertices and edges
int u, v;

vector <vi> AdjLists;
vi dists;  //to do BFS and to compute cycle length
vi parents;//to check cycle

void readIn()
{
  checkRead = scanf("%d %d", &V, &E); assert(checkRead == 2);  
  AdjLists.assign(V, vi());
 
  REP(i, E)
    {
      checkRead = scanf("%d %d", &u, &v); assert(checkRead == 2);
      AdjLists[u].push_back(v);
      AdjLists[v].push_back(u);      
    }
} 

void BFS(int s, int &res)
{
  dists.assign(V, INF);
  parents.assign(V, -1);
  
  dists[s]   = 0; 
  //parents[s] = -1;

  queue<int> Q;
  Q.push(s);
  
  while(!Q.empty())
    {
      int cur = Q.front(); Q.pop();
      REP(i, ( (int) AdjLists[cur].size()))
	{
	  int next = AdjLists[cur][i];
	  if(next == parents[cur]) continue;
	  
	  if(dists[next] == INF)
	    {
	      parents[next] = cur;
	      dists[next] = dists[cur] + 1;
	      Q.push(next);
	    }
	  else //this node already visited, form here a cycle
	    {
	      res = min(res, dists[cur] + dists[next] + 1);
	      //return; //return here might cause errors because of the arbitrary order of pushing into queue
	    }
	} 
    }
}

int main()
{
  int nbCases;
  checkRead = scanf("%d", &nbCases); assert(checkRead == 1);

  REP(i, nbCases)
    {
      printf("Case %d: ", i+1);
      readIn();
      int res = INF;
      REP(j,V)
	{
	  BFS(j, res);
	}
      if(res == INF)
	printf("impossible\n");
      else
	printf("%d\n", res);
    }
  return 0;
}
