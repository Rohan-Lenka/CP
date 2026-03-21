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
#define vld vector<long double>
#define vstr vector<string>
#define vvi vector<vector<int>>
#define vvll vector<vector<long long>>
#define vvd vector<vector<double>>
#define vvld vector<vector<long double>>
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
#define forik(i, start, limit, k) for(int i = start; i <= limit; i += k)
#define ford(i, start, limit) for(int i = start; i >= limit; i--)
#define fordk(i, start, limit, k) for(int i = start; i >= limit; i -= k)
#define vmax(v) *max_element(v.begin(), v.end())
#define vmin(v) *min_element(v.begin(), v.end())
#define _log2(x) (64 - __builtin_clzll(x) - 1)

const ll MOD = 998244353;
ll modadd(ll a, ll b, ll m = MOD) { return ((a % m + b % m) % m + m) % m; }
ll modmul(ll a, ll b, ll m = MOD) { return ((a % m * b % m) % m + m) % m; }
ll modsub(ll a, ll b, ll m = MOD) { return ((a % m - b % m) % m + m) % m; }
ll modexpo(ll a, ll p, ll m = MOD) { ll r = 1; for (a %= m; p; p >>= 1, a = (a * a) % m) if (p & 1) r = (r * a) % m; return r; }
ll modinv(ll a, ll m = MOD) { return modexpo(((a % m) + m) % m, m - 2, m); }
ll moddiv(ll a, ll b, ll m = MOD) { return modmul(a, modinv(b, m), m); }

inline long long myPow(long long a, long long b, long long m=1){long long r=1;while(b){if(b&1)r=(m==1?r*a:r*a%m);a=(m==1?a*a:a*a%m);b>>=1;}return r;}

inline void yes() { cout << "YES" << '\n'; }
inline void no() { cout << "NO" << '\n'; }

template <typename T> inline void printArray(const vector<T> &arr) { cout << '[' << ' '; for(const T& el : arr) cout << el << ' '; cout << ']'; cout << '\n'; }

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    bool testsExist = true;
    int tt = 1;
    if(testsExist) cin >> tt;
    while(tt--) {
        
    }
    return 0;
}