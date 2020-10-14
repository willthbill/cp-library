// https://cses.fi/problemset/task/1694
#include<bits/stdc++.h>
using namespace std;
#define int long long
// Con is the edges container type, Int is capacity type, size is type of N, Int and size cannot be unsigned
template<class Int>
struct MaxFlow{
    // ford fulkerson with dfs and capacity scaling
    // works for directed and undirected
    int N;
    vector<vector<Int>> capacity;
    vector<int> par;
    vector<vector<pair<int, Int>>> adjList;
    MaxFlow(){}
    // adjList[i][j] = {node, capacity}
    // might be able to handle selfloops
    MaxFlow(vector<vector<pair<int, Int>>>& adjList){
        N = adjList.size();
        capacity = vector<vector<Int>> (N, vector<Int> (N));
        this->adjList = adjList;
        for(int i = 0; i < N; i++){
            for(auto &e : adjList[i]){
                capacity[i][e.first] += e.second;
            }
        }
        for(int i = 0; i < N; i++){
            for(auto& e : adjList[i]){
                this->adjList[e.first].push_back({i, 0}); // works for undirected???
            }
        }
    }
    Int getMinFlow(int node, int p, Int constrain, int t){
        par[node] = p;
        for(auto& e : adjList[node]){
            int nb = e.first;
            if(nb == p || par[nb] != -1) continue;
            if(capacity[node][nb] >= constrain){
                if(nb == t) {
                    par[nb] = node;
                    return capacity[node][nb];
                }
                Int temp = getMinFlow(nb, node, constrain, t);
                if(temp > 0) return min(temp, capacity[node][nb]);
            }
        }
        return 0;
    }
    // s cannot be t
    Int maxFlow(int s, int t){
        Int flow = 0;
        Int maxCapacity = 0;
        for(int i = 0; i < N; i++) for(int j = 0; j < N; j++)
            maxCapacity = max(capacity[i][j], maxCapacity);
        Int constrain = 1 << (sizeof(maxCapacity) * 8 - 1 - __builtin_clzll(maxCapacity)); // test this
        while(constrain){
            Int minFlow = -1;
            while(1){
                par = vector<int> (N, -1);
                minFlow = getMinFlow(s, -2, constrain, t);
                if(minFlow == 0) break;
                int node = t;
                while(node != s){
                    capacity[par[node]][node] -= minFlow;
                    capacity[node][par[node]] += minFlow;
                    node = par[node];
                }
                flow += minFlow;
            }
            constrain >>= 1;
        }
        return flow;
    }
};
signed main(){
    int N, M; cin >> N >> M;
    vector<vector<pair<int,int>>> adj (N);
    int s = 0, t = N - 1;
    for(int i = 0; i < M; i++){
        int a, b, c; cin >> a >> b >> c; a--, b--;
        adj[a].push_back({b, c});
    }
    MaxFlow<int> mf;
    mf = MaxFlow<int>(adj);
    cout << mf.maxFlow(s, t) << endl;
}
