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

vector <int> id;
vector <int> sz;

int find(int x)
{
    if(id[x] == x)
        return x;
    else
    {
        id[x] = find(id[x]);
        return id[x];
    }
}

void unite(int x, int y)
{
    int px = find(x);
    int py = find(y);

    if(sz[px] < sz[py])
    {
        sz[py] += sz[px];
        id[px] = py;
    }
    else
    {
        sz[px] += sz[py];
        id[py] = px;
    }
}

int main()
{
    int TC;
    int nbComp; //nb of computer
    int x, y;   //2 computers
    int nbCon;
    int nbUnCon;
    char c;
    //char aline[128];
    ri(TC);

    if(scanf("\n", &c) != 0) cout << "scanf enter line problem" << endl;
    if(scanf("\n", &c) != 0) cout << "scanf enter line problem" << endl;


    while(TC--)
    {
        ri(nbComp);
        //init
        sz.assign(1001, 1);
        id.assign(1001, 0);
        for(int i = 0; i < 1001; ++i)
        {
            id[i] = i;
        }
        nbCon = 0;
        nbUnCon = 0;
        //done init
        //scanf("\n", &c);
        if(scanf("\n", &c) != 0) cout << "scanf enter line problem" << endl;

        while(scanf("%c %d %d \n", &c, &x, &y) == 3)
        {
//            int cr = scanf("%c %d %d\n", &c, &x, &y);
//            if(cr != 3) { cout << "scanf problem" << endl; break;}
            if(c == 'c')
            {
                unite(x,y);
            }
            else
            {
                if(find(x) == find(y))
                    nbCon++;
                else
                    nbUnCon++;
            }
        }
        printf("%d,%d\n", nbCon, nbUnCon);
        if(TC) printf("\n");
    }

    return 0;
}
