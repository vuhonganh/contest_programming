//MAIN IDEA: simple problem after sorting. Just try to make pair the minimum and the maximum, if can not, the maximum has to be in one bin itself. Need to pay attention at the end while index_low >= index_high.

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

//bool debug = false;
bool debug = true;
int checkRead;


int ri() {int res; checkRead = scanf("%d", &res); assert(checkRead == 1); return res;}

bool ri(int &intIN) {checkRead = scanf("%d", &intIN); return (checkRead != EOF);}


//done shortcut
////////////////
 
int n;
int l;
vi objLens;

void readIn()
{
  n = ri();
  l = ri();
  objLens.assign(n, 0);
  REP(i, n)
    {
      objLens[i] = ri();
    }
  sort(objLens.begin(), objLens.end());
}

void printObjs()
{
  if(!debug) return;

  printf("print objects'lengths in sorted order:\n");
  REP(i, n)
    {
      printf("%d\n", objLens[i]);
    }
  printf("\n");
}

void solve()
{
  int cnt = 0;
  int iLow = 0;
  int iHigh = n-1;
  while(iLow < iHigh)
    {
      if(objLens[iLow] + objLens[iHigh] > l)
	{
	  cnt++;
	  iHigh--;
	}
      else
	{
	  iHigh--;
	  iLow++;
	  cnt++;
	}
    }
  if(iLow == iHigh) cnt++;//dont forget this
  printf("%d\n", cnt);
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
