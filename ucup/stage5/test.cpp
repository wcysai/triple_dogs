#include <bits/stdc++.h>
#define pb push_back
#define _for(i, a, b)  for (int i = (a); i <= (b); i ++ )
#define _all(i, a, b)  for (int i = (a); i >= (b); i -- )
using namespace std;
const int N = 2e5 + 5;
int n, ans, a[N];
map<int, int> f[N], g[N];
vector<int> G[N];
int Dfs(int u, int fa) {
	if (g[u][fa])  return g[u][fa];
	int & T = g[u][fa];
	T = a[u];
	for (int v : G[u])  if (v != fa)  T = max(T, Dfs(v, u) + a[u]);
	return T;
}
int dfs(int u, int fa) {
	if (f[u][fa])  return f[u][fa];  // 记忆化 
	int & F = f[u][fa];
	F = 0;
	int tmp[2] = {0, 0};
	for (int v : G[u])  if (v != fa) {
		F = max(F, dfs(v, u));
		int t = Dfs(v, u);
		if (t > tmp[0])  tmp[1] = tmp[0], tmp[0] = t;
		else if (t > tmp[1])  tmp[1] = t;
	}
	F = max(F, tmp[0] + tmp[1] + a[u]);
	return F;
}
signed main() {
	ios :: sync_with_stdio(false), cin.tie(0), cout.tie(0);
	memset(f, 0, sizeof(f));
	memset(g, 0, sizeof(g));
	cin >> n;
	_for (i, 1, n)  cin >> a[i];
	int x, y;
	_for (i, 2, n)  cin >> x >> y, G[x].pb(y), G[y].pb(x);
	// 1. 两条独立的路径 
	_for (i, 1, n)  for (int v : G[i])
		ans = max(ans, dfs(v, i) + dfs(i, v));  // 把树分为两个部分：v的子树 和 v的子树以外 
	// 2. 有一个交点 
	_for (i, 1, n) {  // 枚举交点 
		vector<int> temp;
		_for (i, 1, 4)  temp.pb(0);
		for (int v : G[i])
		for (int v : G[i])  temp.pb(Dfs(v, i));
		sort(temp.begin(), temp.end());
		reverse(temp.begin(), temp.end());
		ans = max(ans, temp[0] + temp[1] + temp[2] + temp[3]);
	}
	cout << ans << endl;
	return 0;
}
