#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <stdio.h>

using namespace std;

bool debug = false;
//bool debug = true;

#define trace(x) cout << #x << " = " << x << endl;

bool ri(int &res)
{
    int cr;
    cr = scanf("%d", &res);
    if(cr == 1) return true;
    else return false;
}

int main()
{
    map<char, int> prices;
    int N;
    int K;

    char c;
    int v;

    ri(N);

    for(int i = 0; i < N; ++i)
    {
        ri(K);
        prices.clear();
        for(int j = 0; j < K; ++j)
        {
            getchar();//aller a la ligne
            c = getchar();
            ri(v);
            prices[c] = v;
        }
        long sum = 0;
        int M;
        ri(M);
        int cnt = 0;
        while(true)
        {
            c = getchar();
            if(c == EOF) break;
            if(c == '\n') cnt++;
            if(cnt == M+1) break;
            if(c != '\n' || c != ' ')
                sum += prices[c];
        }
        double res = 1.0*sum/100.0;
        printf("%.2f$\n", res);
    }

    return 0;
}
