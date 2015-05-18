//main idea: find the first occurrence of the input date
//find the period of a round year (least common multiple)
//convert to long count


#include <iostream>
#include <algorithm>
#include <string.h>

using namespace std;

#define REP(i, n) for(int i = 0; i < (n); ++i)

#define VAR(v, x) __typeof(x) v = x

#define FOREACH(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)

#define TRACE(debug, x) if(debug) cout << #x << " = " << x << endl;

typedef unsigned long ulong;

bool debug = false;
bool checkRead = true;

//done shortcut
////////////////

//20 days
const char days[][16] = {"Imix", "Ik", "Akbal", "Kan", "Chikchan", "Kimi", "Manik", "Lamat", "Muluk", "Ok", "Chuen", "Eb", "Ben", "Ix", "Men", "Kib", "Kaban", "Etznab", "Kawak", "Ajaw"};

//19 months (18 months = 20 days) + (1 months = 5 days)
const char months[][16] = {"Pohp", "Wo", "Sip", "Zotz", "Sek", "Xul", "Yaxkin", "Mol", "Chen", "Yax", "Sak", "Keh", "Mak", "Kankin", "Muan", "Pax", "Kayab", "Kumku", "Wayeb"};

int input[4]; //input decoded as the nb.posiDay.nb.posiMonth --> need 4 numbers
const int start[4] = {9, 19, 3, 2}; //9 Ajaw 3 Sip
const int period = 260*365/5; //length of a calendar round year

void readInput()
{
    char day[16], month[16];
    //int nbDay, nbMonth;

    int nbRead = scanf("%d.%s%d.%s", &input[0], day, &input[2], month);
    checkRead = (nbRead == 4);

    REP(i, 20)
    {
        if(strcmp(days[i], day) == 0)
            input[1] = i;
    }


    REP(i, 19)
    {
        if(strcmp(months[i], month) == 0)
            input[3] = i;
    }

}

bool equalInput(int date[4])
{
    return ( (date[0] == input[0]) && (date[1] == input[1]) && (date[2] == input[2]) && (date[3] == input[3]) );
}



//advance one day
//13 * 20 day_names + 20 * 18 month_names + 5 * month_19th
void advance_oneDay(int date[4])
{
    int today[4];
    REP(i, 4) today[i] = date[i];

    //tzolkin day
    date[0] = (today[0] % 13) + 1;
    date[1] = (today[1] + 1) % 20;

    //haab day
    if(today[3] == 18)
        date[2] = (today[2] % 5) + 1;
    else
        date[2] = (today[2] % 20) + 1;

    if(((today[2] == 5) && today[3] == 18) || today[2] == 20)
        date[3] = (today[3] + 1) % 19;
}

//find the first orcurrence of input
//advance the start date during a period, until it matches the input, find nb of day it takes
//return -1 if the input date does not exist
int nbDaysToInput()
{
    int date[4];
    REP(i, 4) date[i] = start[i];

    REP(i, period)
    {
        if(equalInput(date))
            return i;
        advance_oneDay(date);
    }
    return -1;
}

void convertToLongCount(long counts, int ar[5])
{
    ar[0] = counts / 144000;
    counts %= 144000;
    ar[1] = counts / 7200;
    counts %= 7200;
    ar[2] = counts / 360;
    counts %= 360;
    ar[3] = counts / 20;
    ar[4] = counts % 20;

}

//start date = 8.0.0.0.0 in Long Count
void writeDays(int distanceToStart)
{
    long startLongCount = 8*144000 + distanceToStart;

    while(startLongCount < 1440000)
    {
        int ar[5] = {0};
        convertToLongCount(startLongCount, ar);
        printf("%d.%d.%d.%d.%d\n", ar[0], ar[1], ar[2], ar[3], ar[4]);
        startLongCount += period;
    }

}



void inline printDate(int date[4])
{
    printf("%d.%d.%d.%d", date[0], date[1], date[2], date[3]);
}

int main()
{
    int testCase;
    int nbRead = scanf("%d", &testCase);
    checkRead = (nbRead == 1);
    while(testCase--)
    {
        readInput();
        int distance = nbDaysToInput();
        if(distance == -1)
            printf("NO SOLUTION\n");
        else
            writeDays(distance);

        if(testCase)
            printf("\n");
    }
    //readInput();

    return 0;

}
