#include <bits/stdc++.h>
using namespace std;
#define ll long long

// 1) Modulo and subtraction
/*
    Always do this when you are performing modulo and also doing subtraction
    example -> 
    ll a = myPow(n, k1, MOD); ll b = myPow(n, k2, MOD);
    if u are doing ll c = (a - b) % MOD; then this can be wrong when a < b, i.e negative ans
    as by doing % MOD gives u remainder, ll a can be a lower remainder while ll b be a higher one
    so to avoid this always do -> 
    ll c = (a - b + MOD) % MOD    
*/

// 2) FERMAT'S LITTLE THEORM FOR CP -> 
/*
    (a / b) % MOD != (a % MOD / b % MOD) coz division itself is invalid in modular arithmatic 
    here we have to do -> (a * modInverseOfB) % MOD 
    where modInverseOfB = binary_exponentiation(b, MOD - 2, MOD)
    therefore -> (a / b) % MOD = ((a % MOD) * binary_exponentiation(b, MOD - 2, MOD)) % MOD
    This is used in many CP problems involving number theory, maths, combinatorics, etc
    NOTE -> MOD must always be a PRIME NUMBER for this to work like MOD = 1e9 + 7, 998244353, etc 
*/

// 3) Legendre's Formula
/*
    finds the highest power of a prime that divides n! 
    formula -> highest_power(n, p) = (n/p) + (n/p^2) + (n/p^3) + ......
    explanation -> https://codeforces.com/topic/122957/en1
*/
long long legendre(long long n, long long p) {
    long long cnt = 0;
    while(n > 0) {
        cnt += n / p;
        n /= p;
    }
    return cnt;
}

// 4) Bertrand's postulate
/*
    For each positive integer x there is a prime p, inside the interval [x,2x]
*/

// 5) Euclidean algorithm 
int findGCD(int a, int b) {
    while(a > 0 && b > 0) {
        if(a > b) a = a % b;
        else b = b % a;
    }
    if(!a) return b;
    return a;
    // TC = O(log(min(a, b)))
    // SC = O(1)
}

// 6) Bezout identity
/*
    for three known integers -> a, b, c if c == gcd(a, b) then there exists
    a pair of intergers -> x, y such that ax + by = c.
    Basically => ax + by = gcd(a, b).
    x, y are called bezout coefficients.
*/

// 7) Extended Euclidean algorithm
/*
    Used to solve the bezout identity i.e the eq -> ax + by = gcd(a, b)
    explanation -> https://www.geeksforgeeks.org/dsa/euclidean-algorithms-basic-and-extended/ 
*/
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
// returns {gcd, x, y}
// TC = o(min(a, b)) (same as euclid algo)

// 8) Chinese Remainder Theorm
/*
    Used to solve a system of linear congruences i.e ->
    x = r1 (mod m1)
    x = r2 (mod m2)
    ......
    x = rk (mod mk)
    NOTE -> There is a solution iff gcd(mi, mj) divides ai - aj for all pairs of i, j such that i != j
    explanation -> https://codeforces.com/blog/entry/61290
*/
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
// solves x ≡ r[i] (mod m[i]) for all i
// returns {x, lcm} such that x is the unique solution mod lcm
// for a particular system of linear congruences, if the final ans is {x, lcm} other solutions are 
// -> x +- k * lcm i.e x, x+2*lcm, x+3*lcm, etc 
// returns {-1, -1} if no solution exists

// 9) Linear Diophantine Equations 
/*
    If there are n constants a1, a2, a3,...an & a relation ->
    a1x1 + a2x2 + a3x3 + ... anxn = K where a1, a2, a3,...an & K are integers,
    and x1, x2, x3,...xn can be any integer, this is possible iff ->
    G = gcd(a1, a2, a3,...an) & K mod(G) == 0 i.e K is divisible by G. 
    This is basically an extension of bezout identity
*/
// The below function finds the base values of all xs 
// base values means one soln for the eq
// returns true if the eq satisfies and populates the vector x 
// else return false  
bool solve_lde(vector<ll> &a, ll K, vector<ll> &x) {
    int n = a.size();
    if(n == 0) return false;
    vector<ll> u(n), v(n);
    ll curr_g = a[0];
    for(int i = 1; i < n; ++i) {
        auto [next_g, ui, vi] = egcd(curr_g, a[i]);
        u[i] = ui;
        v[i] = vi;
        curr_g = next_g;
    }
    if(K % curr_g != 0) {
        return false;
    }
    x.assign(n, 0);
    ll running_scale = K / curr_g;
    for(int i = n - 1; i > 0; --i) {
        x[i] = v[i] * running_scale;
        running_scale *= u[i]; 
    }
    x[0] = running_scale;
    return true;
}
// TC = O(n * log(max(ai)) & SC = O(n)

// 10) Linear Diophantine Equation with 2 vars
/*
    src -> https://codeforces.com/topic/85512/en4
    Eq is -> ax + by = k
    Mainly 2 types of qs are IMP
    i) General eq to find all solutions 
    ii) Given a range for x and y, find no. of solutions 
*/
// i) 
/*
    General eq is ->
    x = x0 + t * (b / g)
    y = y0 - t * (a / g)
    where x0, y0 are base solutions, g = gcd(a, b), t is any arbitary integer
    NOTE -> Base solution can be found using the above code
*/
// ii) 
/*
    code -> 
*/
ll fd(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); }
ll cd(ll a, ll b) { return a / b + ((a ^ b) >= 0 && a % b); }
void upd(ll &L, ll &R, ll mn, ll mx, ll v, ll b) {
    ll mn_k = (v > 0) ? cd(mn - b, v) : cd(mx - b, v);
    ll mx_k = (v > 0) ? fd(mx - b, v) : fd(mn - b, v);
    L = max(L, mn_k);
    R = min(R, mx_k);
}
ll count_sols(ll a, ll b, ll c, ll mx, ll Mx, ll my, ll My) {
    if(!a && !b) return (c == 0) ? (Mx - mx + 1) * (My - my + 1) : 0;
    if(!a) return (c % b == 0 && my <= c / b && c / b <= My) ? Mx - mx + 1 : 0;
    if(!b) return (c % a == 0 && mx <= c / a && c / a <= Mx) ? My - my + 1 : 0;
    auto [g, x, y] = egcd(abs(a), abs(b));
    if (c % g) return 0;
    x *= c / g;
    y *= c / g;
    if(a < 0) x = -x;
    if(b < 0) y = -y;
    ll L = -2e18, R = 2e18;
    upd(L, R, mx, Mx, b / g, x);
    upd(L, R, my, My, -a / g, y);
    return max(0LL, R - L + 1);
}
// mx means min_x, Mx means max_x
// my means min_y, My means max_y
// TC = O(log(min(|a|,|b|))) & SC = O(1)

int main() {
    
    return 0;
}