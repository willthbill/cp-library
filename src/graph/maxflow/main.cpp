// Int is capacity type
template<class Int>
struct MaxFlow{
    // ford fulkerson with dfs and capacity scaling
    // works for directed and undirected
    int N;
	bool hasbeeninitialized = false; // useful when using the reset method
    vector<vector<Int>> capacity; // change this to map if memory problems
    vector<int> par;
    vector<vector<pair<int, Int>>> adjList;
    MaxFlow(){}
    // adjList[i][j] = {node, capacity}
    // might be able to handle selfloops
    MaxFlow(vector<vector<pair<int, Int>>>& _adjList){
		N = (int)_adjList.size();
		capacity = vector<vector<Int>> (N, vector<Int> (N));
		reset(_adjList);
		hasbeeninitialized = true;
    }
	// does not reallocate large memory, n*n (capacity matrix)
	void reset(vector<vector<pair<int,Int>>>& _adjList){
        adjList = _adjList;
        N = (int)adjList.size();
		if(hasbeeninitialized){
			for(int i = 0; i < N; i++){
				for(auto &e : _adjList[i]){
					capacity[i][e.first] = 0;
				}
			}
		}
		for(int i = 0; i < N; i++){
            for(auto &e : _adjList[i]){
                capacity[i][e.first] += e.second;
            }
        }
        for(int i = 0; i < N; i++){
            for(auto& e : _adjList[i]){
                adjList[e.first].push_back({i, 0}); // works for undirected???
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
		Int constrain = -1;
		for(int i = sizeof(maxCapacity) * 8 - 1; i >= 0; i--){
			if((maxCapacity >> i) & 1){
				constrain = 1 << i;
			}
		}
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
