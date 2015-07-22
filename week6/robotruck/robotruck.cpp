//MAIN IDEA: using dynamic programming, consider dp[i] is the minimum cost to finish i-eme delivery (from beginning). When calculate dp[j] (j>i), test all the possibility for that i and j are two consecutive times leave from office, move (i->...>j) then return to office (from j) and keep the minimum value while respecting the constraint of maximum capacity. 
	 
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

bool debug = false;
//bool debug = true;
int checkRead;


int ri() {int res; checkRead = scanf("%d", &res); assert(checkRead == 1); return res;}

bool ri(int &intIN) {checkRead = scanf("%d", &intIN); return (checkRead != EOF);}


//done shortcut
////////////////
int C; //max capacity
int N; //number of packages

vi xx;
vi yy;

vi dists;
vi weights;
vi dp;

int w;

void readIn()
{
  C = ri();
  N = ri();
  xx.assign(N+1, 0);
  yy.assign(N+1, 0);
  dists.assign(N+1, 0);
  weights.assign(N+1, 0);
  dp.assign(N+1, INT_MAX);
  dp[0] = 0;
  for(int i = 1; i < N+1; ++i)
    {
      xx[i] = ri();
      yy[i] = ri();
      w = ri();
      weights[i] = weights[i-1] + w;
      dists[i] = dists[i-1] + abs(xx[i] - xx[i-1]) + abs(yy[i] - yy[i-1]);
    }
}

void solve()
{
  for(int j = 1; j < N+1; ++j)
    {
      for(int i = j; i > 0; --i)
	{
	  if(weights[j] - weights[i-1] > C) break;
	  //we test all the possibility for that i and j are two consecutive times return to office and keep the minimum value
	  int distIJ = abs(xx[i]) + abs(yy[i]) + dists[j] - dists[i] + abs(xx[j]) + abs(yy[j]);
	  if(debug) cout << "leave from office at i = "; TRACE(i);
	  if(debug) cout << "go back to office at j = "; TRACE(j);
	  TRACE(dp[j]);
	  TRACE(dp[i-1]);
	  TRACE(distIJ);
	  if(dp[j] > dp[i-1] + distIJ)
	    {
	      if(debug) cout << "plus petite, mets dp[j] a nouvelle valeur: for j = " << j << ", ";
	      dp[j] = dp[i-1] + distIJ;
	      TRACE(dp[j]);
	    }
	  //dp[j] = min(dp[j], dp[i-1] + distIJ);
	}
    }
  printf("%d\n", dp[N]);
}

int main()
{
  int nbTests = ri();
  while(nbTests--)
    {
      readIn();
      solve();
      if(nbTests) printf("\n");
    }
  return 0;
}
