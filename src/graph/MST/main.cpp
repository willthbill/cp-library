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

