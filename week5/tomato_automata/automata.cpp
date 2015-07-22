#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <cassert>
#include <stack>
#include <deque>
#include <set>
#include <cstring>

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

bool ri(int &intIN) {checkRead = scanf("%d", &intIN); return (checkRead != EOF);}


//done shortcut
////////////////
struct cmd
{
  string s;
  int p1;
  int p2;
  int id;
};
//char aline[88];
string aline;
int n;//nb of lines in the current tomato automata program
//int curidx;
int previdx;
vector<cmd> program;
//vector<long long> stores;
//vector<long long> buffers;

vi intBuffers;
vi intStores;
int intCurRes;
int intMaxCnt;
long long maxCnt;
long long curRes;


//flags
bool reach_die;
bool infi;
bool found_die;
void readIN2()
{
  while(getline(cin, aline))
    {
      cout << aline << endl;      
      if(cin.eof()) break;
    }
  return;
}

bool readIn()
{
  //init
  n = 0;
  maxCnt = 0;  
  curRes = 0;
  intMaxCnt = 0;
  intCurRes = 0;
  reach_die = false;
  infi = false;
  found_die = false;
  if(!program.empty()) program.clear();
  //done init
  while(getline(cin, aline))
    {
      if(aline.empty())
	{
	  //stores.assign(n, 0);
	  //buffers.assign(n, 0);
	  intStores.assign(n, 0);
	  intBuffers.assign(n, 0);
	  return true;	  
	}
      char s[8];
      int d1 = -1;
      int d2 = -1;
      sscanf(aline.c_str(), "%s", s);
      if(s[0] == 'I') s[0] = 'i';
      if(s[0] == 'i' || s[0] == 'j')
	{
	  sscanf(aline.c_str(), "%*s %d", &d1);	  
	}
      else if(s[0] == 'l')
	{
	  sscanf(aline.c_str(), "%*s %d %d", &d1, &d2);	 
	}
      else if(s[0] == 'd') found_die = true;
      d1--;//to get index	  
      cmd cur = {s, d1, d2, n++};
      program.push_back(cur);
      
      if(cin.eof()) 
	{
	  //stores.assign(n, 0);
	  //buffers.assign(n, 0);
	  intStores.assign(n, 0);
	  intBuffers.assign(n, 0);
	  return false;
	}
    }
  
    return false;
}

void print_cmd(cmd &cur)
{
  if(!debug) return;    
  printf("line %d: %s %d %d\n", cur.id, cur.s.c_str(), cur.p1, cur.p2);
}

void print_program()
{
  if(!debug) return;
  printf("print program:\n");
  REP(i, n)
    {
      print_cmd(program[i]);
    }
  printf("done printting program\n");
}
/*
void process(int curidx)
{

  if(!found_die) {infi = true; return;} //infinity
  
  if(reach_die)
    {
      curRes = max(maxCnt, curRes);
      if(debug) cout << "compare \n";
      TRACE(curRes);
      TRACE(maxCnt);
      return;
      //return maxCnt;
    }
  if(infi || curidx == n)
    {
      curRes = -1;
      return;
      //return -1;
    }
  
  cmd cur_cmd = program[curidx];
  TRACE(curidx);
  print_cmd(cur_cmd);
  switch(cur_cmd.s[0])
    {
    case 'p':
      maxCnt++;
      TRACE(maxCnt);
      previdx = curidx;
      stores[curidx] = maxCnt;
      break;
      
    case 'd':
      maxCnt++;
      TRACE(maxCnt);
      previdx = curidx;
      stores[curidx] = maxCnt;
      reach_die = true;
      break;
    case 'l':      
      TRACE(previdx);
      TRACE(cur_cmd.p1);
      TRACE(stores[previdx]);
      TRACE(stores[cur_cmd.p1]);
      maxCnt += (stores[previdx] - stores[cur_cmd.p1] + 2)*(cur_cmd.p2 - 1) + 1;//+2 bcs 1 for the begin line of loop and 1 for the line of loop itself
      TRACE(maxCnt);
      stores[curidx] = maxCnt;
      previdx = curidx;
      break;
    case 'j':
      if (curidx >= cur_cmd.p1 && stores[cur_cmd.p1] != 0) {infi = true; break;}
      previdx = curidx;
      maxCnt++;
      TRACE(maxCnt);
      stores[curidx] = maxCnt;
      curidx = cur_cmd.p1-1;
      break;

    default: //case ifgo
      if (curidx >= cur_cmd.p1 && stores[cur_cmd.p1] != 0) {infi = true; break;}
      ++maxCnt;
      int oldMaxCnt = maxCnt;
      TRACE(oldMaxCnt);
      previdx = curidx;
      stores[curidx] = maxCnt;
      process(cur_cmd.p1);
      if(debug) cout << "never go here\n";
      if(curRes == -1) return;     
      maxCnt = oldMaxCnt;
      break;
    }
  curidx++;
  process(curidx);  
}


long long process2(int curidx)
{

  if(!found_die) {infi = true; return -1;} //infinity
  
  if(reach_die)
    {
      TRACE(maxCnt);
      curRes = max(curRes, maxCnt);
      return maxCnt;
    }
  if(infi || curidx == n)
    {
      return -1;
    }
  
  cmd cur_cmd = program[curidx];
  TRACE(curidx);
  print_cmd(cur_cmd);

  switch(cur_cmd.s[0])
    {
    case 'p':       //pass
      maxCnt++;
      TRACE(maxCnt);
      previdx = curidx;
      stores[curidx] = maxCnt;
      break;
      
    case 'd':       //die
      maxCnt++;
      TRACE(maxCnt);
      previdx = curidx;
      stores[curidx] = maxCnt;
      reach_die = true;
      break;

    case 'l':      //loop
      TRACE(previdx);
      TRACE(cur_cmd.p1);
      TRACE(stores[previdx]);
      TRACE(stores[cur_cmd.p1]);
      maxCnt += (stores[previdx] - stores[cur_cmd.p1] + 2)*(cur_cmd.p2 - 1) + 1;//+2 bcs 1 for the begin line of loop and 1 for the line of loop itself
      TRACE(maxCnt);
      stores[curidx] = maxCnt;
      previdx = curidx;
      break;

    case 'j':      //jump
      if (curidx >= cur_cmd.p1 && stores[cur_cmd.p1] != 0) {infi = true; break;}
      previdx = curidx;
      maxCnt++;
      TRACE(maxCnt);
      stores[curidx] = maxCnt;
      curidx = cur_cmd.p1-1;
      break;

    default: //case ifgo
      if (curidx >= cur_cmd.p1 && stores[cur_cmd.p1] != 0) {infi = true; break;}
      ++maxCnt;
      int oldMaxCnt = maxCnt;
      TRACE(oldMaxCnt);
      previdx = curidx;
      stores[curidx] = maxCnt;
      
      buffers.assign(stores.begin(), stores.end());
      long long goforthis = process2(cur_cmd.p1);
      
      if(debug) cout << "go here\n";
      if(goforthis == -1) return -1; //infinity
      else curRes = max(goforthis, curRes);
      //set back the value of maxCnt here
      maxCnt = oldMaxCnt;
      stores.assign(buffers.begin(), buffers.end());
      break;
    }
  //curidx++;
  return process2(curidx + 1);  
  }
*/

int process3(int curidx)
{

  if(!found_die) {infi = true; return -1;} //infinity
  
  if(reach_die)
    {
      TRACE(intMaxCnt);
      intCurRes = max(intCurRes, intMaxCnt);
      return intMaxCnt;
    }
  if(infi || curidx >= n)
    {
      return -1;
    }

  if(intMaxCnt > INF) {infi = true; return -1;}
  
  cmd cur_cmd = program[curidx];
  TRACE(curidx);
  print_cmd(cur_cmd);

  switch(cur_cmd.s[0])
    {
    case 'p':       //pass
      intMaxCnt++;
      TRACE(intMaxCnt);
      previdx = curidx;
      intStores[curidx] = intMaxCnt;
      break;
      
    case 'd':       //die
      intMaxCnt++;
      TRACE(intMaxCnt);
      previdx = curidx;
      intStores[curidx] = intMaxCnt;
      reach_die = true;
      break;

    case 'l':      //loop
      TRACE(previdx);
      TRACE(cur_cmd.p1);
      TRACE(intStores[previdx]);
      TRACE(intStores[cur_cmd.p1]);
      intMaxCnt += (intStores[previdx] - intStores[cur_cmd.p1] + 2)*(cur_cmd.p2 - 1) + 1;//+2 bcs 1 for the begin line of loop and 1 for the line of loop itself
      TRACE(intMaxCnt);
      intStores[curidx] = intMaxCnt;
      previdx = curidx;
      break;

    case 'j':      //jump
      if (curidx >= cur_cmd.p1 && intStores[cur_cmd.p1] != 0) {infi = true; break;}
      previdx = curidx;
      intMaxCnt++;
      TRACE(intMaxCnt);
      intStores[curidx] = intMaxCnt;
      curidx = cur_cmd.p1-1;
      break;

    default: //case ifgo
      //if (curidx >= cur_cmd.p1 && intStores[cur_cmd.p1] != 0) {infi = true; break;}
      intMaxCnt++;
      int oldMaxCnt = intMaxCnt;
      TRACE(oldMaxCnt);
      previdx = curidx;
      intStores[curidx] = intMaxCnt;
      
      intBuffers.assign(intStores.begin(), intStores.end());
      int goforthis = process3(cur_cmd.p1);
      
      if(debug) cout << "go here\n";
      if(goforthis == -1) return -1; //infinity
      else intCurRes = max(goforthis, intCurRes);
      //set back the value of intMaxCnt here
      intMaxCnt = oldMaxCnt;
      intStores.assign(intBuffers.begin(), intBuffers.end());
      break;
    }
  //curidx++;
  return process3(curidx + 1);  
}


/*
void solve()
{
  //process(0);
  long long res = process2(0);
  if(curRes == -1 || res == -1) printf("infinity\n");
  else
    {
      printf("%lld\n", max(res,curRes));
    }
}
*/

void solve3()
{
  
  int res = process3(0);
  if(infi) printf("infinity\n");
  else
    {
      printf("%d\n", max(res,intCurRes));
    }
}

int main()
{
  while(readIn())
    {
      solve3();
    }
  solve3();
  
  return 0;
}
