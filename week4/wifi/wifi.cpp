//MAIN IDEA: using dichotomy method: keep a left and up bound of the value, when test a value, check if that with all the wifi access points, can we set up or not. If yes, we can reduce the value (by setting right lower), if not, we need to increase the value (by setting left higher)


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

#define FOR(i, a, b) for(int i = (a); i < (b); ++i)

#define VAR(v, x) __typeof(x) v = x

#define FOREACH(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)

#define TRACE(x) if(debug) cout << "  " << #x << " = " << x << endl;

#define INF 1000000000 
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

bool debug = false;
int checkRead;
//done shortcut
////////////////

//#define MAX_SZ 100000
//int h[MAX_SZ];
int l, r, MxDist;
int nb_wifis, nb_houses; 
vi h;

void readIn()
{
  checkRead = scanf("%d %d", &nb_wifis, &nb_houses); assert(checkRead == 2);
  
  h.assign(nb_houses, 0);
  REP(i, nb_houses)
    {
      checkRead = scanf("%d", &h[i]); assert(checkRead == 1);     
    }
  sort(h.begin(), h.end());
}

void solve()
{
  l = 0;
  r = 2 * h[nb_houses-1];
    
  while(l < r)
    {
      int nbWifisUsed = 1;
      int wifi_posi = h[0];
      if(debug) cout << "\nnew loop while here \n";
      MxDist = (l+r)/2;
      TRACE(MxDist);
      TRACE(wifi_posi);
      FOR(i, 1, nb_houses)
	{
	  if(h[i] > wifi_posi + MxDist)//exists a house with bigger dist than mxDist
	    {
	      //set up a wifi point here to maintain the properties of MxDist
	      if (debug) cout << "exists a house with bigger dist than MxDist\n";
	      TRACE(h[i]);
	      TRACE(wifi_posi);
	      TRACE(MxDist);

	      nbWifisUsed++;
	      wifi_posi = h[i];

	      if(debug) cout << "update wifi posi and nb of wifi used\n";
	      TRACE(nbWifisUsed);
	      TRACE(wifi_posi);

	    }
	}
      
      if(nbWifisUsed > nb_wifis)//if need more wifis than we have
	{
	  //increase MxDist to use fewer wifis
	  l = MxDist + 1;
	  TRACE(l);	  
	}
      else //dont use all of wifis that we have
	{
	  //decrease MxDist to optimise
	  r = MxDist;
	  TRACE(r);
	}      
    }
  
  printf("%.1lf\n", r/2.0);//before MxDist represent the distance between the two houses so need to be devided by 2 to find the distance to the wifi position

}


int main()
{
  int nbCases;
  checkRead = scanf("%d", &nbCases);
  while(nbCases--)
    {
      readIn();
      solve();
    }
  return 0;
}
