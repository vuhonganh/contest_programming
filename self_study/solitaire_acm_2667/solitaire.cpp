#include <iostream>

using namespace std;

#define REP(i, n) for(int i = 0; i < (n); ++i)

#define TRACE(x) if(debug) cout << #x << " = " << x << endl;

//#define TRACE(debug, x) if(debug) cout << #x << " = " << x << endl;

bool debug = false;

//done shortcut
////////////////

int nbWrongPos;

//configuration of chessboard
bool curr[8][8];// = {false};
bool dest[8][8];// = {false}; 

int xx[4];//4 pieces
int yy[4];

//move possible
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

//check state
//one configuration of x_i and y_i need 6 bits to present
//so we need 24 bits to decode all the possible state it could produce
//explain: a position x_i varie from 0 to 7 --> need 3 bits to present
//So we have: XXX000 + YYY = XXX << 3 + YYY
//keep continue, we end up with 24 bits to present all states
//can consider a value of a state is the nb of moves done so far
char states[(1 << 24)];

//find the current state of the curr configuration
int find_IdState()
{
  int res = 0;
  REP(i, 4)
    res = ( ((res << 3) + xx[i]) << 3) + yy[i];
  //  cout << res << endl;
  return res;
}

//check if x and y lies in [0,7] or not
bool inBounds(int x, int y)
{
  //return ( ( (x | y) & (~7) ) == 0);

  return ( (x >= 0) && (x < 8) &&  (y >= 0) && (y < 8) ); //other way to test
}




//return 1: readInput OK
//return 0: bad Input
//return -1: end of tests
int readInput()
{
  REP(i, 8) REP(j, 8) curr[i][j] = dest[i][j] = false;

  int checkRead;
  REP(i, 4)
    {
      int x, y;
      checkRead = scanf("%d", &x); //col <-> x, row <-> y
      
      if(checkRead == EOF)//end of tests 
	return -1;

      checkRead = scanf("%d", &y);
      --x;//idx = nb - 1
      --y;
      if(x < 0  || x > 7 || y < 0 || y > 7 || curr[x][y]) //check the correctness of input
	return 0    ;
      else
	{
	  curr[x][y] = true;
	  xx[i] = x;
	  yy[i] = y;
	}
      if(checkRead != 1 && debug)
	cout << "sth wrong in readInput\n";
    }

  REP(i, 4)
    {
      int x, y;
      checkRead = scanf("%d %d", &x, &y); 
      --x;
      --y;
      
      if(x < 0  || x > 7 || y < 0 || y > 7)//check the correctness of input
	return 0;
      else
	{
	  dest[x][y] = true;
	}
      if(checkRead != 2 && debug)
	cout << "sth wrong in readInput\n";
    }
  return 1;
}

//return nb of wrong position between current configuration and the destination config
int find_NbWrongPos()
{
  int res = 0;

  //4 pieces
  REP(i, 4) if(!dest[xx[i]][yy[i]]) ++res;
  return res;
}

int k = 0;
void search(int nbMove_done)
{
  if(nbMove_done == 8 && nbWrongPos != 0)
    return;
  
  if(nbWrongPos == 0)
    {
      throw 0;
    }
  
  if(nbWrongPos != find_NbWrongPos())
    cout << "sth wrong with nbWrongPos\n";

  int idState = find_IdState();
  //  while(k++ < 100) {cout << (int) states[idState] << endl; }
  if(states[idState] < nbMove_done)//already reached this state before 
    {
      //      cout << (int) states[idState] << " " << nbMove_done << endl;
      return;

    }

  
  states[idState] = nbMove_done;
  

  REP(i, 4) REP(j, 4)
    {
      int x = xx[i], y = yy[i];

      int x_next = x + dx[j], y_next = y + dy[j];

      if(!inBounds(x_next, y_next)) continue;

      //check whether this move make 2 pieces coincide
      if(curr[x_next][y_next])
	{
	  x_next += dx[j]; y_next += dy[j];
	  if(!inBounds(x_next, y_next) || curr[x_next][y_next]) continue;
	}
      
      int old_nbWrongPos = nbWrongPos;//keep a copy of curr nbWrongPos before take this move
      
      //go for this move
      if(dest[x][y]) ++nbWrongPos; //this piece jumped from a destination posi to another position
      //if this moved position is a destination position
      if(dest[x_next][y_next]) --nbWrongPos;
      
	if(nbWrongPos + nbMove_done <= 7)// 7 = 8 - 1, cause the nbWrongPos is already calculated for the next move (i.e. for nbMove_done + 1)
	{
	  //change configuration
	  curr[x][y] = false; curr[x_next][y_next] = true;
	  xx[i] = x_next; yy[i] = y_next;
	  
	  search(nbMove_done + 1);
	  
	  //continue here means this move is not one solution
	  xx[i] = x; yy[i] = y;
	  curr[x][y] = true; curr[x_next][y_next] = false;
	}
      //done going for this move

      nbWrongPos = old_nbWrongPos;      
    }
  
}

int main()
{
  while(true)
    {
      if(readInput() == 1)
	{
	  nbWrongPos = find_NbWrongPos();
	  //TRACE(nbWrongPos);
	  //init states
	  REP(i, (1 << 24) ) states[i] = 10; 
	  //REP(i, (1 << 24) ) if(states[i] != 9) {cout << "wrong char states array" << endl; break;} 
	  
	  try
	    {
	      search(0); //nb moves done from start is definitely 0
	      printf("NO\n");
	    }
	  catch(int)
	    {
	      printf("YES\n");
	    }     
	}
      else if(readInput() == 0) 
	printf("NO\n");
      else
	break;
    }
 
  return 0;

}
