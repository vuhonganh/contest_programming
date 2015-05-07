#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>

//#define checkhere if(dbg) cout << "return false here" << endl

//const double EPS = 0.00000001;
const double EPS = 0;
using namespace std;

bool dbg = false;

//add -w/2 and length + w/2 to avoid test case

bool test(vector<double> sortedPos, int sizeAr, double w, double length)
{
  //sortedPos content real positive number as indicated in the problem (start from 0.0)
  
  //check if smallest content 0.0
  
  int cur = 0;
  if(sortedPos[cur] - w/2.0 > EPS)
    {
      //    checkhere;
      if(dbg) cout << "return false here" << endl;
      return false;

    }
     while(cur < sizeAr-1)
    {
      if(sortedPos[cur+1] - sortedPos[cur] > w + EPS)
	{
	  if(dbg) cout << "return false here" << endl;
	  return false;
	}
      cur++; 
    }
  if(sortedPos[cur] + w/2.0 < length - EPS)
    {
      if(dbg) cout << "return false here" << endl;
      return false;   
    }
  return true;  
}

void runProgram()
{
  //  cout << "start game" << endl;
  while(1)
    {
      //  ifstream Input("input.txt");
      int nx, ny;
      double w;
      cin >> nx;
      cin >> ny;
      cin >> w;
      
      if(nx == 0 && ny == 0)
	break;
      else
	{
	  //cout << "go into program" << endl;
	  vector<double> posX, posY;
	  for(int i = 0; i < nx; i++)
	    {
	      double posi;
	      cin >> posi;
	      posX.push_back(posi);
	    }	

	  for(int i = 0; i < ny; i++)
	    {
	      double posi;
	      cin >> posi;
	      posY.push_back(posi);
	    }	
	  sort(posX.begin(), posX.end());
	  sort(posY.begin(), posY.end());
	  double lengthX = 75.0;
	  double lengthY = 100.0;
	  if( test(posX, nx, w, lengthX) && test(posY, ny, w, lengthY) )
	    cout << "YES" << endl;
	  else
	    cout << "NO" << endl;
	}    
    }

}

int main()
{
  /*
  cout << "start game";
  
  int nx, ny;
  double w;
  cin >> nx;
  cin >> ny;
  cin >> w;
  
  cout << nx << " " << ny << " " << w << " " << endl;
  */

  runProgram();
  return 0;
}
