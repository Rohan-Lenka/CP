#include <bits/stdc++.h>
using namespace std;

// 1) Binary lifting | kth ancestor of a node -> 
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

// 2) LCA 
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

// 3) Diameter of tree
// Tree should be 0 based
pair<int, int> dfs(int u, int par, vector<vector<int>> &tree) {
    int ch_d_mx = 0, h_mx1 = 0, h_mx2 = 0;
    int ch_cnt = 0;
    for(auto &v : tree[u]) {
        if(v == par) continue;
        auto [h, ch_d] = dfs(v, u, tree);
        ch_d_mx = max(ch_d_mx, ch_d);
        if(h > h_mx1) {
            h_mx2 = h_mx1;
            h_mx1 = h;
        } else {
            h_mx2 = max(h_mx2, h);
        }
        ch_cnt++;
    }
    if(!ch_cnt) return {0, 0};
    int d_mx = ch_d_mx;
    if(ch_cnt == 1) d_mx = max(d_mx, 1 + h_mx1);
    else d_mx = max(d_mx, 2 + h_mx1 + h_mx2); 
    int h_mx = 1 + h_mx1;
    return {h_mx, d_mx};
}
int findDiameter(vector<vector<int>> &tree) {
    auto [_, diameter] = dfs(0, -1, tree);
    return diameter;
}

// 4) Tree DP
/*
    NOTES ->
    1) Basically there are 2 ways to apply dp on trees -> 
        i) Use dfs to do "try out all possibilities" then memoize it using DP.
        ii) Tree DP which is mentioned bellow.
    2) How is it applied ->
        i) DP must be of the form dp[u][state2][state3]...[state_n] where one state is compulsory that is u.
        ii) dp[u][]...[] means number of required possibilities for SUBTREE ROOTED AT u.
        iii) Run a dfs(post-order traversal) to visit all nodes & make sure that u always 
        perform computation for a node after its children nodes are already visited. 
        iv) Inside the dfs, i.e in the computation part, tabulation DP is basically performed.
        v) When the q involves take/not-take, try to take 2 DPs => dp0 (not-take) & dp1 (take) instead of 
        introducing a new state to the DP to make things easier.
        vi) Pseudo Code -> 
        dfs(u, par, state2, state3, ... state_n) {
            
            // 1) Base case -> initialize vals in the dp assuming only node u and nothing else
            dp[u][state2]...[state_n] = // base case val
            
            for(auto &v : tree[u]) {
                if(par == v) continue;
                
                // 2) Explore children with diff new states 
                dfs(v, u, new_state2, new_state3, ... new_state_n)

                // 3) Declare new dp array to store the after computed vals
                ndp[u][]...[]
                
                // 4) Cross-compute dp vals between children to compute all possibilities for subtree u for all states
                for(st2 = start to end) 
                    for(st3 = start to end) 
                        ......
                            for(st_n = start to end)
                                ndp[u][st2]...[st_n] = ndp[u][st2]...[st_n] + cross_compute(dp[u][st2]...[st_n], dp[v][st2]...[st_n]) 
                    
                // 5) Copy final vals stored in ndp to dp
                dp = ndp
            }

        }
    3) Eg -> LC-3939
*/

// 5) Reroot DP
/*
    NOTES ->
    1) Tips on when to apply reroot DP ->
        i) We have to calculate something for all nodes of the tree.
        ii) The calculation for a node involves both downward paths(within the subtree) and 
        upward paths(outside the subtree, via the node's parent).
    2) CRUX for reroot DP ->
        i) ans[u] = up[u] + down[u]
        ii) for DOWN, simple dfs can be done. 
        iii) for UP, another dfs is done which involves rerooting.
        iv) PARTIAL_ANS -> This is commonly used in reroot calculations. Meaning ->
        Lets say there is a node u with children [c1, c2,..., ck]
        Then partial_ans[u | ci] = ans for u if its edge with ci is cut off = ans for u without the subtree ci 
        v) partial_ans is IMP coz up[ci] = partial_ans[u | ci]
        vi) finding the partial_ans[u | ci] is the most challenging part in reroot DP 
        which involves finding proper relations between u & ci.
        vii) The partial_ans can be propagated through out the dfs to be reused. 
        viii) Eg -> CSES Tree distance I & II   
*/

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    return 0;
}