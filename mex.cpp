#include <bits/stdc++.h>
using namespace std;

/*
    TIP: Always think of 0, 1, 2 in most of the mex problems
*/

int findMex(vector<int> &a) {
    int n = a.size(), mex = 0;
    vector<bool> f(n + 1, false);
    for(int &e : a) if(e <= n) f[e] = true;
    while(f[mex]) ++mex; 
    return mex;
}

int main() {
    
    return 0;
}