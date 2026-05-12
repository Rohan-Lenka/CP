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

// 2) Lucas therom
/*
    Used to solve nCr % m where n & r are very large.
    2 cases :-
    
    1) m is prime -> Then lucas theorm is applied directly.
    Lucas theorm states that -> For nCr % m if m is prime, then_
    nCr % m = n0Cr0 % m * n1Cr1 % m * n2Cr2 % m .... 
    where ni and ri are digits of n & r in base p i.e
    n = n0 + (n1 * p^1) + (n2 * p^2) + .....  
    r = r0 + (r1 * p^1) + (r2 * p^2) + .....

    2) m is composite -> Then lucas theorm can't be applied directly. To solve_
    Break m into its distinct prime factors -> p1, p2,.... pk
    Let nCr = X, we have ->
    X = a1 (mod p1) where a1 = X % p1
    X = a2 (mod p2) where a2 = X % p2
    ......
    X = ak (mod pk) where ak = X % pk
    1st of all, a1, a2,..... ak can be solved using lucas theorm coz
    ai = X % pi => ai = nCr % pi
    2nd, after we have found all ai, we can stitch all the congruences 
    written above using crt
    
    NOTE -> 
    1) m must be a square-free composite number i.e 
    m = p1 * p2 * .... pk where pi is prime and freq of pi is exactly 1. 
    2) Lucas theorm is widely used for finding binomial coefficients mod p.
    3) If m or primes of m are being constantly used in the nCrLucas, 
    it's better to precompute their fact[] and invFact[] to prevent TLE.
*/
class Lucas {
public:
    vector<int> primes, isPrime;

    Lucas(int lim = 1000000) {
        fastSieve(lim);
    }

    ll modexpo(ll a, ll p, ll m) { 
        ll r = 1; 
        for (a %= m; p; p >>= 1, a = (a * a) % m) 
            if (p & 1) r = (r * a) % m; 
        return r; 
    }
    
    ll modinv(ll a, ll m) { 
        return modexpo(((a % m) + m) % m, m - 2, m); 
    }
    
    ll nCr(ll n, ll r, ll p) {
        if(r < 0 || r > n) return 0;
        if(r == 0 || r == n) return 1;
        if(r > n / 2) r = n - r;
        ll num = 1, den = 1;
        for(ll i = 0; i < r; i++) {
            num = (num * (n - i)) % p;
            den = (den * (i + 1)) % p;
        }
        return (num * modinv(den, p)) % p;
    }

    tuple<ll, ll, ll> egcd(ll a, ll b) {
        ll x = 0, y = 1, u = 1, v = 0;
        while(a != 0) {
            ll q = b / a, r = b % a;
            ll m = x - u * q, n = y - v * q;
            b = a; a = r;
            x = u; y = v;
            u = m; v = n;
        }
        return {b, x, y};
    }

    pair<ll, ll> crt(vector<ll> &r, vector<ll> &m) {
        ll R = r[0], M = m[0];
        for(int i = 1; i < (int)r.size(); i++) {
            ll ri = r[i], mi = m[i];
            auto [g, x, y] = egcd(M, mi);
            if ((ri - R) % g != 0) return {-1, -1};
            ll lcm = M / g * mi;
            R = (R + M * ((ri - R) / g % (mi / g) * x % (mi / g)) % lcm + lcm) % lcm;
            M = lcm;
        }
        return {R, M};
    }
    
    void fastSieve(int n) {
        isPrime.assign(n + 1, true);
        isPrime[0] = false; isPrime[1] = false;
        for(int i = 2; i <= n; i++) {
            if(isPrime[i]) primes.push_back(i);
            for(int p : primes) {
                if(i * p > n) break;
                isPrime[i * p] = false;
                if(i % p == 0) break;
            }
        }
    }

    ll lucas(ll n, ll r, ll p) {
        if(r == 0) return 1;
        return (lucas(n / p, r / p, p) * nCr(n % p, r % p, p)) % p;
    }

    vector<ll> getPrimeFactors(ll n) {
        vector<ll> pf;
        for(auto &p : primes) {
            if(1LL * p * p > n) break;
            if(n % p == 0) {
                pf.push_back(p);
                while(n % p == 0) n /= p;
            }
        }
        if(n > 1) pf.push_back(n);
        return pf;
    }

    ll nCrLucas(ll n, ll r, ll m) {
        if(isPrime[m]) return lucas(n, r, m);
        vector<ll> mods = getPrimeFactors(m), rems;
        for(auto &p : mods) rems.push_back(lucas(n, r, p));
        auto [ans, lcm] = crt(rems, mods);
        return ans;
    }
};
// Each nCrLucas query TC = O((no. of primes upto sqrt(m)) + (Pmax * logn))
// where Pmax is the largest prime factor of m

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    return 0;
}