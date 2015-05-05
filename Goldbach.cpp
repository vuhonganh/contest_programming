#include <iostream>
#include <algorithm>
#include <set>
#include <cmath>

#define n 1000001

using namespace std;

bool sieve[n] = {false, false};
set<int> primes;

void findPrimes()
{
  //init
  for(int i = 2; i < n; i++)
    sieve[i] = true;

  //do sieve
  for(int i = 2; i < sqrt(n)+1; i++)
    {
      if(sieve[i])
	{
	  int j = i*i;
	  while(j < n)
	    {
	      sieve[j] = false;
	      j += i; 
	    }
	}
    }
  for(int i = 2; i < n; i++)
    {
      if(sieve[i])
	primes.insert(i);
    }
}

int main()
{
  findPrimes();
  while(1)
    {
      int input;
      cin >> input;
      if(input == 0)
	break;
      for(set<int>::iterator i = primes.begin(); i != primes.end(); ++i)
	{
	  int cur = *i;
	  int compo = input - cur;
	  if(sieve[compo])
	    {
	      cout << input << " = " << cur << " + " << compo << endl;
	      break;
	    }
	}      
    }
  return 0;
}
  
  

