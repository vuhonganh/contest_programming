//MAIN IDEA: determine connected components, check bipartie properties, count the fewer one
//so, use BFS to find all connected components and also BFS can help to check bipartie properties (layer by layer)

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

 


int V, E; //nb of vertices and edges (i.e. intersections and streets)
int u, v; //two ends of a street

vector <vi> AdjLists;//the weight is not important here
int nbCC = 0; //nb of connected components
vi colors;

bool readInput()
{
  int check;
  check = scanf("%d", &V); if(check == EOF) return false;
  AdjLists.assign(V, vi());
  colors.assign(V, INF);
  
  check = scanf("%d", &E); assert(check == 1);
  REP(i, E)
    {
      check = scanf("%d %d", &u, &v); assert(check == 2);
      --u; --v; //idx = nb - 1
      AdjLists[u].push_back(v);
      AdjLists[v].push_back(u);
    }
  return true;
}

//using BFS to count CCs and also binary-colored each CC to check the bipartite properties
//this BFS return false if the CC contents node s is not BIpartite, return true all the other cases
bool BFS(int s)
{
  if(colors[s] != INF) return true; //already found this node before

  //esle, new CC found
  nbCC++;
  colors[s] = 2*nbCC - 2; //CC = 1, we color (0-1); CC = 2, color (2-3); etc.
  
  queue<int> Q;
  Q.push(s);

  while(!Q.empty())
    {
      int cur = Q.front(); Q.pop();
      REP(i, ( (int) AdjLists[cur].size()))
	{
	  int next = AdjLists[cur][i];
	  if(colors[next] == INF)
	    {
	      colors[next] = 4*nbCC - 3 - colors[cur];
	      Q.push(next);
	    }
	  else if(colors[next] == colors[cur])
	    return false;//NOT BIpartite
	}      
    }
  return true;
}


int main()
{
  while(readInput())
    {
      bool possible = true;
      
      REP(i, V) 
	{
	  if(!BFS(i))
	    {
	      printf("Impossible\n");
	      possible = false;
	      break;
	    }
	}
      //done BFS the whole graph
      if(!possible) continue;

      vi counts(2*nbCC, 0);
      REP(i, V)
	{
	  counts[colors[i]]++;
	}

      int res = 0;
      REP(i, nbCC)
	{
	  res += min(counts[2*i], counts[1 + 2*i]);
	}
      printf("%d\n", res);
    }
  
  return 0;
}
