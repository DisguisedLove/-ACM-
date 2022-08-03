#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef pair<int, int> PII;
typedef long long ll;
typedef double db;
mt19937 mrand(random_device{}()); 
const ll mod=4179340454199820289;
int rnd(int x) { return mrand() % x;}

ll gcd(ll a, ll b) {return b?gcd(b, a%b):a;}
template<class T> 
void chkmin(T&x,T y){x=min(x,y);}
template<class T> 
void chkmax(T&x,T y){x=max(x,y);}
template<class T> 
void add(T&x,T y){x+=y;if(x>=mod)x-=mod;}
template<class T> 
void sub(T&x,T y){x-=y;if(x<0)x+=mod;}
// head 

ll ans, n;

const int N = 1e6 + 10;

int p[N], v[N], tot;
ll f[100];

ll mul(ll a, ll b) {
    ll tmp = 0;
    for (; b; b >>= 1) {
        if (b & 1) add(tmp, a);
        add(a,a);
    }
    return tmp;
}

ll powmod(ll a, ll b) {
    ll tmp = 1;
    while (b) {
        if (b & 1) tmp = mul(tmp, a);
        b >>= 1;
        a = mul(a, a);
    }

    return tmp;
}

void init(int n) {
    for (int i = 2; i <= n; i++) {
        if (v[i] == 0) {
            v[i] = i;
            p[++tot] = i;
        }

        for (int j = 1; j <= tot && p[j] <= n / i; j++) {
            if (v[i] < p[j]) break;
            v[i * p[j]] = p[j];
        }
    }
}

void upd(ll cur, ll hd) {
    cur = n / cur;
    if (cur & 1) cur = mul(cur, (cur + 1) / 2);
    else cur = mul(cur / 2, cur + 1);
    add(ans, mul(hd, cur));
}

void dfs(int i, ll cur, ll hd, bool need) {
    if (need) upd(cur, hd);
    if (i > tot || cur > n) return ;

    if (i < tot && cur <= n / p[i + 1] / p[i + 1]) dfs(i + 1, cur, hd, 0);

    ll tmp = p[i] * 1ll * p[i];
    int k = 2;

    while (tmp <= n / cur) {
        ll fk = f[k];
        ll res = (2 * mod - mul(tmp, fk)) % mod;
        dfs(i + 1, cur * tmp, mul(hd, res), 1);
        if (tmp > (n / cur) / p[i]) break;
        tmp *= p[i];
        ++k;
    }
}

void solve() {
    // to solve a single test case 
    cin >> n;
    ans = 0;
    dfs(1, 1, 1, 1);
    //cout << ans << '\n';
    cout << mul(ans, powmod(n, mod - 2)) << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    init(1e6);

    int tt;
    cin >> tt;
    //tt = 1;
    for (int i = 2; i <= 70; i++) {
        f[i] = powmod(i * (i - 1), mod - 2);
    }

    while (tt--) {
        solve();
    }

    return 0;
}
