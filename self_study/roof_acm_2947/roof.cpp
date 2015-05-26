#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <cassert>
#include <stack>
#include <deque>
#include <set>
#include <list>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define REP(i, n) for(int i = 0; i < (n); ++i)

#define FOR(i, a, b) for(int i = (a), i < (b); ++i)

#define VAR(v, x) __typeof(x) v = x

#define FOREACH(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)

#define TRACE(x) if(debug) cout << #x << " = " << x << endl;

#define INF 1000000000
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

bool debug = false;
int checkRead;
//done shortcut
////////////////


class EndPoint
{
public:
    int x, y; //position of the end point
    int idx;  //idx of segment that contain this end point
    bool left;// = true if this end point is left end

    EndPoint(int ox, int oy, int oidx, bool oleft)
    {
        x = ox; y = oy; idx = oidx; left = oleft;
    };

    bool operator<(const EndPoint &o) const
    {
        if(x != o.x) return (x < o.x); //small x first
        else if(left != o.left) return (left); //add left end to sweepline first
        else if(left == true) return (y < o.y); //if start of a segment, add (to sweepline) from bottom to top
        else return (y > o.y); //remove (from sweepline) from top to bottom
    }
};

int n; //nb of segments
int in_xlow, in_xhigh, in_ylow, in_yhigh;

//sweepline contains index of segments it intersect with
list <int> sweepline;
//vector contains end points of segments
vector<EndPoint> EPs;
vector<EndPoint> EPsSorted;
const EndPoint initEP(-1, -1, -1, true);
vector<int> sky;
vector<int> col;
vector<int> dropTO;
vector<int> nbSources;

void readIn()
{
  //read input
  checkRead = scanf("%d", &n); assert(checkRead == 1);
  EPs.assign(2*n, initEP);
  sky.assign(n, 0);
  nbSources.assign(n, 1);//sky is alreay a source
  col.assign(n, 0);
  dropTO.assign(n, -1);

  REP(i, n)
    {
       checkRead = scanf("%d %d %d %d", &in_xlow, &in_ylow, &in_xhigh, &in_yhigh); assert(checkRead == 4);
       EPs[2*i]     = EndPoint(in_xlow, in_ylow, i, true);
       EPs[2*i + 1] = EndPoint(in_xhigh, in_yhigh, i, false);
    }
  EPsSorted.assign(EPs.begin(), EPs.end());
  sort(EPsSorted.begin(), EPsSorted.end());
}

int findDrop(int xAbove, int yAbove)
{
    double maxHeight = -0.01;
    int drop_to_id = -1;
    FOREACH(c, sweepline)
    {
        int idx = *c;
        EndPoint leftend  = EPs[2*idx];
        EndPoint rightend = EPs[2*idx + 1];
        double height = 1.0/(rightend.x - leftend.x)*(rightend.y - leftend.y)*(xAbove - leftend.x) + leftend.y;
        if(height >= yAbove) continue;
        if(maxHeight < height)
        {
            maxHeight = height;
            drop_to_id = idx;
        }
    }
    return drop_to_id;
}

void sweepping()
{
    REP(i, 2*n)
    {
        EndPoint cur = EPsSorted[i];
        if(cur.left)//start of a segment add this segment to sweepline
        {
            sweepline.push_back(cur.idx);

            if(EPs[2*cur.idx].y < EPs[2*cur.idx + 1].y)//this is the lower end point
            {
                int dropIdx = findDrop(cur.x, cur.y);
                dropTO[cur.idx] = dropIdx;
            }
        }
        else//end of a segment -> remove from sweepline
        {
            sweepline.remove(cur.idx);

            if(EPs[2*cur.idx + 1].y < EPs[2*cur.idx].y)//this is a falling point
            {
                int dropIdx = findDrop(cur.x, cur.y);
                dropTO[cur.idx] = dropIdx;
            }
        }
        if(!sweepline.empty())
        {
            int topSegment = findDrop(cur.x, INF);
            int amount = EPsSorted[i+1].x - cur.x;
            if(topSegment != -1) sky[topSegment] += amount;
        }
    }
}


void add(int idx, int amount)
{
    if(idx != -1)
    {
        col[idx] += amount;
        nbSources[idx]--;
        if(nbSources[idx] == 0)
            add(dropTO[idx], col[idx]);
    }
}

void accumu()
{
    REP(i, n)
    {
        if(dropTO[i] != -1)
            nbSources[dropTO[i]]++;
    }
    REP(i, n)
    {
        add(i, sky[i]);
    }
}

void printCol()
{
    REP(i,n)
    {
        printf("%d\n", col[i]);
    }
}

void solve()
{
    readIn();
    sweepping();
    accumu();
    printCol();
}

int main()
{
    int nbCases;
    checkRead = scanf("%d", &nbCases); assert(checkRead == 1);

    while(nbCases--)
    {
        solve();
        if(nbCases) printf("\n");
    }

    return 0;
}
