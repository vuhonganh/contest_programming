#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <cassert>
#include <stack>
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

bool debug = true;
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
  
  //state(int r, int c);
  state(int r, int c, int t);
}; 


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
int revisited[SZ_AR][SZ_AR];

ii intvTime[SZ_AR][SZ_AR];//pair (time_min_to_come, time_max_to_leave)

int N;
char s[SZ_AR];

const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, -1, 0, 1};

void printCell(ii cell)
{
  printf("cell (%d, %d), visited %d times\n", cell.first, cell.second, revisited[cell.first][cell.second]);
}

void printTime(ii cell)
{
  printf("cell (%d, %d) has time min = %d, time max = %d\n", cell.first, cell.second, intvTime[cell.first][cell.second].first, intvTime[cell.first][cell.second].second);
}

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

  //init revisited
  REP(i, N)
    {
      REP(j,N)
    revisited[i][j] = 0;
    }

  return true;
}

//given an interval of time (from a source cell) and a destination cell, update the interval of time for this cell
//return false if can not reach
bool goToCell(const ii &srcCell, const ii &dstCell)
{

  if(revisited[dstCell.first][dstCell.second] == 6000)
    return false;
  
  //base case 1: road always closed
  if(!roadOpen[dstCell.first][dstCell.second] && roadTime[dstCell.first][dstCell.second] == 0)
    return false;

  int tMin = intvTime[srcCell.first][srcCell.second].first + 1;
  int tMax = intvTime[srcCell.first][srcCell.second].second + 1;

  //base case 2: road always opened
  if(roadOpen[dstCell.first][dstCell.second] && roadTime[dstCell.first][dstCell.second] == 0)
    {      
      intvTime[dstCell.first][dstCell.second] = ii(tMin, tMax);
      return true;
    }

    //normal case
  int tMinNew;
  int tMaxNew;
  
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
	  intvTime[dstCell.first][dstCell.second] = ii(tMinNew, tMaxNew);
     	  return true;
	}
    }
}

void print()
{
  REP(i, N)
    {
      REP(j, N)
	if(roadOpen[i][j]) printf(". ");
	else printf("* ");

      printf("\n");
    }

REP(i, N)
    {
      REP(j, N)
	printf("%d ", roadTime[i][j]);

      printf("\n");
    }
}

bool neighborCell(const ii &srcCell, int dx, int dy, ii &dstCell)
{
  int x = srcCell.first + dx;
  int y = srcCell.second + dy;
  if( (0 <= x) && (x < N) && (0 <= y) && (y < N) ) 
    {
      dstCell.first  = x;
      dstCell.second = y;
      return true;
    }
  return false;
}


void BFS()
{
  if((!roadOpen[N-1][N-1] && roadTime[N-1][N-1] == 0))
    {
      printf("NO\n");
      return;
    }
  
  //init the end point
  intvTime[N-1][N-1] = ii(-1, -1);

  stack<ii> Q;
  //init the start point
  ii srcCell(0,0);
  if(roadOpen[0][0])
    {
      if(roadTime[0][0] == 0)
	intvTime[srcCell.first][srcCell.second] = ii(0, INF);
      else
	intvTime[srcCell.first][srcCell.second] = ii(0, roadTime[0][0]);
    }
  else
    intvTime[srcCell.first][srcCell.second] = ii(0, 1);
  
  int count = 0;

  Q.push(srcCell);
  revisited[srcCell.first][srcCell.second]++;
  while(!Q.empty())
    {
      if(count++ == 10000000)
	{
	  printf("over %d times", count);
	  break;
	} 

      ii cur = Q.top(); Q.pop();
      //cout << "current cell is "; printCell(cur); printTime(cur);
      REP(i, 4)
	{
	  ii dstCell;
	  if(neighborCell(cur, dx[i], dy[i], dstCell) && goToCell(cur, dstCell))
	    {
	      //cout << "one of goable neighbor cells is "; printCell(dstCell);
	      Q.push(dstCell);
	      revisited[dstCell.first][dstCell.second]++;
	      //cout << "add this to stack "; printCell(dstCell); printTime(dstCell);
	    }
	  /*
	  if(neighborCell(cur, dx[i], dy[i], dstCell))
	    {
	      cout << "one of neighbor cells is "; printCell(dstCell);
	      if(goToCell(cur, dstCell))
		{
		  Q.push(dstCell);
		  revisited[dstCell.first][dstCell.second]--;
	   	  cout << "Can goToCell so add this neighbor cell to queue: "; printCell(dstCell); printTime(dstCell);		  
		}
	      else
	      {
		cout << "can not goToCell "; printCell(dstCell);
		}
		}*/
	}
    }
   
  if(intvTime[N-1][N-1].first == -1)
    printf("NO\n");
  else
    printf("%d\n", intvTime[N-1][N-1].first);  
}

void testQueue()
{
  ii srcCell(0,0);
  queue <ii> Q;
  REP(j, 4)
    {
      ii dstCell;
      if(neighborCell(srcCell, dx[j], dy[j], dstCell))
	{
	  printf("(%d, %d)\n", dstCell.first, dstCell.second);
	  Q.push(dstCell);
	}
    }
  
  while(!Q.empty())
    {
      ii elem = Q.front(); Q.pop();
      printf("(%d, %d)\n", elem.first, elem.second);     
    }
}


int main()
{
  if(readIn())
    {
      print();
      BFS();
    }
  
  
  while(readIn())
    {      
      printf("\n");
      BFS();
    }
  //  readIn();
  //print();

  
  
  return 0;
}




  //TO DO: NEED an Array to keep track of maximum number of revisited time of a cell




