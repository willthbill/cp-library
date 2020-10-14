// https://www.hackerearth.com/practice/algorithms/graphs/maximum-flow/practice-problems/algorithm/find-the-flow/
#include<bits/stdc++.h>
using namespace std;
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
int main(){
    int N = 26;
    int E; cin >> E;
    vector<vector<pair<int,int>>> adj (N);
    for(int i = 0; i < E; i++){
        char a, b; int c; cin >> a >> b >> c; a-='A', b-='A';
        adj[a].push_back({b,c});
    }
    MaxFlow<int> mf (adj);
    cout << mf.maxFlow('S' - 'A', 'T' - 'A') << endl;
}
