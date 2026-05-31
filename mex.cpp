#include <bits/stdc++.h>
using namespace std;

/*
    TIP: Think of 0, 1, 2 in some of the mex problems
*/

// 1) Find mex 
int findMex(vector<int> &a) {
    int n = a.size(), mex = 0;
    vector<bool> f(n + 1, false);
    for(int &e : a) if(e <= n) f[e] = true;
    while(f[mex]) ++mex; 
    return mex;
}

// 2) Handle range queries and point updates for mex
class Mex {
private:
    int n;
    vector<int> a, freq;
    set<int> missing;
public:
    Mex(const vector<int>& arr) {
        a = arr;
        n = a.size();
        freq.assign(n + 2, 0);
        for(int i = 0; i <= n + 1; i++) {
            missing.insert(i);
        }
        for(int x : a) {
            if(0 <= x && x <= n + 1) {
                freq[x]++;
                missing.erase(x);
            }
        }
    }
    int getMex() {
        return *missing.begin();
    }
    void update(int idx, int val) {
        int old = a[idx];
        if(0 <= old && old <= n + 1) {
            freq[old]--;
            if(freq[old] == 0) {
                missing.insert(old);
            }
        }
        if(0 <= val && val <= n + 1) {
            if(freq[val] == 0) {
                missing.erase(val);
            }
            freq[val]++;
        }
        a[idx] = val;
    }
};

int main() {
    
    return 0;
}