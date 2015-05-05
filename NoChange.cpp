#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

//n1*v1 + ... = S
bool possible(int S, int idxStart, int coins[], int nbCoins, int ni_minus1)
{	
    //base case
    if(S == 0)
        return true;

    //get value of first coin
    int vi = coins[idxStart];
    int ni = S/vi;

    //conserve condition n1 > n2 >...> ni-1 > ni
    ni = min(ni, ni_minus1);

    //start at ni, (down to 1)
    while(ni > 0)
    {
        bool niIsTrue;
        if(vi*ni == S)
            return true;

        //calculate sum of coin values
        int sumCoin = 0;
        for(int i = idxStart; i < nbCoins; ++i)
            sumCoin += coins[i];
        //end calculate sum


        if(ni*sumCoin < S)
            return false;
        else if(ni*sumCoin == S)
            return true;
        else
        {
            niIsTrue = possible(S-ni*vi, idxStart+1, coins, nbCoins, ni);
        }

        //ni not good, down to ni-1
        if(niIsTrue)
           return true;
        else
        {
            ni -= 1;
        }
    }
}

int main()
{
    int MAX_VAL   = 200000;
    int MAX_SZ_AR = 5;
    int nbCase;
    cin >> nbCase;

    for(int i = 0; i < nbCase; ++i)
    {
        int S;
        cin >> S;
        int nbCoins;
        cin >> nbCoins;

        int coins[MAX_SZ_AR];
        for(int j = 0; j < nbCoins; ++j)
        {
            cin >> coins[j];
        }

        if(possible(S, 0, coins, nbCoins, MAX_VAL))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;

        if(i != nbCase-1)
            cout << "\n" << endl;

    }

    return 0;
}

