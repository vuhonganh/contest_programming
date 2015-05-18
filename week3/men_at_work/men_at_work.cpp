#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <cassert>

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

bool debug = false;
int checkRead;
//done shortcut
////////////////
/*
class state
{
  
public:
  int row;
  int col;
  int time;
  
  state(int r, int c);
  state(int r, int c, int t);
}; 


  state::state(int r, int c)
  {
    row = r;
    col = c;
    time = -1;
  }

state::state(int r, int c, int t)
  {
    row = r;
    col = c;
    time = t;
  }
*/

//cach 2: moi state xac dinh boi mot pair ii (x, y), giu mot Ar 2D ii de update thoi gian (tMin, tMax). Nhet pair vao Queue va lam binh thuong

#define SZ_AR 50

bool roadOpen[SZ_AR][SZ_AR];
int roadTime[SZ_AR][SZ_AR];

ii intvTime[SZ_AR][SZ_AR];//pair (time_min_to_come, time_max_to_leave)

int N;
char s[SZ_AR];

bool readIn()
{
  checkRead = scanf("%d", &N); if(checkRead == EOF) return false;
  
  REP(i, N)
    {
      checkRead = scanf("%s", s);
      REP(j, N)
	{
	  roadOpen[i][j] = (s[j] == '.')? true : false;	  
	}      
    }
  
  REP(i, N)
    {
      REP(j, N)
	checkRead = scanf("%1d", &roadTime[i][j]); 
    }
  
  return true;
}

//given an interval of time (from a source cell) and a destination cell, update the interval of time for this cell
//return false if can not reach
bool goToCell(ii srcCell, ii dstCell)
{
  if(!roadOpen[dstCell.first][dstCell.second] && roadTime[dstCell.first][dstCell.second] == 0)
    return false;
  
  int tMinNew;
  int tMaxNew;

  int tMin = intvTime[srcCell.first][srcCell.second].first + 1;
  int tMax = intvTime[srcCell.first][srcCell.second].second + 1;
  
  int k = tMin/roadTime[dstCell.first][dstCell.second];
  
  if( (k%2 == 0 && roadOpen[dstCell.first][dstCell.second]) || (k%2 == 1 && !roadOpen[dstCell.first][dstCell.second]) )
    {
      tMinNew = tMin;
      tMaxNew = min( (k+1)*roadTime[dstCell.first][dstCell.second], tMax );
      
      intvTime[dstCell.first][dstCell.second] = ii(tMinNew, tMaxNew);
      return true;      
    }
  else
    {
      if( (k+1)*roadTime[dstCell.first][dstCell.second] >= tMax)
	return false;
      else
	{
	  tMinNew = (k+1)*roadTime[dstCell.first][dstCell.second];
	  tMaxNew = min( (k+2)*roadTime[dstCell.first][dstCell.second], tMax);
	  return true;
	}
    }
}

void print()
{
  REP(i, N)
    {
      REP(j, N)
	printf("%d ", roadOpen[i][j]);

      printf("\n");
    }

REP(i, N)
    {
      REP(j, N)
	printf("%d ", roadTime[i][j]);

      printf("\n");
    }
}

int main()
{
  /*
  ii startPoint(0, 0);
  queue<ii> Q;
  Q.push(startPoint);
  */
  readIn();
  print();
  return 0;
}





  //TO DO: init tmin, tmax correctly




