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
typedef pair<ii, int> iii;
typedef vector<int> vi;
typedef vector<ii> vii;

bool debug = false;
int checkRead;
//done shortcut
////////////////

#define SZ_AR 100
const int dirX[4] = {1, -1, 0, 0}; //0: down, 1: up, 2: right, 3: left
const int dirY[4] = {0, 0, 1, -1};

int nbLines;
int nbCols;

bool mat[SZ_AR][SZ_AR] = {false};
bool stateVisited[SZ_AR][SZ_AR][4] = {false};
queue <iii> Q;

int xCote1, xCote2, yCote1, yCote2;//neighbor

char aLine[SZ_AR];

bool inBounds(int x, int y)
{
	return ( 0 <= x && 0 <= y && x < nbLines && y < nbCols );
}

bool entranceCandidate(int x, int y, int dir)
{
    xCote1 = x; yCote1 = y;
    xCote2 = x; yCote2 = y;
    if(dir < 2) //up or down
    {
        xCote1 += dirX[2]; yCote1 += dirY[2];
        xCote2 += dirX[3]; yCote2 += dirY[3];
        if(inBounds(xCote1, yCote1) && inBounds(xCote2, yCote2))
            return (!mat[xCote1][yCote1] && !mat[xCote2][yCote2]);
    }
    else
    {
        xCote1 += dirX[0]; yCote1 += dirY[0];
        xCote2 += dirX[1]; yCote2 += dirY[1];
        if(inBounds(xCote1, yCote1) && inBounds(xCote2, yCote2))
            return (!mat[xCote1][yCote1] && !mat[xCote2][yCote2]);
    }
    return false;
}

int findDir(int deltaX, int deltaY)
{
    REP(i, 4)
    {
        if(deltaX == dirX[i] && deltaY == dirY[i])
            return i;
    }
    cout << "wrong at findDir\n";
    return -1;
}

//move one point around the contour
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

}
//check avai of next cell of (x,y) in direction dir
bool nextCellOpen(int x, int y, int dir)
{
    return (inBounds(x + dirX[dir], y + dirY[dir]) && mat[x + dirX[dir]][y + dirY[dir]]);
}

bool isRealContour(int xE, int yE, int dirE) //Entrance info
{
    if(!entranceCandidate(xE, yE , dirE))
        return false;

    int oppDir = (dirE < 2)? (1 - dirE) : (5 - dirE);
    if(nextCellOpen(xCote1, yCote1, oppDir))
    {
        int xContour = xCote1;
        int yContour = yCote1;
        int xOutside = xCote1 + dirX[oppDir];
        int yOutside = yCote1 + dirY[oppDir];
        REP(i, (nbCols*nbLines))
        {
            while()
        }
    }

}

void findEntrance()
{


}

void readIn()
{
	checkRead = scanf("%d\n%d\n", &nbLines, &nbCols); assert(checkRead == 2);	
	
	REP(i, nbLines)
	{
		checkRead = scanf("%s", aLine);
		REP(j, nbCols)
		{
			mat[i][j] = (aLine[j] == '.')? true : false;
		}
	}
	
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

int main()
{
	int nbCases;
	checkRead = scanf("%d", &nbCases); assert(checkRead == 1);
	while(nbCases--)
	{
		readIn();
		printMat();		
		
		if(nbCases) printf("\n");
	}
	
	return 0;
}
