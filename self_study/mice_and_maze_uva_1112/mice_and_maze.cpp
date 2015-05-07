#include <iostream>
#include <cstdio>

using namespace std;

#define szAr 128
#define MAX_VAL 1000000000


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
  //read input
  int nbCases;
  
  int a, b, t; // a ->  b takes t unit of time
  
  //read data
  scanf("%d", &nbCases);
  
  //for each test case
  while(nbCases)
    {
      scanf("%d %d %d %d", &N, &E, &T, &M);
      
      //re initialize according to the new size array
      //initGraph();

      for(int i = 0; i < N; ++i)
	{
	  for(int j = 0; j < N; ++j)
	    adjMatrix[i][j] = MAX_VAL;
	  
	  adjMatrix[i][i] = 0;
	}
      //read edges' weight
      for(int j = 0; j < M; ++j)
	{
	  scanf("%d %d %d", &a, &b, &t);
	  adjMatrix[a-1][b-1] = t;
	  //cout << "connection " << j << ": " << a << b << t << endl;
	  // cout << "adjMatrix[" << a+1 << "][" << b+1 << "]" << adjMatrix[a][b] << endl;
	}
  
      //cout << "\nafter read input\n";
      /*for(int i = 0; i < N; i++)
	for(int j = 0; j < N; j++)
	cout << "adjMatrix[" << i+1 << "][" << j+1 << "]" << adjMatrix[i][j] << endl;*/
 
      //floyd warshall
      for(int k = 0; k < N; ++k)
	for(int i = 0; i < N; ++i)
	  for(int j = 0; j < N; ++j)
	    adjMatrix[i][j] = min(adjMatrix[i][j], adjMatrix[i][k] + adjMatrix[k][j]);

      /*cout << "\n after floyd warshall\n";
      for(int i = 0; i < N; i++)
	for(int j = 0; j < N; j++)
	cout << "adjMatrix[" << i+1 << "][" << j+1 << "]" << adjMatrix[i][j] << endl;*/
      
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
