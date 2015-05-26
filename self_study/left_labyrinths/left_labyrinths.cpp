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

#define MAX_SZ 100
int nbLines;
int nbCols;

char aLine[MAX_SZ];
bool mat[MAX_SZ][MAX_SZ];
const int dx[4] = {1, 0, -1, 0}; //direction. Note that dir = 0,2 corresponds to horizontal direction, dir = 1,3 corresponds to vertical direction
const int dy[4] = {0, 1, 0, -1};

bool inBound(const int &x, const int &y)
{
    return ( (0 <= x) && (x < nbCols) && (0 <= y) && (y < nbLines));
}

void readIn()
{
    checkRead = scanf("%d", &nbLines); assert(checkRead == 1);
    checkRead = scanf("%d", &nbCols); assert(checkRead == 1);

    REP(i, nbLines)
    {
        checkRead = scanf("%s", aLine);
        REP(j, nbCols)
        {
            mat[i][j] = (aLine[j] == '.') ? true : false;
        }
    }
}
//check if (x,y) is a corner, and change the direction dir to continue along the contour
bool isCorner(const int &x, const int &y, int &dir)
{
    int nextDir = (dir + 1)%2;
    if(inBound(x + dx[nextDir], y + dy[nextDir]) && !mat[x + dx[nextDir]][y + dy[nextDir]])
    {
        dir = nextDir;
        return true;
    }
    else if(inBound(x + dx[nextDir + 2], y + dy[nextDir + 2]) && !mat[x + dx[nextDir + 2]][y + dy[nextDir + 2]])
    {
        dir = nextDir + 2;
        return true;
    }
    return false;
}

//start point must be feasible point (that people can stand)
bool findEntrance(ii &startPoint, ii &entrance)
{
    int x = startPoint.first; int y = startPoint.second;

    if(!inBound(x, y)) return false;
    int toCenterx = (x < nbCols/2)? 1 : -1;
    int toCentery = (y < nbLines/2)? 1: -1;

    while(mat[x][y])
    {
        x += toCenterx;
        y += toCentery;
    }
    //now (x,y) is the first point of contour labyrinth
    int dir = -1;//direction to continue on the contour of labyrinth
    REP(i, 4)
    {
        if(!mat[x + dx[i]][y + dy[i]])
        {
            dir = i;
            break;
        }
    }
    if(dir == -1) return false;//need to check another start point

    int xold = x; int yold = y;
    while(true)
    {
        while(!mat[x + dx[dir]][y + dy[dir]])
        {
            x += dx[dir];
            y += dy[dir];
        }
        //here, either (x,y) be near the entrance, either it's a corner of labyrinth
        //if it's not a corner than it's the entrance
        if(!isCorner(x, y, dir))
        {
            entrance = ii(x + dx[dir], y + dy[dir]);
            return true;
        }
        if(x == xold && y == yold)
            break;
    }
    return false;
}

void printMat(int x, int y)
{
    char sym[2] = {'#', '.'};
    REP(i, nbLines)
    {
        REP(j, nbCols)
                if(i == x && j == y) printf("%c", 'E');
                else printf("%c", sym[mat[i][j]]);
        printf("\n");
    }
}

int main()
{
    int nbCases;
    checkRead = scanf("%d", &nbCases); assert(checkRead == 1);
    while(nbCases--)
    {
        readIn();
        ii startPoint(0,0);
        ii entrance;
        if(findEntrance(startPoint, entrance))
        {
            printf("%d %d\n", entrance.first, entrance.second);
            printMat(entrance.first, entrance.second);
        }
        else
            printf("No entrance found\n");

        if(nbCases) printf("\n");
    }

    return 0;
}
