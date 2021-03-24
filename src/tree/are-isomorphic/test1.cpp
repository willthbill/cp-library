#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
template <class T> ll size(const T& x) { return x.size(); }
#define rep(i,a,b) for(ll i = (a); i < (b); ++i)
#define rrep(i,a,b) for(ll i = (a); i > b; --i)
#define iter(it,c) for(auto it = (c).begin(); it != (c).end(); ++it)
#define pb push_back
#define fs first
#define sc second
#define MOD 1000000007
#define MOD2 998244353;
#define INF 1000000000000000000ll
#pragma GCC optimize("Ofast")
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
template <class T> T smod(T a, T b) {
	return (a % b + b) % b;
}
typedef pair<int, vector<int> > node;

vector<vector<int>> construct(string in)
{
	vector<node> tedg;
	int cnt = 0;
	tedg.pb(node(0, vector<int>()));
	int cur = 0;
	for(char c : in)
	{
		if (c == '0')
		{
			cnt++;
			tedg.pb(node(cur, vector<int>()));
			tedg[cur].sc.pb(cnt);
			cur = cnt;
		}
		else
		{
			cur = tedg[cur].fs;
		}
	}
	int n = cnt + 1;
	vector<vector<int>> edg(n);
	for (int i = 0; i < n; i++)
	{
		for (int u : tedg[i].sc)
		{
			edg[i].pb(u);
		}
	}
	return edg;
}
string _assign_canonical_names(int v, vector<vector<int>>& edg)
{
	int n = edg.size();
	if (edg[v].size() == 0)
	{
		return "10";
	}
	vector<string> cur;
	for(int nxt : edg[v])
	{
		cur.pb(_assign_canonical_names(nxt, edg));
	}
	string temp = "";
	sort(cur.rbegin(), cur.rend());
	for(string t : cur)
	{
		temp += t;
	}
	return '1' + temp + '0';
}
bool are_isomorphic(vector<vector<int>>& edg1, vector<vector<int>>& edg2)
{
	return _assign_canonical_names(0, edg1) == _assign_canonical_names(0, edg2);
}

int main()
{
	ll n;
	cin >> n;
	rep(i, 0, n)
	{
		string in1, in2;
		cin >> in1 >> in2;
		vector<vector<int>> tree1 = construct(in1), tree2 = construct(in2);
		if (are_isomorphic(tree1, tree2))
		{
			cout << "same" << endl;
		}
		else
		{
			cout << "different" << endl;
		}
	}
}
