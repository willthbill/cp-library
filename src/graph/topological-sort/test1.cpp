#include<bits/stdc++.h>
using namespace std;
struct TopoSort{ // must be a DAG, O(n) complexity
	vector<vector<int>> adj;
	TopoSort(){}
	TopoSort(vector<vector<int>>& _adj){adj = _adj; res = vector<int> (adj.size(), -1);}
	int idx;
	vector<int> res;
	void dfs(int node){
		if(res[node] != -1) return;
		for(auto& e : adj[node]) dfs(e);
		res[node] = idx--;
	}
	vector<int>& run(){
		int n = (int)adj.size();
		idx = n - 1;
		for(int i = 0; i < n; i++){
			if(res[i] == -1) dfs(i);
		}
		return res;
	}
};
int N,M;
vector<int> state;
vector<vector<int>> adj;
vector<int> idxs;
int idx = 0;
bool flag = 0;
void dfs1(int node){
    if(state[node] == 2) return;
    if(state[node] == 1){
        flag = 1;
        return;
    }
    state[node] = 1;
    for(auto nb : adj[node]) dfs1(nb);
    state[node] = 2;
}
void solve(){
    cin >> N >> M;
    vector<pair<int, int>> edges (M);
    vector<int> isdirected(M);
    adj = vector<vector<int>> (N);
    state = vector<int> (N);
    flag = 0;
    idx = N - 1;
    for(int i = 0; i < M; i++){
        int t,x,y; cin >> t >> x >> y; x--; y--;
        if(t){
            adj[x].push_back(y);
        }
        edges[i] = {x,y};
        isdirected[i] = t;
    }
    for(int i = 0; i < N; i++){
        if(state[i] == 0) dfs1(i);
    }
    if(flag){
        cout << "NO" << endl;
    }else{
		TopoSort topo;
		topo = TopoSort(adj);
		auto idxs = topo.run();
        cout << "YES" << endl;
        for(int i = 0; i < M; i++){
            if(!isdirected[i]){
                int a = edges[i].first;
                int b = edges[i].second;
                if(idxs[a] < idxs[b]){
                    cout << a + 1 << " " << b + 1 << endl;
                }else{
                    cout << b + 1 << " " << a + 1 << endl;
                }
            }else{
                cout << edges[i].first + 1 << " " << edges[i].second + 1 << endl;
            }
        }
    }
}
int main(){ 
    int T; cin >> T;
    while(T--) solve();
}
