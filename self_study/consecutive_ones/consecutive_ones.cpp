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

void swapTask(int colI, int colJ)
{
  REP(i, nbRows)
    swap(mat[i][colI], mat[i][colJ]);

  swap(order[colI], order[colJ]);  
}

bool setCol(int current_col)
{
  if(current_col == nbCols) 
    return true;
  
  FOR(col, current_col, nbCols)
    {
      FOR(row, 0, nbRows)//check each row too see whether this could not be a solution
	{
	  if(mat[row][current_col - 1] && !mat[row][col]) //... 1 0 0 ...
	    FOR(after, current_col, nbCols)
	      {
		if(mat[row][after]) // ... 1 0 0 ... 0 1 ...
		  goto chooseNextCol;
	      }
	} 
      
      //feasible, go for this setCol
      swapTask(col, current_col);

      if(setCol(current_col + 1))
	 return true;

      //go here i.e. this set above is not the solution
      // --> swap back
      swapTask(col, current_col);

    chooseNextCol: {}
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

 
