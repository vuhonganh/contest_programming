#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <cassert>
#include <stack>
#include <deque>
#include <set>
#include "string.h"

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

//char * rs() {char * res; checkRead = scanf("%s", res); return res;}

//done shortcut
////////////////
 

int lastMet[26];
char people[501];
//char *people;
int n, k;
int main()
{
  int nbCases;
  int curCase = 1;
  nbCases = ri();
  while(nbCases--)
    {

      n = ri(); k = ri();
      REP(i, 26)
	{
	  lastMet[i] = -1024;
	}
      TRACE(n);
      TRACE(k);      
      checkRead = scanf("%s", people);
      int count = 0;
      REP(i, n)
	{

	  TRACE((lastMet[people[i] - 'A']));
	  if(i - lastMet[people[i]-'A'] < k+1)
	    {
	      count++;
	      TRACE(i);
	      TRACE(people[i]);
	      TRACE(lastMet[people[i]-'A']);
	    }
	   
	  lastMet[people[i]-'A'] = i;
	}
      printf("Case %d: %d\n", curCase++, count);
    }
  
  return 0;
}
