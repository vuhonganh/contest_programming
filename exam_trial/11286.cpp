
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
    map < set<int> , int> m;
    int N;

    int cur;
    while(true)
    {
        ri(N);
        if(N == 0) break;
        int popularity = 0;
        m.clear();
        for(int i = 0; i < N; ++i)
        {
            set<int> s;
            for(int j = 0; j < 5; ++j)
            {
                ri(cur);
                s.insert(cur);
            }
//            if(m.find(s) == m.end()) m[s] = 1;
//            else m[s]++;
            m[s]++;
            popularity = max(m[s], popularity);
        }

        map<set<int>, int>::iterator it;
        int cnt = 0;
        for(it = m.begin(); it != m.end(); ++it)
        {
            if(it->second == popularity) cnt += popularity;
        }
        printf("%d\n", cnt);
    }
    return 0;
}
