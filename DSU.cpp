#include <bits/stdc++.h>
using namespace std;

class DSU {

public:
    vector<int> parent, Size;
    DSU(int v) {
        Size.resize(v);
        parent.resize(v);
        for (int i = 0; i < v; i++) {
            Size[i] = 1;
            parent[i] = i;
        }
    }

    int findPar(int u) {
        if (parent[u] == u)
            return u;
        return parent[u] = findPar(parent[u]);
    }

    void unionBySize(int u, int v) {
        int UP_u = findPar(u);
        int UP_v = findPar(v);
        if (UP_u == UP_v)
            return;
        if (Size[UP_u] < Size[UP_v]) {
            parent[UP_u] = UP_v;
            Size[UP_v] += Size[UP_u];
        } else {
            parent[UP_v] = UP_u;
            Size[UP_u] += Size[UP_v];
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    return 0;
}