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

#define INT_MAX 2147483647
#define INT_MIN -2147483647
#define pi acos(-1.0)


#define REP(i, n) for(int i = 0; i < (n); ++i)

#define FOR(i, a, b) for(int i = (a); i < (b); ++i)

#define VAR(v, x) __typeof(x) v = x

#define FOREACH(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)

#define TRACE(x) if(debug) cout << #x << " = " << x << endl;

#define INF 1000000000 
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

//bool debug = true;
bool debug = false;
int checkRead;


int ri() {int res; checkRead = scanf("%d", &res); assert(checkRead == 1); return res;}

bool ri(int &intIN) {checkRead = scanf("%d", &intIN); return (checkRead != EOF);}


//done shortcut
////////////////
 
int a, b;
int caseNB = 0;
int nbPages;
#define MAXSZ 128

int graph[MAXSZ][MAXSZ];
bool exist[MAXSZ];
void initGraph(int a, int b)
{
  REP(i, MAXSZ)
    {
      REP(j, MAXSZ)
	{
	  graph[i][j] = INF;
	  
	}
      exist[i] = false;
      graph[i][i] = 0;
    }
  graph[a][b] = 1;
  exist[a] = true;
  exist[b] = true;
}

bool readIn()
{
  a = ri();
  b = ri();
  if(a == 0 && b == 0)
    return false;
  
  initGraph(a-1,b-1);
  bool endInput = false;
  nbPages = 0;
  while(!endInput)
    {
      a = ri();
      b = ri();
      nbPages = max(nbPages, a);
      nbPages = max(nbPages, b);
      if(a != 0 && b != 0)
	{
	  graph[a-1][b-1] = 1;
	  exist[a-1] = true;
	  exist[b-1] = true;
	  if(debug) printf("%d -> %d = 1\n", a, b);
	}  
      else endInput = true; 
    }
  caseNB++;
  return true;
}

void floyWarshal()
{
  REP(k, nbPages)
    {
      REP(i, nbPages)
	{
	  REP(j, nbPages)
	    {
	      if(exist[i] && exist[j]) graph[i][j] = min( graph[i][j], graph[i][k] + graph[k][j]);
	    }
	}
    }
}

void printGraph()
{
  if(!debug) return;
  REP(i, nbPages)
    {
      REP(j, nbPages)
	{
	  printf("edge(%d, %d) = %d\n", i+1, j+1, graph[i][j]);
	}
    }
  printf("\n");
}

void solve()
{
  printGraph();
  if(debug) printf("do FLOYWARSHAL\n");
  floyWarshal();
  if(debug) printf("done FLOYW.\n");
  printGraph();
  unsigned int sum = 0;
  int nbLinks = 0;
  REP(i, nbPages)
    {
      REP(j, nbPages)
	{
	  if(i != j && exist[i] && exist[j])
	    {
	      TRACE(sum);
	      TRACE(graph[i][j]);
	      sum += graph[i][j];
	      nbLinks++;
	    }	  
	}
    }
  double res = 1.0 * sum / nbLinks;
  printf("Case %d: average length between pages = %.3f clicks\n", caseNB, res);
}

int main()
{
  while(readIn())
    {
      solve();      
    }
  return 0;
}
