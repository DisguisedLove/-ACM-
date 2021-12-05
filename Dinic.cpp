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

const int N = 1e4 + 10, M = 2e5 + 10;

int e[M], ne[M], f[M], h[M], idx;
int d[N], cur[N], n, m, S, T;

void add(int u, int v, int w) {
	f[idx] = w, e[idx] = v, ne[idx] = h[u], h[u] = idx++;
	f[idx] = 0, e[idx] = u, ne[idx] = h[v], h[v] = idx++;
}

bool bfs() {
	memset(d, -1, sizeof d);

	d[S] = 0; cur[S] = h[S];
	queue<int> q;
	q.push(S);

	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = h[u]; ~i; i = ne[i]) {
			int v = e[i];

			if (d[v] == -1 && f[i]) {
				d[v] = d[u] + 1;
				cur[v] = h[v];
				if (v == T) return true;
				q.push(v);
			}
		}
	}

	return false;
}

int find(int u, int limit) {

	if (u == T) return limit;
	int flow = 0;

	for (int i = cur[u]; ~i && flow < limit; i = ne[i]) {
		cur[u] = i;
		int v = e[i];

		if (d[v] == d[u] + 1 && f[i]) {
			int t = find(v, min(f[i], limit - flow));
			if (!t) d[v] = -1;
			f[i] -= t, f[i ^ 1] += t, flow += t;
		}
	}

	return flow;
}

int dinic() {
	int r = 0, flow;
	while (bfs()) if ((flow = find(S, INF)) > 0) r += flow;
	return r;
}

int main() {
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
#endif
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m >> S >> T;
	memset(h, -1, sizeof h);

	while (m--) {
		int u, v, w;
		cin >> u >> v >> w;
		add(u, v, w);
	}

	cout << dinic() << '\n';

    return 0;
}
