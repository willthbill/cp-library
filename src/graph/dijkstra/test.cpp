// https://cses.fi/problemset/task/1671/
#include<bits/stdc++.h>
using namespace std;

template<class Int=long long>
struct Dijkstra{
    // could add support for number of shortest paths and so on...
    // 0-indexed nodes
    int N;
	Int MX;
    vector<vector<pair<int, Int>>> adj;
    vector<Int> dist; // distance to node, MX if not visited
    vector<int> prev; // previous node, -2 if no previous node, -1 if not visited
    Dijkstra(){}
    Dijkstra(vector<vector<pair<int, Int>>>& _adj, Int _MX){
        adj = _adj;
        N = (int)adj.size();
		MX = _MX;
    }
    struct Qitem{
        Int dist;
        int node, prev;
    };
    struct Comparator{
        bool operator()(Qitem& i1, Qitem& i2){
            return i1.dist > i2.dist;
        }
    };
    vector<Int>& run(int start){ // returned as reference
        priority_queue<Qitem, vector<Qitem>, Comparator> q;
        q.push({0, start, -2});
        dist = vector<Int> (N, MX);
        prev = vector<int> (N, -1);
        while(!q.empty()){
            Qitem curr = q.top(); q.pop();
            if(prev[curr.node] != -1) continue;
            dist[curr.node] = curr.dist;
            prev[curr.node] = curr.prev;
            for(auto& edge : adj[curr.node]){
                if(prev[edge.first] == -1){
                    q.push({curr.dist + edge.second, edge.first, curr.node});
                }
            }
        }
        return dist;
    }
};
int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    vector<vector<pair<int, long long>>> adj (n);
    Dijkstra<> ds;
    for(int i = 0; i < m; i++){
        int a, b, c; cin >> a >> b >> c;
        a--, b--;
        adj[a].push_back({b, c});
    }
    ds = Dijkstra<>(adj, LLONG_MAX);
    vector<long long>& res = ds.run(0);
    for(auto& e : res) cout << e << " ";
    cout << endl;
}
