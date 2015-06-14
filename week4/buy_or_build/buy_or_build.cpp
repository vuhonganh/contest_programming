//main idea: sort cost to connect 2 cities, and exhautive try all posibility to buy subnetworks then build connectivity that lacked (from low to high cost)


#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <cassert>
#include <stack>
#include <deque>
#include <set>


using namespace std;

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
int checkRead;
inline int ri() {int input; checkRead = scanf("%d", &input); assert(checkRead == 1); return input;}
//done shortcut
////////////////

int compare(const void * a, const void * b) //order: minimum first
{
  return ( *(int*)a - *(int*)b );
}

int nbCities;  //nb of cities
int nbSubs;    //nb of subnetworks

int q[16], b[16][1024], c[16];  //nb of cities in the subnetworks and its indices, its cost
int x[1024], y[1024];  //coordinates of each cities

int dist[1024*1024][3]; //distance between 2 cities in the first cell and the identifiers stored in the two last cells
int distSz;
long long res;

int calCost(int i, int j)
{
   return ( (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]) );
}

void printDist()
{
    REP(i, distSz)
    {
        printf("%d %d %d\n", dist[i][0], dist[i][1], dist[i][2]);
    }
}

void sortDists()
{
    distSz = 0;
    REP(i, nbCities)
    {
        FOR(j, i+1, nbCities)
        {
            dist[distSz][0] = calCost(i, j);
            dist[distSz][1] = i+1;
            dist[distSz][2] = j+1;
            distSz++;
        }
    }

    //sort the costs from min to max
    qsort(dist, distSz, sizeof(dist[0]), compare);
}

//UNION FIND part
int id[1032], sz[1032];

void initUF()
{
    REP(i, nbCities+1)
    {
        id[i] = i;
        sz[i] = 0;
    }
}

int find(int x)
{
    while( x != id[x])
    {
        x = id[x];
    }
    return x;
}

int unite(int i, int j)//return 1 if we can unite these two sets of 2 cities and 0 if they are already in a set 
{
    int representI = find(i);
    int representJ = find(j);
    if(representI == representJ)
        return 0;
    if(sz[representI] < sz[representJ])//mettre class i to class j
    {
        id[representI] = representJ;
        sz[representJ] += sz[representI];
        //printf("change id[%d] = %d\n", i, j);
    }
    else
    {
        id[representJ] = representI;
        sz[representI] += sz[representJ];
        //printf("change id[%d] = %d\n", j, i);
    }
    return 1;
}

void solve()
{
    //sort the distances between any 2 cities
    sortDists();
    /*printf("sorted array:\n");
    for(int i = 0; i < distSz; ++i)
    {
        printf("%d = (%d -> %d)\n", dist[i][0], dist[i][1], dist[i][2]);
    }*/
    //solve by exhautive search: given nbSubs subnetworks -> have 2^nbSubs choices of buying subnetworks
    REP(choice, 1 << nbSubs)
    {
        int nbCitiesLeft = nbCities;
        long long curCost = 0;
        initUF();
        REP(i, nbSubs)
        {
            if(choice & (1 << i)) //if buying i-eme subnetwork
            {
                //printf("choice = %d, buy %d -th subnetwork\n", choice, i+1);
                curCost += c[i];
                //printf("current cost = %lld", curCost);
                //printf("cities bought = %d", b[i][0]);
                REP(j, q[i]-1)
                {
                    nbCitiesLeft -= unite(b[i][j], b[i][j+1]);
                    //printf(" %d", b[i][j+1]);
                }
                //printf("\n");
            }
        }
        REP(i, distSz)
        {
	  if(nbCitiesLeft == 1)//the rest is the whole union
            {
                break;
            }
            if(unite(dist[i][1], dist[i][2]))//if these two cities are not connected
            {
                //printf("nb of cities left = %d\n", nbCitiesLeft);
                curCost += dist[i][0];
                nbCitiesLeft--;
                //printf("unite 2 cities: %d %d, so nb of cities left = %d\n", dist[i][1], dist[i][2], nbCitiesLeft);
                //two cases: 1) one already connected to current, the other not -> connect it reduces one.
                //           2) these twos are not connected, -> connect it reduces one (two became one)
            }
        }
        res = min(res, curCost);
    }

    printf("%lld\n", res);
}
int idCity;
void readIn()
{
    checkRead = scanf("%d %d", &nbCities, &nbSubs); assert(checkRead == 2);
    REP(i, nbSubs)
    {
        checkRead = scanf("%d %d", &q[i], &c[i]); assert(checkRead == 2);
        REP(j, q[i])
        {
            checkRead = scanf("%d", &idCity); assert(checkRead == 1);
            b[i][j] = idCity;//-1;
        }
    }
    REP(i, nbCities)
    {
        checkRead = scanf("%d %d", &x[i], &y[i]); assert(checkRead == 2);
    }
    res = INF;
}

void printInput()
{
    REP(i, nbSubs)
    {
        printf("%d %d ", q[i], c[i]);
        REP(j, q[i])
        {
            printf("%d ", b[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    REP(i, nbCities)
            printf("%d %d\n", x[i], y[i]);
}

void dotask()
{
    int nbCases;
    checkRead = scanf("%d", &nbCases); assert(checkRead == 1);
    while(nbCases--)
    {
        readIn();
        //printInput();
//        int a[5] = {1, 3, 2, 5, 4};
//        qsort(a, 5, sizeof(int), compare);
//        REP(i, 5) printf("%d ", a[i]);
        //sortDists();
        solve();
        if(nbCases) printf("\n");
    }

}

int main()
{
//   readIn();
//   solve();

    dotask();
    return 0;
}
