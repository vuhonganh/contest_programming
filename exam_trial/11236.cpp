#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <stdio.h>
#include <set>
#include <vector>
using namespace std;

//bool debug = false;
bool debug = true;

#define trace(x) if(debug) cout << #x << " = " << x << endl;

bool ri(int &res)
{    
    int cr = scanf("%d", &res);
    if(cr == 1) return true;
    else return false;
}

bool rc(char &res)
{
    int cr = scanf("%c", &res);
    if(cr == 1) return true;
    else return false;
}


int main()
{
    cout << "fuck\n";
    int a,b,c,d;
    for(a = 1; a < 501; a++)
    {
        cout << "fuck1\n";
        for(b = a; a + 3*b < 20; b+=0.01)
        {
            for(c = b+0.01; c < 10.01; c+=0.01)
            {
                for(d = c+0.01; d < 20.01-a-b-c; d+=0.01)
                {
                    if(a+b+c+d == a*b*c*d)
                        printf("%.2f %.2f %.2f %.2f\n", a, b, c, d);
                    if(a*b*c*d > a+b+c+d)
                        break;
                }
            }
        }
    }
    return 0;
}
