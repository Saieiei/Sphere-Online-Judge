https://www.spoj.com/submit/PRATA/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

bool possibleSolution(vector<int>cooksRanks, int np, int sol)
{
    //we will go through each cook and see if he can finish it by the given time(sol)
      //we will go through each time it requires to make the pratas and if its less than the sol, then we will add it to (currP)
    // to create such a loop we will have to create a unconditional loop
    // in the end we will check if the pratas made so far (currP)>=required Pratas(np) 
    //remember that the pratas r cooked parallely
    int currP = 0;
    for (int i = 0; i < cooksRanks.size(); i++)
    {
        int j = 1;
        int r = cooksRanks[i];
        int timeTaken = 0;

        while (true)
        {
            if (timeTaken + j * r <= sol)
            {
                currP++;
                timeTaken += j * r;
                j++;
            }
            else
            {
                break;
            }
        }
        if (currP >= np)
        {
            return true;
        }
    }
    return false;
}


int minimumTimeNeededToCooknpPratas(vector<int>cooksRanks, int np)
{
    int nc=cooksRanks.size();
    //we will be using bianry search on the SearchSpace
    //the start will be 0
    //the end (max time, worst case) will be the time needed by the bad cook with the highest rank(needs more time to cook)
    //the mid(time taken to cook all the required pratas(np)) could be the solution
    int start=0, ans=0;
    int higestRank=*max_element(cooksRanks.begin(), cooksRanks.end()); //r
    //1r+2r+3r+...+nr=r(1+2+3+...+n)=r(n(n+1)/2)
    int end=higestRank*(np*(np+1)/2);
    int mid = start + (end - start) / 2;
    while(start<=end)
    {
        mid = start + (end - start) / 2;
        if(possibleSolution(cooksRanks, np, mid)) //we have a solution but we will try to decrase the time
        //so we have to move left of the searchSpace
        {
            ans=mid;
            end=mid-1;
        }
        else// we coudnt find the required solution becase the time was less
        // so we have to increase the time
        // so we have to move right of our searchSpace
        {
            start=mid+1;
        }
    }
    return ans;
}


int main()
{
    int t;
    cin >> t; // number of test cases
     int np = 0, nc = 0;
    // np = number of paratas
    // nc = number of cooks

    while (t--)
    {
       
        cin >> np >> nc;

        vector<int> cooksRanks;
        while (nc--)
        {
            int x = 0;
            cin >> x;
            cooksRanks.push_back(x);
        }

        // Call the function and print the result for each test case
        cout << minimumTimeNeededToCooknpPratas(cooksRanks, np) << endl;
    }

    return 0;
}
