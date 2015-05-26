#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <cassert>

using namespace std;

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
int checkRead;
//done shortcut
////////////////

#define SZ_AR 400

bool mat[SZ_AR][SZ_AR];
int order[SZ_AR];
int nbRows, nbCols;
char aRow[SZ_AR];

//swap two collumns indexed colI and colJ
void swapTask(int colI, int colJ)
{
  REP(i, nbRows)
    swap(mat[i][colI], mat[i][colJ]);

  swap(order[colI], order[colJ]);  
}

//return true if we can fill the collumn indexed idx_col with collumn col
//assumming that all collumns which are previous idx_col meet the condition consecutive ones 
bool fillAble(int col, int idx_col)
{
  //consider each row
  for(int r = 0; r < nbRows; ++r)
    {
      //if the previous collumns contain 0, any col can be filled to the idx_col
      //if previous collumns contain 1
      if(mat[r][idx_col-1])
	{
	  //if col contains 1 it's ok but if it contains 0, than all other elements on the row r in from idx_col -> last have to be 0)
	  if(mat[r][col] == false)
	    {
	      for(int others = idx_col; others < nbCols; ++others)
		if(mat[r][others]) return false;
	    }
	}
    }
  return true;
}

bool setCol(int idx_colToFill)
{
  if(idx_colToFill == nbCols) 
    return true;
  
  for(int col = idx_colToFill; col < nbCols; ++col)
    {
      
      if(fillAble(col, idx_colToFill))
	{
	  //go for this setCol
	  swapTask(col, idx_colToFill);
	  
	  if(setCol(idx_colToFill + 1))
	    return true;
	  
	  //go here i.e. this set above is not the solution
	  // --> swap back
	  swapTask(col, idx_colToFill);
	}
    }
  return false;
}

void compute()
{
  checkRead = scanf("%d", &nbRows); assert(checkRead == 1);
  checkRead = scanf("%d", &nbCols); assert(checkRead == 1);
  
  REP(i, nbRows)
    {
      checkRead = scanf("%s", aRow); 
      REP(j, nbCols)
	{
	  mat[i][j] = (aRow[j] == '1');
	}
    }
  //init order
  REP(i, nbCols) order[i] = i;

  //do stuff
  setCol(1);
  REP(i, nbCols) printf("%d\n", order[i]);
}

int main()
{
  int nbCases;
  checkRead = scanf("%d", &nbCases);
  while(nbCases--)
    {      
      compute();     
      if(nbCases) printf("\n");
    }
  return 0;
}

 
