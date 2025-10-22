#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ADVANCED DP

// 1) bitmask + dp
// for problems like TSP & assign n jobs to n poeple
ll fx1(int job, int mask, vector<vector<ll>> &cost, vector<vector<ll>> &dp, int n) {
    if(job == n) return 0LL;
    if(dp[job][mask] != -1) return dp[job][mask];
    ll mn = LLONG_MAX;
    for(int person = 0; person < n; person++) {
        if((mask & (1 << person))) {
            ll here = fx1(job + 1, (mask ^ (1 << person)), cost, dp, n);
            mn = min(mn, cost[person][job] + here);
        }
    }
    return dp[job][mask] = mn;
}
// TC = O(2^n * n^2)
// SC = O(2^n * n)
// NOTES -> 
// 1) mask in binary -> ith bit -> == 0 means ith person not available & vice versa
// 2) initially mask = (1 << n) - 1 coz all n people should be available 

int main() {
    
    return 0;
}