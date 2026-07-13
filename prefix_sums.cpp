#include <bits/stdc++.h>
using namespace std;

// 1) 2D prefix sums OR prefix sum of matrix 
class MatPref {
public: 
    vector<vector<long long>> pref;
    MatPref(vector<vector<int>> &G) {
        int n = G.size(), m = G[0].size();
        pref.assign(n + 1, vector<long long>(m + 1, 0));
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                pref[i][j] = G[i-1][j-1] 
                        + pref[i-1][j] 
                        + pref[i][j-1] 
                        - pref[i-1][j-1];
            }
        }
    }
    long long query(int r1, int c1, int r2, int c2) {
        r1++; c1++; 
        r2++; c2++;
        return pref[r2][c2] 
        - pref[r1 - 1][c2] 
            - pref[r2][c1 - 1] 
            + pref[r1 - 1][c1 - 1];
    }
};

int main() {
    
    return 0;
}