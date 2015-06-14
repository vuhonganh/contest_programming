
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
typedef pair <ii, int> iii;
bool debug = false;
int checkRead;
//done shortcut
////////////////

#define MAX_SZ 100
int nbLines;
int nbCols;

char aLine[MAX_SZ];
bool mat[MAX_SZ][MAX_SZ];

bool visited[MAX_SZ][MAX_SZ];


//DIRECTION
const int dirX[4] = {1, -1, 0, 0}; //0: down, 1: up, 2: right, 3: left
const int dirY[4] = {0, 0, 1, -1};

const int leftDir[4] = {2, 3, 1, 0};
const int rightDir[4] = {3, 2, 0, 1};


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
            visited[i][j] = !mat[i][j];
        }
    }
}

//from (x,y) check if can move along the dir direction
inline bool movePossible(int x, int y, int dir)
{
    return (inBound(x + dirX[dir], y + dirY[dir]) && mat[x + dirX[dir]][y + dirY[dir]] && !visited[x + dirX[dir]][y + dirY[dir]]);
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
    }
    return true;
}

bool atYard(int &x, int &y, int &dir)
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

bool firstUnvisited(ii &unvisited)
{
    REP(i, nbLines)
    {
        REP(j, nbCols)
        {
            if(!visited[i][j])
            {
                unvisited.first  = i;
                unvisited.second = j;
                return true;
            }
        }
    }
    return false;
}

void move(ii &curP, int curD)
{
    curP.first  += dirX[curD];
    curP.second += dirY[curD];
}
int xCote1, xCote2, yCote1, yCote2;//neighbor
bool entranceCandidate(int x, int y, int dir)
{
    xCote1 = x; yCote1 = y;
    xCote2 = x; yCote2 = y;
    if(dir < 2) //up or down
    {
        xCote1 += dirX[2]; yCote1 += dirY[2];
        xCote2 += dirX[3]; yCote2 += dirY[3];
        if(inBound(xCote1, yCote1) && inBound(xCote2, yCote2))
            return (!mat[xCote1][yCote1] && !mat[xCote2][yCote2]);
    }
    else
    {
        xCote1 += dirX[0]; yCote1 += dirY[0];
        xCote2 += dirX[1]; yCote2 += dirY[1];
        if(inBound(xCote1, yCote1) && inBound(xCote2, yCote2))
            return (!mat[xCote1][yCote1] && !mat[xCote2][yCote2]);
    }
    return false;
}

iii findEntrance()
{
    queue<iii> Q;
    ii start;
    while(firstUnvisited(start))
    {
        REP(dir, 4)
        {
            if(movePossible(start.first, start.second, dir))
            {
                Q.push(iii(start, dir));
            }
        }
        visited[start.first][start.second] = true;

        while(!Q.empty())
        {
            iii cur = Q.front(); Q.pop();
            ii curPoint = cur.first;
            int curDir = cur.second;
            if(entranceCandidate(curPoint.first, curPoint.second, curDir))
            {
                return cur;
            }
            //move and add new possible move
            move(curPoint, curDir);
            REP(dir, 4)
            {
                if(movePossible(curPoint.first, curPoint.second, dir))
                {
                    Q.push(iii(curPoint, dir));
                }
            }
            visited[curPoint.first][curPoint.second] = true;
        }
    }
    return iii( ii(-1,-1), -1);
}

void printMat()
{
    REP(i, nbLines)
    {
        REP(j, nbCols)
        {
            if(mat[i][j]) printf("%c", '.'); else printf("%c", '#');
        }
        printf("\n");
    }
}


void inline turnLeft(int &x, int &y, int &id_dir)
{
    id_dir = leftDir[id_dir];
    x += dirX[id_dir];
    y += dirY[id_dir];
}

void inline turnRight(int &x, int &y, int &id_dir)
{
    id_dir = rightDir[id_dir];
    x += dirX[id_dir];
    y += dirY[id_dir];
}


void solve()
{
    //ii startp(0, nbCols/2);
    iii entrance = findEntrance();
    if(entrance.second == -1)
        printf("N0\n");
    else
    {
        int x = entrance.first.first; int y = entrance.first.second;
        int idxDir = entrance.second;
        if(debug) cout << "entrance = " << x << ", "<< y << endl;
        int ox = x; int oy = y;
        while(!atYard(x, y, idxDir))
        {

            if(leftPossible(x, y, idxDir))
            {
                turnLeft(x, y, idxDir);
                continue;
            }
            else if(forwardPossible(x, y, idxDir))
            {
                x += dirX[idxDir];
                y += dirY[idxDir];
                continue;
            }
            else if(rightPossible(x, y, idxDir))
            {
                turnRight(x, y, idxDir);
            }
            else
            {
                printf("NO\n");
                return;
            }
            if(ox == x && oy == y)
            {
                printf("NO\n");
                return;
            }
        }
        printf("YES\n");
        return;
    }
}

int main()
{
    int nbCases;
    checkRead = scanf("%d", &nbCases); assert(checkRead == 1);
    while(nbCases--)
    {
        readIn();
        //printMat();
        solve();
        if(nbCases) printf("\n");
    }

    return 0;
}
