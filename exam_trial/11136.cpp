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
    multiset<int> s;

    multiset<int>::iterator itF;//first
    multiset<int>::iterator itL;//last

    int N;
    int nb;
    int cur;
    long long res;
    while(true)
    {
        ri(N);
        if(N == 0) break;
        //init
        s.clear();
        res = 0;

        for(int j = 0; j < N; ++j)
        {
            ri(nb);
            for(int i = 0; i < nb; ++i)
            {
                ri(cur);
                s.insert(cur);
            }
            itF = s.begin();
            itL = s.end();
            --itL;
            res += ((*itL) - (*itF));
            s.erase(itF);
            s.erase(itL);
        }
        printf("%lld\n", res);
    }

    return 0;
}
