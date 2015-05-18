//IDEA: just a all source single destination shortest paths
//use floyd warshall to compute all source all destination shortest paths (for its simplicity)

#include <iostream>
#include <cstdio>

using namespace std;

#define szAr 128
#define MAX_VAL 1000000000

bool debug = false;

int N; //nb of cells (i.e. vertices)
int E; //exit cell
int T; //starting value time (this will count down to 0)
int M; //nb of connections (i.e. directed edges)

int adjMatrix[szAr][szAr];

void initGraph()
{
  for(int i = 0; i < N; ++i)
    {
      for(int j = 0; j < N; ++j)
	adjMatrix[i][j] = MAX_VAL;

      adjMatrix[i][i] = 0;
    }
}

int main()
{
  int checkRead;
  //read input
  int nbCases;
  
  int a, b, t; // a ->  b takes t unit of time
  
  //read data
  checkRead =  scanf("%d", &nbCases);
  if(checkRead != 1 && debug)
    cout << "sth wrong with read input nbCases\n";
  //for each test case
  while(nbCases)
    {
      checkRead = scanf("%d %d %d %d", &N, &E, &T, &M);
      if(checkRead != 4 && debug)
	cout << "sth wrong with read input N, E, T, M\n";

      //re initialize according to the new size array
      initGraph();
      /*
      for(int i = 0; i < N; ++i)
	{
	  for(int j = 0; j < N; ++j)
	    adjMatrix[i][j] = MAX_VAL;
	  
	  adjMatrix[i][i] = 0;
	  }*/
      //read edges' weight
      for(int j = 0; j < M; ++j)
	{
	  checkRead = scanf("%d %d %d", &a, &b, &t);
	  if(checkRead != 3 && debug)
	    cout << j << " =j, sth wrong with read input a, b, t\n";
	  adjMatrix[a-1][b-1] = t;
	  if(debug)
	    {
	      cout << "connection " << j << ": " << a << b << t << endl;
	      cout << "adjMatrix[" << a+1 << "][" << b+1 << "]" << adjMatrix[a][b] << endl;
	    }
	}
  
      if(debug)
	{
	  cout << "\nafter read input\n";
	  for(int i = 0; i < N; i++)
	    for(int j = 0; j < N; j++)
	      cout << "adjMatrix[" << i+1 << "][" << j+1 << "]" << adjMatrix[i][j] << endl;	  
	}
      
      //floyd warshall
      for(int k = 0; k < N; ++k)
	for(int i = 0; i < N; ++i)
	  for(int j = 0; j < N; ++j)
	    adjMatrix[i][j] = min(adjMatrix[i][j], adjMatrix[i][k] + adjMatrix[k][j]);

      if(debug)
	{
	  cout << "\n after floyd warshall\n";
	  for(int i = 0; i < N; i++)
	    for(int j = 0; j < N; j++)
	      cout << "adjMatrix[" << i+1 << "][" << j+1 << "]" << adjMatrix[i][j] << endl;	  
	}
      
      int res = 0;
      for(int i = 0; i < N; ++i)
	if(adjMatrix[i][E-1] <= T)
	  res++;

      printf("%d\n", res);
      //done one case
      nbCases--;
      if(nbCases)
	printf("\n");
      
    }
 
  return 0;
  

}
