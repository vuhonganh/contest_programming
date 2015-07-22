//MAIN IDEA: first we need to sort the value of subcompanies, then, base on greedy, the optimised move is to eat itself subcompany (the two biggest) in order to create a bigger subcompany and if this move can help to either avoid being eaten (next turn) or eat the two biggest of the enemy (next 2 turn). if should not eat itself, then consider then it can eat enemy this turn.  

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <cassert>
#include <stack>
#include <deque>
#include <set>


using namespace std;

#define INT_MAX 2147483647
#define INT_MIN -2147483647
#define pi acos(-1.0)


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
//bool debug = true;
int checkRead;


int ri() {int res; checkRead = scanf("%d", &res); assert(checkRead == 1); return res;}

long long rll(){long long res; checkRead = scanf("%lld", &res); assert(checkRead == 1); return res;}

bool ri(int &intIN) {checkRead = scanf("%d", &intIN); return (checkRead != EOF);}


//done shortcut
////////////////
int N, M;
vector<long long int> TakeIn, BuyLim; 

bool readIn()
{
  if(!ri(N)) return false;
  M = ri();
  TakeIn.assign(N, 0);
  BuyLim.assign(M, 0);
  REP(i, N)
    {
      TakeIn[i] = rll();
    }
  REP(i, M)
    {
      BuyLim[i] = rll();
    } 
  return true;
}

void move(vector<long long> &inTurn, int &idInTurn, vector<long long> &enemy, int &idEnemy)
{
  //if value market of inTurn is bigger than its concurence than eat it
  TRACE(idInTurn); TRACE(inTurn[idInTurn]);
  TRACE(idEnemy); TRACE(enemy[idEnemy]);
  
  //it may to eat itself to become bigger, optimisation for the next move by greedy eating (eat the second biggest to become as big as possible) 
  if( (idInTurn > 0 && inTurn[idInTurn] < enemy[idEnemy]) || ( idInTurn > 0 && idEnemy > 0 
	  && inTurn[idInTurn] + inTurn[idInTurn-1] > enemy[idEnemy] + enemy[idEnemy-1])    ) 
    {
      inTurn[idInTurn - 1] += inTurn[idInTurn];
      idInTurn--;
      if(debug) cout << "merge two biggest subcompanies\n";
    }
  //if can not eat itself, than check if it can eat its enemy
  else if(inTurn[idInTurn] > enemy[idEnemy])
    {
      idEnemy--;
      if(debug) cout << "eat enemy\n";
    }
} 
int caseNB = 1;
void solve()
{
  //first we sort the value market of each company
  sort(TakeIn.begin(), TakeIn.end());
  sort(BuyLim.begin(), BuyLim.end());
  REP(i, N) TRACE(TakeIn[i]); 
  REP(i, M) TRACE(BuyLim[i]); 
  int i = N-1;
  int j = M-1;
  
  int turn = 0;
  while(i > -1 && j > -1)
    {
      if(turn % 2 == 0)
	move(TakeIn, i, BuyLim, j);
      else
	move(BuyLim, j, TakeIn, i);
      turn++;
    }
  if(j == -1)
    printf("Case %d: Takeover Incorporated\n", caseNB);
  else
    printf("Case %d: Buyout Limited\n", caseNB);
  caseNB++;
}

int main()
{
  while(readIn())
    {
      solve();
    }
  return 0;
}
