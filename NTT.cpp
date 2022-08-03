#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

const int g = 3, mod = 998244353, N = 1e6 + 10;
#define LOCAL

ll powmod(ll a, ll b, ll mod) {ll res=1;a%=mod;
assert(b>=0);for(;b;b>>=1){if(b&1)res=res*a%mod;
a=a*a%mod;};return res;}
ll gcd(ll a, ll b) {return b?gcd(b, a%b):a;}
// head 

int rev[N], bit, tot;
ll f[N], invf[N];

struct cmp {

    bool operator()(vector<ll>&a, vector<ll>& b) const {
        return a.size() > b.size();
    }
};

priority_queue<vector<ll>, vector<vector<ll>>, cmp> q;

void init(int n) {
    f[0] = 1;
    for (int i = 1; i <= n; i++) f[i] = f[i - 1] * i % mod;
    invf[n] = powmod(f[n], mod - 2, mod);
    for (int i = n - 1; i >= 0; i--) invf[i] = invf[i + 1] * (i + 1) % mod;
}

ll c(ll a, ll b) {
    if (a < 0 || b < 0 || a < b) return 0;
    return f[a] * invf[b] % mod * invf[a - b] % mod;
}

void ntt(vector<ll>& a, int inv) {
    for (int i = 0; i < tot; i++)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);

    for (int mid = 1; mid < tot; mid <<= 1) {
        ll wk = powmod(g, (mod - 1) / (2 * mid), mod);
        if (inv == -1) wk = powmod(wk, mod - 2, mod);
        for (int i = 0; i < tot; i += mid * 2) {
            ll w = 1;
            for (int j = 0; j < mid; j++, w = w * wk % mod) {
                ll x = a[i + j], y = w * a[i + j + mid] % mod;
                a[i + j] = (x + y) % mod, a[i + j + mid] = (x - y + mod) % mod;
            }
        }
    }
}

int main() {
#ifdef LOCAL
    //freopen("in.txt", "r", stdin);
#endif
    
    init(1e6);

    int tt;
    scanf("%d", &tt);
    while (tt--) {
        int n, k;
        scanf("%d%d", &n, &k);
        vector<ll> a(n + 1), vis(n + 1, 0);
        for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
        vector<int> sz;
        for (int i = 1; i <= n; i++) {
            if (vis[i]) continue;
            vis[i] = 1;
            int cnt = 1;
            int t = a[i];
            while (t != i) {
                vis[t] = 1;
                ++cnt;
                t = a[t];
            }

            sz.push_back(cnt);
        }

        function<vector<ll>(int, int)> solve=[&](int l, int r) {
            if (l == r) {
                vector<ll> a(sz[l]);
                int n = (int)a.size();
                for (int i = 0; i < min(n, k + 1); i++) 
                    a[i] = (c(n - i - 1, i - 1) + c(n - i, i)) % mod;
                return a;
            } else {
                int mid = (l + r) / 2;
                vector<ll> a = solve(l, mid), b = solve(mid + 1, r);
                int n = (int)a.size() - 1, m = (int)b.size() - 1;

                bit = 0;
                while ((1 << bit) < min(k + 1, n + m + 1)) ++bit;
                tot = 1 << bit;
                a.resize(tot), b.resize(tot);

                for (int i = 1; i < tot; i++)
                    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
                ntt(a, 1); ntt(b, 1);
                for (int i = 0; i < tot; i++) a[i] = a[i] * b[i] % mod;
                ntt(a, -1);
                a.resize(min(k + 1, n + m + 1));
                ll inv = powmod(tot, mod - 2, mod);
                for (int i = 0; i < a.size(); i++) a[i] = a[i] * inv % mod;
                return a;
            }
        };

        vector<ll> ans = solve(0, (int)sz.size() - 1);
        if (k >= (int)ans.size()) puts("0");
        else printf("%lld\n", ans[k]);
    }
    return 0;
}
