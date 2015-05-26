//MAIN IDEA: can solve by BFS by considering 3-dimensions state (x,y,t) but this seems slow
//I choose another way clearer to solve: at each time t maintain a 2D which represents reachable cells at time t. Keep counting the nb of new cells discovered along the way. After one period, if no new cell discovered -> no solution 


#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <cassert>
#include <stack>
#include <time.h>
#include <stdlib.h>

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
//DONE SHORTCUT///
//////////////////


#define SZ_AR 50

bool roadOpen[SZ_AR][SZ_AR];
int roadTime[SZ_AR][SZ_AR];
bool reachAtT[SZ_AR][SZ_AR];//true if this cell is reachable at current time T, false if not
bool discovered[SZ_AR][SZ_AR];
int nbDiscovered;
queue <ii> cellsChangesStates;

int N;
char s[SZ_AR];

const int dx[5] = {-1, 0, 1, 0, 0};
const int dy[5] = {0, -1, 0, 1, 0};

bool inBounds(int x, int y)
{

    return ( (0 <= x) && (x < N) && (0 <= y) && (y < N) );
}

int atTimeT(int t) //return nb of new cell discovered at time = t
{
    //at t = 0, the man is already at cell (0, 0) so we consider t >= 1
    if(t == 0)
        cout << "t = 0 considered at function atTimeT" << endl;

    int oldNbDiscovered = nbDiscovered;
    //update roadOpen at this time t
    REP(i, N)
    {
        REP(j, N)
        {
            if(roadTime[i][j] != 0) //if it can change
            {
                if(t % roadTime[i][j] == 0)//change period
                    roadOpen[i][j] = !roadOpen[i][j];

            }
        }
    }

    //make sure the queue empty before doing task
    if(!cellsChangesStates.empty()) printf("error at queue cells changes states"); //this queue needs to be empty after each loop

    //find cells that we can reach at t (suppose t >= 1), t = 0 we always start at (0,0)
    REP(i, N)
    {
        REP(j, N)
        {
            if(reachAtT[i][j])//in fact this reachAtT is for time = t-1, we are updating for time = t
            {
                REP(k, 5)
                {
                    //consider cell (x,y)
                    int x = i + dx[k];
                    int y = j + dy[k];

                    if(inBounds(x, y) && roadOpen[x][y])
                    {
                        cellsChangesStates.push( ii(x, y) );
                        //check if discovered a new cell or not
                        if(discovered[x][y] == false)
                        {
                            discovered[x][y] = true;
                            nbDiscovered++;
                        }
                    }

                }
            }
        }
    }

    //update reachAtT for time = t
    //clean previous state time = t-1
    REP(i, N) REP(j, N) reachAtT[i][j] = false;
    //update this state time = t
    while(!cellsChangesStates.empty())
    {
        ii cur = cellsChangesStates.front(); cellsChangesStates.pop();
        reachAtT[cur.first][cur.second] = true;
    }
    return nbDiscovered - oldNbDiscovered;
}

bool existStates()
{
    REP(i, N) REP(j, N) if(reachAtT[i][j]) return true;
    return false;
}

const int maxNoNew = 5040; //period of configuration 
//2520 = least common multiple of 1..9, double cause the state changes from open - close - open ...

void compute()
{
    int t = 1;
    int countNoNew = 0;
    while(true)
    {
        int newDiscover = atTimeT(t);

        if(newDiscover == 0)
            countNoNew++;
        else
            countNoNew = 0;

        if(!existStates())
        {
            printf("NO\n");
            return;
        }

        if(countNoNew == maxNoNew)
        {
            printf("NO\n");
            return;
        }

        if(reachAtT[N-1][N-1])
        {
            printf("%d\n", t);
            return;
        }

        t++;
    }
}

//read input
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

    //init reachAtT
    REP(i, N)
    {
        REP(j,N)
                reachAtT[i][j] = false;
    }
    reachAtT[0][0]   = true;  //at time 0
    discovered[0][0] = true;  //at time 0
    nbDiscovered = 1; //cell (0,0)
    return true;
}

void doTask()
{
    if(readIn())
      {
        compute();
      }

    while(readIn())
      {
        printf("\n");
        compute();
      }

}

void genRandIn(int t)
{
    srand (time(NULL) + t);

    int size = rand()%50 + 1;

    printf("%d\n", size);
    REP(i, size)
    {
        REP(j, size)
        {
            int c = rand()%2;
            if(c) printf(".");
            else printf("*");
        }
        printf("\n");
    }

    REP(i, size)
    {
        REP(j, size)
        {
            int num = rand()%10;
            printf("%d", num);
        }
        printf("\n");
    }


}

int main()
{
  doTask();
  /*
  REP(i,5)
    {
      genRandIn(i*1024);
      printf("\n");
      }*/
    return 0;
}


