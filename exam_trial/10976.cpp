#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <stdio.h>
#include <set>

using namespace std;

bool debug = false;
//bool debug = true;

#define trace(x) if(debug) cout << #x << " = " << x << endl;

bool ri(int &res)
{    
    int cr = scanf("%d", &res);
    if(cr == 1) return true;
    else return false;
}

int main()
{
    int k;
    int x, y;

    while(ri(k))
    {

        int cnt = 0;
        for(y = k+1; y < 2*k+1; ++y)
        {
            if( (k * y)%(y - k) == 0 )
            {
                x = (k*y)/(y-k);
                cnt++;
            }
        }
        printf("%d\n", cnt);
        for(y = k+1; y < 2*k+1; ++y)
        {
            if( (k * y)%(y - k) == 0 )
            {
                x = (k*y)/(y-k);
                printf("1/%d = 1/%d + 1/%d\n", k, x, y);
            }
        }
    }

    return 0;
}
