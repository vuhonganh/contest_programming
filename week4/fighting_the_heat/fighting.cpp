//Main idea: exhautive search for each word: row, collumn, up to down diagonal, down to up diagonal (both backward and forward)

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <cassert>
#include <stack>
#include <deque>
#include <set>
#include <string.h>

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

 
int nbRows, nbCols, nbWords;
char words[200][24];
char grid[41][41];
bool highlighted[41][41];
bool readIn()
{
    checkRead = scanf("%d", &nbRows);
    if(checkRead == EOF)
        return false;
    checkRead = scanf("%d", &nbCols);  assert(checkRead == 1);
    checkRead = scanf("%d", &nbWords); assert(checkRead == 1);

    REP(i, nbWords)
    {
        checkRead = scanf("%s", words[i]);
    }
    REP(i, nbRows)
    {
        checkRead = scanf("%s", grid[i]);
    }
    //re init
    memset(highlighted, false, sizeof(highlighted));

    return true;
}

//dir = 1: forward, dir = -1: backword
void searchRow(int row, char * w, int len_w, int dir)
{
    int startIdxWord = (dir == 1)? 0 : len_w - 1;
    REP(i, nbCols - len_w + 1)
    {
        REP(j, len_w)
        {
            if(grid[row][i+j] != w[startIdxWord + j*dir])
                goto nextCell;
        }
        //go here means it matches word w in the list
        REP(j, len_w)
        {
            highlighted[row][i+j] = true;
        }
        nextCell:;
    }

}

//dir = 1: forward, dir = -1: backward
void searchCollumn(int col, char* w, int len_w, int dir)
{
    int startIdxWord = (dir == 1)? 0 : len_w - 1;
    REP(i, nbRows - len_w + 1)
    {
        REP(j, len_w)
        {
            if(grid[i+j][col] != w[startIdxWord + j*dir])
                goto nextCell;
        }
        //go here means it matches word w in the list
        REP(j, len_w)
        {
            highlighted[i+j][col] = true;
        }
        nextCell:;
    }
}

//dir = 1: forward, dir = -1: backward
void searchDiagUpDown(int startRow, char * w, int len_w, int dir)
{
    if(startRow + len_w > nbRows) return;
    int startIdxWord = (dir == 1) ? 0 : len_w - 1;
    REP(i, nbCols - len_w + 1)
    {
        REP(j, len_w)
        {
            if(grid[startRow + j][i + j] != w[startIdxWord + j*dir])
                goto nextCell;
        }
        REP(j, len_w)
        {
            highlighted[startRow + j][i + j] = true;
        }
        nextCell:;
    }
}

//start from Down to Up
//dir = 1: forward, dir = -1: backward
void searchDiagDownUp(int startRow, char * w, int len_w, int dir)
{
    if(startRow < len_w - 1 ) return;
    int startIdxWord = (dir == 1)? 0 : len_w - 1;

    REP(i, nbCols - len_w + 1)
    {
        REP(j, len_w)
        {
            if(grid[startRow - j][i + j] != w[startIdxWord + j*dir])
                goto nextCell;
        }
        REP(j, len_w)
        {
            highlighted[startRow - j][i + j] = true;
        }
        nextCell:;
    }
}

void search()
{
    REP(i, nbWords)
    {
        int len_w = strlen(words[i]);
        REP(j, nbRows)
        {
            searchRow(j, words[i], len_w, 1);
            searchRow(j, words[i], len_w, -1);
            searchDiagDownUp(j, words[i], len_w, 1);
            searchDiagDownUp(j, words[i], len_w, -1);
            searchDiagUpDown(j, words[i], len_w, 1);
            searchDiagUpDown(j, words[i], len_w, -1);
        }
        REP(j, nbCols)
        {
            searchCollumn(j, words[i], len_w, 1);
            searchCollumn(j, words[i], len_w, -1);
        }
    }

    REP(i, nbRows)
    {
        REP(j, nbCols)
        {
            if(!highlighted[i][j])
            {
                printf("%c", grid[i][j]);
            }
        }
    }
    printf("\n");
}


void printGrid()
{
//    REP(i, nbRows)
//    {
//        printf("%s\n", grid[i]);
//    }
    REP(i, nbRows)
    {
        REP(j, nbCols)
        {
            if(highlighted[i][j]) printf("%c", '#');
            else printf("%c", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void printWords()
{
    REP(i, nbWords)
    {
        printf("%s\n", words[i]);
    }
    printf("\n");
}

int main()
{
    while(readIn())
    {
//        printWords();
//        printGrid();
        search();
//        printWords();
//        printGrid();
    }
    return 0;
}
