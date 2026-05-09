#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<long long, long long>
#define vb vector<bool>
#define vi vector<int>
#define vll vector<long long>
#define vd vector<double>
#define vstr vector<string>
#define vvi vector<vector<int>>
#define vvll vector<vector<long long>>
#define vvstr vector<vector<string>>
#define vpii vector<pair<int, int>>
#define vpll vector<pair<ll, ll>>
#define add push_back
#define del pop_back
#define sz(x) ((int)(x).size())
#define ff first
#define ss second
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define rrev(x) reverse((x).begin(), (x).end())
#define fori(i, start, limit) for(int i = start; i <= limit; i++)
#define ford(i, start, limit) for(int i = start; i >= limit; i--)

inline long long myPow(long long a, long long b, long long m=1){long long r=1;while(b){if(b&1)r=(m==1?r*a:r*a%m);a=(m==1?a*a:a*a%m);b>>=1;}return r;}
inline void yes() { cout << "YES" << '\n'; }
inline void no() { cout << "NO" << '\n'; }
template <typename T> inline void printArray(const vector<T> &arr) { cout << '[' << ' '; for(const T& el : arr) cout << el << ' '; cout << ']'; cout << '\n'; }

// 1) below codes are for both nCr and nPr

const int MAXN = 100001;
ll mod = 998244353;
ll fact[MAXN], invFact[MAXN];
bool done = false;

void genFactorials() {
    done = true;
    fact[0] = 1;
    invFact[0] = 1;
    for(int i = 1; i < MAXN; i++) {
        fact[i] = (fact[i - 1] * i) % mod;
    }
    invFact[MAXN - 1] = myPow(fact[MAXN - 1], mod - 2, mod);
    ford(i, MAXN - 2, 1) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % mod;
    }
}
ll nCr(ll n, ll r) {
    if(r < 0 || r > n) return 0;
    if(!done) genFactorials();
    return (((fact[n] * invFact[r]) % mod) * invFact[n - r]) % mod;
}
ll nPr(ll n, ll r) {
    if(r < 0 || r > n) return 0;
    if(!done) genFactorials();
    return (fact[n] * invFact[n - r]) % mod;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    return 0;
}