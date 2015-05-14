#include <iostream>
#include <algorithm>
using namespace std;

#define REP(i, n) for(int i = 0; i < (n); ++i)

#define VAR(v, x) __typeof(x) v = x

#define FOREACH(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)

#define TRACE(x) if(debug) cout << #x << " = " << x << endl;

bool debug = false;
int checkRead;
//done shortcut
////////////////

 
const int MAX_SZ = 1024;

double bl[MAX_SZ]; //base level
double h[MAX_SZ]; //height
double w[MAX_SZ]; //width
double d[MAX_SZ]; //depth


void find_level(int n, double V) //n = nb of cistern
{
  
  double sumV = 0.0;
  
  double l = 0.0;//we use binary convergent to find the level of water
  double r = 0.0;//l and r represent this interval [l,r] where level of water is in this interval
  double mid;
  //First of all: check if overflow or not
  REP(i, n)
    {
      sumV += h[i]* w[i] * d[i];
      TRACE(sumV);
      r = max(r, bl[i] + h[i]);
    }
  
  TRACE(n);
  TRACE(V);
  TRACE(sumV);
  
  if(sumV < V)
    {
      printf("OVERFLOW\n");
      return;
    }
  
  
  REP(convert, 100)
    {
      sumV = 0.0;
      mid = (l + r)/2.0;
      REP(i, n)
	{
	  if(mid < bl[i]) continue;//consider only the lower cistern first
	  sumV += w[i] * d[i] * min(h[i], mid - bl[i]);
	}
      
      if(sumV < V)
	l = mid;
      else
	r = mid;
    }
  
  printf("%.2f\n", mid);
}

int main()
{

  int testCase, n;
  double V;
  bool readInput = true;
  checkRead = scanf("%d", &testCase);
  readInput = (checkRead == 1);

  while(testCase--)
    {
      checkRead = scanf("%d", &n);
      readInput = (checkRead == 1);
      REP(i, n)
	{
	  checkRead = scanf("%lf %lf %lf %lf", &bl[i], &h[i], &w[i], &d[i]);
	  readInput = (checkRead == 4);
	  TRACE(bl[i]);
	  TRACE(h[i]);
	  TRACE(w[i]);
	  TRACE(d[i]);
	}
      checkRead = scanf("%lf", &V);
      
      find_level(n, V);

      
      if(testCase)
	printf("\n");
    }
  
  if(!readInput && debug)
    cout << "sth wrong with reading input data\n";

  return 0;
}
