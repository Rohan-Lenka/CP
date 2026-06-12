#include <bits/stdc++.h>
using namespace std;

// 1) chck whether 2 ranges intersect with each other
bool inline intersect(int l1, int r1, int l2, int r2) {
    return r2 >= l1 && r1 >= l2;
}

// 2) Coordinate Compression
vector<int> cc; 
void build(vector<int> &a) {
    cc = a;
    sort(cc.begin(), cc.end());
    cc.erase(unique(cc.begin(), cc.end()), cc.end());
}
int get_cc(int u) {
    auto it = lower_bound(cc.begin(), cc.end(), u);
    if(it == cc.end() || *it != u) {
        cerr << "u was not in array a !" << '\n';
        return -1;
    }
    return int(it - cc.begin());
}

int main() {
    
    return 0;
}