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

struct EndPoint
{
    int x, y; //position of the end point
    int idx;  //idx of segment that contain this end point
    long litre;
    long col;
    int drop;//-1 drop to ground, else drop = idx of segment water from this will drop to
    bool left;// = true if this end point is left end

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
const EndPoint initEP = {-1, -1, -1, 0, 0, -1, true};
vector<int> sky;
vector<int> col;
vector<int> dropTO;
vector<int> nbSources;

void printEndPoint(EndPoint &endP)
{
    printf("[%d, %d]: segment %d, contains %ld litres, drop on segment %d, ", endP.x, endP.y, endP.idx, endP.litre, endP.drop);
    if(endP.left) printf("left end\n");
    else printf("right end\n");
}

void addWater(int segmentIdx, long litres)
{
    EPs[2*segmentIdx].litre += litres;
    EPs[2*segmentIdx + 1].litre += litres;
}


void addWaterCol(int segmentIdx, long litres)
{
    EPs[2*segmentIdx].col += litres;
    EPs[2*segmentIdx + 1].col += litres;
}

void usePtrList(vector<EndPoint *> &listEP)
{
    REP(i, ( (int) listEP.size()))
    {
        EndPoint cur = * (listEP[i]);
        printEndPoint(cur);
    }
}

void test()
{
    EndPoint e1 = {1, 1, 0, 0, -1, true};
    EndPoint e2 = {3, 3, 0, 0, -1, false};
    EndPoint e3 = {1, 5, 1, 0, -1, true};
    EndPoint e4 = {2, 4, 1, 0, -1, false};

    vector<EndPoint *> ptrList;
    ptrList.push_back(&e1);
    ptrList.push_back(&e2);
    ptrList.push_back(&e3);
    ptrList.push_back(&e4);

    usePtrList(ptrList);

    vector<EndPoint> listEP;
    listEP.push_back(e1);
    listEP.push_back(e2);
    listEP.push_back(e3);
    listEP.push_back(e4);

    sort(listEP.begin(), listEP.end());

    REP(i, ( (int) listEP.size()))
    {
        printEndPoint(listEP[i]);

    }
}

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
       EPs[2*i]     = {in_xlow, in_ylow, i, 0, 0, -1, true};
       EPs[2*i + 1] = {in_xhigh, in_yhigh, i, 0, 0, -1, false};
    }
  EPsSorted.assign(EPs.begin(), EPs.end());
  sort(EPsSorted.begin(), EPsSorted.end());
}

//assuming water falls from point (xAbove,yAbove)
//find the first segment in the sweepline it meets, return the segment 's index or -1 if meet ground
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
                EPs[2*cur.idx].drop = dropIdx;
                EPs[2*cur.idx + 1].drop = dropIdx;
                if(debug) cout << "cur end is the lower end of segment " << cur.idx << ", drop to segment " << dropIdx << endl;
                dropTO[cur.idx] = dropIdx;
            }
            if(debug) cout << "segment " << cur.idx << " added in to sweepline" << endl;
        }
        else//end of a segment -> remove from sweepline
        {
            sweepline.remove(cur.idx);

            if(EPs[2*cur.idx + 1].y < EPs[2*cur.idx].y)//this is a falling point
            {

                int dropIdx = findDrop(cur.x, cur.y);
                EPs[2*cur.idx].drop = dropIdx;
                EPs[2*cur.idx + 1].drop = dropIdx;
                if(debug) cout << "cur end is the lower end of segment " << cur.idx << ", drop to segment " << dropIdx << endl;
                dropTO[cur.idx] = dropIdx;
            }
            if(debug) cout << "segment " << cur.idx << " removed from sweepline" << endl;
        }
        if(!sweepline.empty())
        {
            if(debug) cout << "go in to find top segment\n";

            int topSegment = findDrop(cur.x, INF);

            if(debug) cout << "found top segment = " << topSegment;

            int amount = EPsSorted[i+1].x - cur.x;

            if(debug) cout << "will add " << amount << "into top segment\n";
            if(debug) cout << "EPs size" << EPs.size() << endl;

            addWater(topSegment, amount);
            sky[topSegment] += amount;

            if(debug)
            {

                if(cur.left) {cout << "current end point: "; printEndPoint(EPs[cur.idx*2]);}
                else {cout << "current end point: "; printEndPoint(EPs[cur.idx*2 + 1]);}
                cout << "add " << (EPsSorted[i+1].x - cur.x) << " lits water from sky to top segment: " << topSegment; cout << endl; cout << endl;
            }
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
            printf("%d\n", col[i]);
}

void accumulateFromSegI(int i, long litres)
{
    int dropTo = EPs[2*i].drop;
    if(dropTo == -1) return;
    else
    {
        addWaterCol(dropTo, litres);
        accumulateFromSegI(dropTo, litres);
    }
}

void computeCollected()
{
    REP(i, n)
    {
        accumulateFromSegI(i, EPs[2*i].litre);
    }
}
void printEPs()
{
    REP(i, n)
        printEndPoint(EPs[2*i]);
}

void printResult()
{
    REP(i,n)
            printf("%ld\n", EPs[2*i].litre + EPs[2*i].col);
}

void solve()
{
    readIn();
    sweepping();
    //computeCollected();
    //printResult();
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


