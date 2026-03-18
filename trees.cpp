#include <bits/stdc++.h>
using namespace std;

// binary lifting | kth ancestor of a node -> 
class TreeAncestor {
private:
    int LOG = 20;
    vector<vector<int>> up;
public:
    TreeAncestor(int n, vector<int>& parent) {
        // NOTE -> Here the parent of the root node should always be -1  
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
class LCA {
    private:
    int n;
    int LOG;
    vector<vector<int>> up;
    vector<int> depth;
    vector<vector<int>> adj;
    
    void dfs(int node, int parent) {
        up[node][0] = parent;
        
        for(int j = 1; j <= LOG; j++) {
            if(up[node][j - 1] != -1)
            up[node][j] = up[up[node][j - 1]][j - 1];
            else
            up[node][j] = -1;
        }
        
        for(auto &child : adj[node]) {
            depth[child] = depth[node] + 1;
            dfs(child, node);
        }
    }
    
    public:
    LCA(int n, vector<int> &parent) {
        // NOTE -> Here the parent of the root node should always be -1  
        this->n = n;
        LOG = 20;

        up.assign(n, vector<int>(LOG + 1, -1));
        depth.assign(n, 0);
        adj.assign(n, vector<int>());

        int root = -1;

        for(int i = 0; i < n; i++) {
            if(parent[i] == -1) {
                root = i;
            } else {
                adj[parent[i]].push_back(i);
            }
        }

        dfs(root, -1);
    }

    int getLCA(int u, int v) {
        if(depth[u] < depth[v])
            swap(u, v);

        int diff = depth[u] - depth[v];
        for(int j = 0; j <= LOG; j++) {
            if(diff & (1 << j))
                u = up[u][j];
        }

        if(u == v) return u;

        for(int j = LOG; j >= 0; j--) {
            if(up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
            }
        }

        return up[u][0];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    return 0;
}