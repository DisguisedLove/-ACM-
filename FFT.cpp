#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <string>
#include <cstring>
#include <algorithm>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <ctime>
#include <vector>
#include <fstream>
#include <list>
#include <iomanip>
#include <cassert>
#include <numeric>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

const int INF = 0x3f3f3f3f;
//#define LOCAL

ll powmod(ll a, ll b, ll mod) {ll res=1;a%=mod;
assert(b>=0);for(;b;b>>=1){if(b&1)res=res*a%mod;
a=a*a%mod;};return res;}
ll gcd(ll a, ll b) {return b?gcd(b, a%b):a;}
// head 

const int N = 3e5 + 10;
const double PI = acos(-1);

struct Complex {
	double x, y;

	Complex operator + (const Complex& t) const {
		return {x + t.x, y + t.y};
	}

	Complex operator - (const Complex& t) const {
		return {x - t.x, y - t.y};
	}

	Complex operator * (const Complex& t) const {
		return {x * t.x - y * t.y, x * t.y + y * t.x};
	}
} a[N], b[N];

int rev[N], n, m, tot, bit;

void fft(Complex a[], int inv) {
	for (int i = 0; i < tot; i++)
		if (i < rev[i])
			swap(a[i], a[rev[i]]);

	for (int mid = 1; mid < tot; mid *= 2) {
		auto wk = Complex({cos(PI / mid), inv * sin(PI / mid)});

		for (int i = 0; i < tot; i += mid * 2) {
			Complex w = {1, 0};

			for (int j = 0; j < mid; j++, w = w * wk) {
				auto x = a[i + j], y = w * a[i + j + mid];
				a[i + j] = x + y, a[i + j + mid] = x - y;
			}
		}
	}
}

int main() {
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
#endif
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	for (int i = 0; i <= n; i++) cin >> a[i].x;

	for (int i = 0; i <= m; i++) cin >> b[i].x;

	while ((1 << bit) < n + m + 1) ++bit;
	tot = 1 << bit;


	for (int i = 1; i < tot; i++)
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));

	fft(a, 1); fft(b, 1);

	for (int i = 0; i < tot; i++) a[i] = a[i] * b[i];

	fft(a, -1);
	for (int i = 0; i <= n + m; i++)
		cout << (int)(a[i].x / tot + 0.5) << ' ';
	cout << '\n';
    return 0;
}
