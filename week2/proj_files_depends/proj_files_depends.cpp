//KEY: topological sorting (implements algo in wikipedia: http://en.wikipedia.org/wiki/Topological_sorting )
//just takes into account of using a priority queue to have the order asked

#include <iostream>
#include <cstdio>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<int> vi;


#define NB_NODES 128
#define INF 1000000000

#define print(x) if(debug) cout << #x << " = " << x << endl;


/*
  NOTE:  NODE_INDEX = NODE_NUMBER - 1
*/

//int order[NB_NODES] = {0};
bool adjMat[NB_NODES][NB_NODES] = {false};
//adjMat[i][j] = exist edge from i to j

//stack<int> Q;

priority_queue<int, vector<int>, greater<int> >pQ;

int edges_come[NB_NODES] = {0};//? should to use it?

int N; //nb of tasks (i.e. nodes)
int M; //nb of rules

int checkRead;//control scanf's output
bool debug = false;

void readInput()
{
  checkRead = scanf("%d %d", &N, &M);
  if(checkRead != 2 && debug)
    cout << "sth wrong with read N M\n";

  int T0;
  int k;
  for(int i = 0; i < M; ++i)
    {
      checkRead = scanf("%d %d", &T0, &k);
      if((checkRead != 2) && debug)
	cout << "sth wrong at read T0, k\n";
      for(int j = 0; j < k; ++j)
	{
	  int idx_src;
	  checkRead = scanf("%d", &idx_src);
	  if((checkRead != 1) && debug)
	    cout << "sth wrong at read idx_src\n";
	  adjMat[idx_src - 1][T0 - 1] = true;
	}
    }
  //done reading data for one case
  if(debug)
    cout << "done reading data for one case\n";
  
  //put into the queue what does not have comming edges
  for(int i = 0; i < N; ++i)
    {
      for(int j = 0; j < N; ++j)
	{
	  edges_come[i] += (adjMat[j][i])? 1 : 0;
	}
      if(edges_come[i] == 0)
	pQ.push(i);
    }
  if(debug)
    cout << "put into queues\n";
  
}

void topologicalSort()
{
  //int maxOrder = 0;
  while(!pQ.empty())
    {
      int idx_src = pQ.top();
      pQ.pop();
      
      //for all edges come from src
      for(int i = 0; i < N; ++i)
	{
	  if(adjMat[idx_src][i])
	    {
	      //	      order[i] = order[idx_src] + 1;
	      //maxOrder = max(order[i], maxOrder);
	      adjMat[idx_src][i] = false;//remove edge
	      edges_come[i] -= 1;
	      if(edges_come[i] == 0)
		pQ.push(i);
	    }
	}
      if(pQ.empty())
	cout << idx_src+1;
      else
	cout << idx_src+1 << " ";
    }

  cout << endl;
  if(debug)
    cout << "done topological sort\n";
  //print(maxOrder);
  //print result
}

/*
void printResult()
{
  vi arrayVect[NB_NODES+1];
  for(int i = 0; i < N; ++i)
    {
      //print(order[i]);
      arrayVect[order[i]].push_back(i);
    }

  for(int i = 0; i < maxOrder+1; ++i)
    {
      if(!arrayVect[i].empty())
	{
	  sort(arrayVect[i].begin(), arrayVect[i].end());
	  for(size_t j = 0; j < arrayVect[i].size(); ++j)
	    {
	      cout << arrayVect[i][j]+1 << " ";
	    }
  	  
	}
    }
  cout << "\n";
  if(debug)
    cout << "printed out result\n";
    }*/

int main()
{
  int nbCases;
  checkRead = scanf("%d", &nbCases);

  //cout << nbCases << endl;
  if(checkRead != 1 && debug)
    cout << "sth wrong with nbCase\n";

  for(int i = 0; i < nbCases; ++i)
    {
      readInput();
      topologicalSort();
      if(i != nbCases - 1)
	printf("\n");
    }
}
