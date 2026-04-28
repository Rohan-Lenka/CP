#include <bits/stdc++.h>
using namespace std;

class DSU {

public:
    vector<int> par, sz;
    DSU(int v) {
        sz.resize(v);
        par.resize(v);
        for(int i = 0; i < v; i++) {
            sz[i] = 1;
            par[i] = i;
        }
    }

    int findPar(int u) {
        if(par[u] == u)
            return u;
        return par[u] = findPar(par[u]);
    }

    void unionBySize(int u, int v) {
        int UP_u = findPar(u);
        int UP_v = findPar(v);
        if(UP_u == UP_v)
            return;
        if(sz[UP_u] < sz[UP_v]) {
            par[UP_u] = UP_v;
            sz[UP_v] += sz[UP_u];
        } else {
            par[UP_v] = UP_u;
            sz[UP_u] += sz[UP_v];
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    return 0;
}