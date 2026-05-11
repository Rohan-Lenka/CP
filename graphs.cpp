#include <bits/stdc++.h>
using namespace std;

// 1) 0-1 BFS
/*
    - Used when all edge weights are either 0 or 1.
    - Maybe initially the edge weights are not 0/1,
    but can be made 0/1 indirectly due to some statements given in the Q.  
    - Further qs ->
    Can we apply the same trick if our edge weights can only be 0 and x (x >= 0) ? [YES, treat x as 1]
    Can we apply the same trick if our edge weights are x and x+1 (x >= 0) ? [NO]
    Can we apply the same trick if our edge weights are x and y (x,y >= 0) ? [NO]
    - explanation -> https://codeforces.com/blog/entry/22276
*/
vector<int> _01BFS(int n, vector<vector<pair<int, int>>> &adj, int src) {
    const int INF = 1e9;
    vector<int> dist(n + 1, INF);
    dist[src] = 0;
    deque<int> dq;
    dq.push_front(src);
    while(!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        for(auto &[v, wt] : adj[u]) {
            if(dist[u] + wt < dist[v]) {
                dist[v] = dist[u] + wt;
                if(wt == 0) dq.push_front(v);
                else dq.push_back(v);
            }
        }
    }
    return dist;
}


int main() {
    
    return 0;
}