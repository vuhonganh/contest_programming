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
bool road[MAX_SZ][MAX_SZ];
//const int dx[4] = {1, 0, -1, 0}; //direction. Note that dir = 0,2 corresponds to horizontal direction, dir = 1,3 corresponds to vertical direction
//const int dy[4] = {0, 1, 0, -1};

//DIRECTION
const int dirX[4] = {1, -1, 0, 0}; //0: down, 1: up, 2: right, 3: left
const int dirY[4] = {0, 0, 1, -1};

const int leftDir[4] = {2, 3, 1, 0};
const int rightDir[4] = {3, 2, 0, 1};

void inline turnLeft(int &x, int &y, int &id_dir)
{
    id_dir = leftDir[id_dir];
    x += dirX[id_dir];
    y += dirY[id_dir];
    //road[x][y] = true;
}

void inline turnRight(int &x, int &y, int &id_dir)
{
    id_dir = rightDir[id_dir];
    x += dirX[id_dir];
    y += dirY[id_dir];
    //road[x][y] = true;
}

void inline backWard(int &x, int &y, int &id_dir)
{
  id_dir = (id_dir < 2)? 1 - id_dir : 5 - id_dir;
  x += dirX[id_dir];
  y += dirY[id_dir];
}

int inline findLeftDir(const int &id_dir)
{
    return leftDir[id_dir];
}

int inline findRightDir(const int &id_dir)
{
    return rightDir[id_dir];
}

int inline findDir(int deltaX, int deltaY)
{
    REP(i, 4)
    {
        if(deltaX == dirX[i] && deltaY == dirY[i])
            return i;
    }
    return -1;
}

bool inBound(const int &x, const int &y)
{
    return ( (0 <= x) && (x < nbLines) && (0 <= y) && (y < nbCols));
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
            road[i][j] = false;
        }
    }
}

//asume entrance is never at corner
//DIR has to be the new dir if it have turned
bool nextIsEntrance(int &xContour, int &yContour, int &xOutside, int &yOutside, int &idxDir)
{
    if(mat[xContour + dirX[idxDir]][yContour + dirY[idxDir]] && mat[xOutside + dirX[idxDir]][yOutside + dirY[idxDir]])
    {
        if(!mat[xContour + 2*dirX[idxDir]][yContour + 2*dirY[idxDir]])
        {
            xContour += dirX[idxDir]; yContour += dirY[idxDir];
            xOutside += dirX[idxDir]; yOutside += dirY[idxDir];
            idxDir = findDir(xContour - xOutside, yContour - yOutside);
            return true;
        }
    }
    return false;
}

void moveAroundContour(int &xContour, int &yContour, int &xOutside, int &yOutside, int &idxDir)
{
    //if corner
    if(!mat[xContour + dirX[idxDir]][yContour + dirY[idxDir]] && !mat[xOutside + dirX[idxDir]][yOutside + dirY[idxDir]])
    {
        int idxTurn = findDir(xOutside - xContour, yOutside - yContour);
        //update the move
        xOutside = xContour; yOutside = yContour;
        xContour += dirX[idxDir]; yContour += dirY[idxDir];
        idxDir = idxTurn;
    }
    else if(mat[xContour + dirX[idxDir]][yContour + dirY[idxDir]] && mat[xOutside + dirX[idxDir]][yOutside + dirY[idxDir]])
    {
        int idxTurn = findDir(xContour - xOutside, yContour - yOutside);
        //in fact in this case, we are already at the corner
        xOutside = xContour + dirX[idxDir]; yOutside = yContour + dirY[idxDir];
        idxDir = idxTurn;
    }
    else //normal case (not corner)
    {
         xContour += dirX[idxDir]; yContour += dirY[idxDir];
         xOutside += dirX[idxDir]; yOutside += dirY[idxDir];
    }
    //road[xContour][yContour] = true;
}

bool getEntrance(ii &startPoint, ii &entrance, int &idDirEnter)
{
    //start point (nam tren cot giua cua ma tran)
    int x = startPoint.first;
    int y = startPoint.second;

    //start dir
    const int downDir = 0;
    const int upDir = 1;
    const int rightDir = 2;
    const int leftDir = 3;
    //road[x][y] = true;
    while(mat[x][y])
    {        
        x += dirX[downDir];
        y += dirY[downDir];
        //road[x][y] = true;
    }
    int ox = x; int oy = y;
    //(x, y) now in contour
    int idxDir;
    if(!mat[x + dirX[leftDir]][y + dirY[leftDir]])
        idxDir = leftDir;
    else
        idxDir = rightDir;

    int xOutside = x + dirX[upDir];
    int yOutsire = y + dirY[upDir];
    while(!nextIsEntrance(x, y, xOutside, yOutsire, idxDir))
    {
        moveAroundContour(x, y, xOutside, yOutsire, idxDir);
        if(ox == x && oy == y)
            return false;
    }
    //if go here, i.e. (x,y) is the entrance
    entrance = ii(x, y);
    idDirEnter = idxDir;
    //cout << "idxDir = " << idxDir << endl;
    return true;
}


void printMat(int x, int y, int xYard, int yYard)
{
    char sym[2] = {'#', '.'};
    REP(i, nbLines)
    {
        REP(j, nbCols)
                if(i == x && j == y) printf("%c", 'E');
                else if(i == xYard && j == yYard) printf("%c", 'Y');
                else if(road[i][j]) printf("%c", '+');
                else printf("%c", sym[mat[i][j]]);
        printf("\n");
    }
}

//person at (x,y), check if it could turn left or not
inline bool leftPossible(const int &x, const int &y, const int &dir)
{
    int l = leftDir[dir];
    return mat[x + dirX[l]][y + dirY[l]];

}

inline bool rightPossible(const int &x, const int &y, const int &dir)
{
    int r = rightDir[dir];
    return mat[x + dirX[r]][y + dirY[r]];
}

inline bool forwardPossible(const int &x, const int &y, const int &dir)
{
    return mat[x + dirX[dir]][y + dirY[dir]];
}

int allDirX[8] = {1, 1, 1, 0, 0, -1, -1, -1};
int allDirY[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
bool atYardCent(int x, int y)
{
    REP(i,8)
    {
       if(!inBound(x + allDirX[i], y + allDirY[i]) || !mat[x + allDirX[i]][y + allDirY[i]])
            return false;
      /* if(!inBound(x + allDirX[i], y + allDirY[i]))
          printf("(%d, %d)", x + allDirX[i], y + allDirY[i]);

      if(!mat[x + allDirX[i]][y + allDirY[i]])
      {
          return false;
      }*/

    }
    REP(i, 8)
      road[x + allDirX[i]][y + allDirY[i]] = true;
    road[x][y] = true;
    return true;
}

bool atYard(const int &x, const int &y, const int &dir)
{
  if(leftPossible(x, y , dir) && forwardPossible(x, y, dir))
    {
        int l = leftDir[dir];
        if(forwardPossible(x + dirX[l], y + dirY[l], dir))
            return atYardCent(x + dirX[l], y + dirY[l]);
    }
    if(rightPossible(x, y , dir) && forwardPossible(x, y, dir))
    {
        int r = rightDir[dir];
        if(forwardPossible(x + dirX[r], y + dirY[r], dir))
            return atYardCent(x + dirX[r], y + dirY[r]);
    }
    return false;
}

bool atYard2(int x, int y)
{
  if(mat[x-1][y]  && mat[x-1][y-1] && mat[x][y-1]) return true;
  if(mat[x-1][y]  && mat[x-1][y+1] && mat[x][y+1]) return true;
  if(mat[x+1][y]  && mat[x+1][y-1] && mat[x][y-1]) return true;
  if(mat[x+1][y]  && mat[x+1][y+1] && mat[x][y+1]) return true;
  return false;

}

bool findEntranceRobust(ii &resEntrance, int &resIdxDir)
{
    int nbStartPoints = 3*(nbLines/2);
    vii listEntrance(nbStartPoints, ii(-1,-1));
    vi listDirs(nbStartPoints, -1);
    vector<bool> foundEntrance(nbStartPoints, false);

    REP(i, nbStartPoints)
    {
        ii startPoint(i%(nbLines/3), (i%3)*nbCols/4 + nbCols/4);
        foundEntrance[i] = (getEntrance(startPoint, listEntrance[i], listDirs[i]));
    }
    REP(i, nbStartPoints-1)
    {
        if(foundEntrance[i] && foundEntrance[i+1])
        {
            if(listEntrance[i].first == listEntrance[i+1].first && listEntrance[i].second == listEntrance[i+1].second)
            {
                resIdxDir   = listDirs[i];
                resEntrance = listEntrance[i];
                if(debug) printf("found entrance robust at ligne i = %d\n", i);
                return true;
            }
        }
    }
    return false;
}

void solve()
{
    //ii startp(0, nbCols/2);
    ii entrance;
    int idxDir;
    if(findEntranceRobust(entrance, idxDir))    
    {
        int x = entrance.first; int y = entrance.second;
        if(debug) cout << "entrance = " << x << ", "<< y << endl;
        int ox = x; int oy = y;
        while(!atYard(x, y, idxDir))
        {
	  //road[x][y] = true;
            if(leftPossible(x, y, idxDir))
            {
                turnLeft(x, y, idxDir);
                //continue;
            }
            else if(forwardPossible(x, y, idxDir))
            {
                x += dirX[idxDir];
                y += dirY[idxDir];
                //continue;
            }
            else if(rightPossible(x, y, idxDir))
            {
                turnRight(x, y, idxDir);
		//continue;
            }
	    else
	      {
		backWard(x, y, idxDir);
	
	      }
            /*else
            {
                if(debug) printMat(ox, oy, x, y);
                printf("NO\n");
                return;
		}*/
            if(ox == x && oy == y)
            {
	      if(debug) printMat(ox, oy, x, y);
                printf("NO\n");
                return;
            }
        }
        if(debug) printMat(ox, oy, x, y);
        printf("YES\n");
        return;
    }
    else
    {
        printf("NO\n");
        //printf("no entrance found --> STH WRONG\n");
    }
}

int main()
{
    int nbCases;
    checkRead = scanf("%d", &nbCases); assert(checkRead == 1);
    while(nbCases--)
    {
        readIn();
        //cout << "done readIN\n";
        solve();
//        ii entrance;
//        int idxDirEnter;
//        if(getEntrance(entrance, idxDirEnter))
//        {
//            printf("%d %d\n", entrance.first, entrance.second);
//            printf("direction enter is %d, note that 0: down, 1: up, 2: right, 3: left\n", idxDirEnter);
//            printMat(entrance.first, entrance.second);
//        }
//        else
//        {
//            printf("no entrance found --> STH WRONG\n");
//        }

        if(nbCases) printf("\n");
    }

    return 0;
}
