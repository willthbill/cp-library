// https://open.kattis.com/problems/minspantree | this code is for this problem
#include<bits/stdc++.h>
using namespace std;
template<class Int=long long>
struct MST{
	bool isForest; // if isForest then numberOfTreesInForest > 1 else it is 1 (or 0 is no nodes)
	vector<int> sumOnTrees; // length is numberOfTreesInForest
	Int totalSum;
	int numberOfTreesInForest;
	struct Edge{
		Int w;
		int from, to;
	};
	vector<vector<Edge>> treeEdges; // length is numberOfTreesInForest
	vector<vector<int>> nodesInTrees; // length is numberOfTreesInForest
	struct Comparator{
		bool operator()(Edge& a, Edge& b){
			return a.w > b.w;
		}
	};
	MST(vector<vector<pair<int,Int>>>& adj) {
		int N = (int) adj.size();
		vector<bool> v (N);
		totalSum = 0;
		numberOfTreesInForest = 0;
		for(int i = 0; i < N; i++){
			if(!v[i]){
				priority_queue<Edge, vector<Edge>,Comparator> pq;
				pq.push({0, -1, i});
				int idx = numberOfTreesInForest;
				numberOfTreesInForest++;
				sumOnTrees.push_back(0);
				treeEdges.push_back({});
				nodesInTrees.push_back({});
				while(!pq.empty()){
					Edge curr = pq.top(); pq.pop();
					if(v[curr.to]) continue;
					v[curr.to] = true;
					sumOnTrees[idx] += curr.w;
					treeEdges[idx].push_back(curr);
					nodesInTrees[idx].push_back(curr.to);
					for(auto& edge : adj[curr.to]){
						if(!v[edge.first]){
							pq.push({edge.second, curr.to, edge.first});
						}
					}
				}
				totalSum += sumOnTrees[idx];
			}
		}
		isForest = numberOfTreesInForest > 1;
	}
};
int main(){
	int n, m;
	while(1){
		cin >> n >> m;
		if(n == 0 && m == 0) break;
		vector<vector<pair<int,int>>> adj (n);
		for(int i = 0; i < m; i++){
			int a, b, c; cin >> a >> b >> c;
			c += 20000;
			adj[a].push_back({b, c});
			adj[b].push_back({a, c});
		}
		MST<int> mst (adj);
		if(mst.isForest){
			cout << "Impossible" << endl;
			continue;
		}else{
			cout << mst.totalSum - 20000 * (n - 1) << endl;
			vector<pair<int,int>> edges (mst.treeEdges[0].size());
			for(int i = 0; i < edges.size(); i++){
				edges[i] = {
					min(mst.treeEdges[0][i].from, mst.treeEdges[0][i].to),
					max(mst.treeEdges[0][i].from, mst.treeEdges[0][i].to)
				};
			}
			sort(edges.begin(), edges.end());
			for(auto& e : edges){
				if(e.first != -1) cout << e.first << " " << e.second << endl;
			}
		}
	}
}
