#include <bits/stdc++.h>
using namespace std;

// binary lifting | kth ancestor of a node -> 
class TreeAncestor {
private:
    int LOG = 20;
    vector<vector<int>> up;

public:
    TreeAncestor(int n, vector<int>& parent) {
        up = vector<vector<int>> (n, vector<int> (LOG + 1, -1));
        for(int v = 0; v < n; v++) {
            up[v][0] = parent[v];
        }
        for(int j = 1; j <= LOG; j++) {
            for(int v = 0; v < n; v++) {
                if (up[v][j - 1] != -1)
                    up[v][j] = up[up[v][j - 1]][j - 1];
            }
        }
    }
    
    int getKthAncestor(int node, int k) {
        for(int j = 0; j <= LOG; j++) {
            if(node == -1) break;
            if(k & (1 << j)) {
                node = up[node][j];
            }
        }
        return node;
    }
};


// LCA 


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    return 0;
}