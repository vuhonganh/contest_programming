#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <cassert>
#include <set>
using namespace std;

#define REP(i, n) for(int i = 0; i < (n); ++i)

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

int nbLines, nbCols;
int matIn[SZ_AR][SZ_AR];//will read like this mat[idx_Col][idx_Row]
int matOut[SZ_AR][SZ_AR];
int idxLastOne[SZ_AR];//for each row, return the idx of last 1 added
//int idxLastOnePrevious[SZ_AR];
int idNextCol;

set <int> Q;
vi results;
void readIn()
{
  checkRead = scanf("%d", &nbLines); assert(checkRead == 1);
  checkRead = scanf("%d", &nbCols); assert(checkRead == 1);
  
  REP(i, nbLines)
    {
      REP(j, nbCols)
	{
	  checkRead = scanf("%1d", &matIn[j][i]);
	}
    }
 
  //INIT 
  idNextCol = 0;
  //prepare the set
  if(!Q.empty()) Q.clear();  
  REP(i, nbCols-1) Q.insert(i+1);//col 0 is fixed

  //init the idx of Last One
  REP(i, nbLines) idxLastOne[i] = -1;
  REP(i, nbCols) REP(j, nbLines) matOut[i][j] = -1;

  if(!results.empty()) results.clear();
  REP(i, nbCols) results.push_back(0);
}


bool setCol(int idIn, int idOut)//set the collumn idIn to the collumn idOut
{
 
  REP(i, nbLines)
    {
      if(idxLastOne[i] != -1)
	if(matIn[idIn][i] == 1)
	  if(idxLastOne[i] < idOut - 1)
	    return false;
    }
 
  //set row
  REP(i, nbLines)
    {
      matOut[idOut][i] = matIn[idIn][i];
      //update idx of Last One
      //idxLastOnePrevious[i] = idxLastOne[i];
      if(matIn[idIn][i] == 1)
	idxLastOne[i] = idOut;
    }
  return true;  
}

void printMatIn()
{
  REP(i, nbLines)
    {
      REP(j, nbCols)
	printf("%d ", matIn[j][i]);
      printf("\n");
    }
  printf("\n");  
}


void printMatOut()
{
  REP(i, nbLines)
    {
      REP(j, nbCols)
	printf("%d ", matOut[j][i]);
      printf("\n");
    }
  printf("\n");  
}


void search()
{
  //  if(Q.empty()) throw 0;
  
  FOREACH(i, Q)
    {
      //get a collumn
      int idColIn = *i;

      //int old_idNextCol = idNextCol;
      vi oldLastOne(nbLines, -1);
      REP(i, nbLines) oldLastOne[i] = idxLastOne[i];
      if(setCol(idColIn, idNextCol)) //go for this call
	{
	  results[idNextCol] = idColIn;
	  if(debug)
	    {
	      printf("set col %d of input to col %d in output\n", idColIn, idNextCol);
	      printMatOut();
	    }
	  if(Q.size() == 1) throw 0;
	  Q.erase(i);
	  idNextCol++;

	  search();
	  
	  //go here i.e.
	  Q.insert(idColIn);
	  idNextCol--;
	  
	  REP(i, nbLines) idxLastOne[i] = oldLastOne[i];
	}
      else if(debug) printf("can not set col %d of input to col %d in output\n", idColIn, idNextCol);
    }
  
}


void compute()
{
  setCol(0, 0);
  idNextCol++;
  try
    {
      search();
    }
  catch(int)
    {
      //printf("result is\n");
      //printMatOut();
      REP(i, nbCols) printf("%d\n", results[i]);
    }
}

int main()
{
  int nbCases;
  checkRead = scanf("%d", &nbCases);
  while(nbCases--)
    {
      
      readIn();
      //printMatIn();
      compute();     
      if(nbCases) printf("\n");
    }
  
  //  test set  
  /*
  Q.insert(3);
  Q.insert(4);
  Q.insert(5);
  Q.insert(9);
  
  FOREACH(i,Q) cout << *i << endl;

  //Q.erase(3);

  FOREACH(i,Q) Q.erase(i);

  FOREACH(i,Q) cout << *i << endl;*/
  
  return 0;  
}


