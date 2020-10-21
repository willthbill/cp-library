template<class Int=long long>
struct Dijkstra{
    // could add support for number of shortest paths and so on...
    // 0-indexed nodes
    int N;
    vector<vector<pair<int, Int>>> adj;
    vector<Int> dist; // distance to node, -2 if not visited
    vector<int> prev; // previous node, -1 if no previous node, -2 if not visited
    Dijkstra(){}
    Dijkstra(vector<vector<pair<int, Int>>>& _adj){
        adj = _adj;
        N = (int)adj.size();
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
        q.push({0, start, -1});
        dist = vector<Int> (N, -2);
        prev = vector<int> (N, -2);
        while(!q.empty()){
            Qitem curr = q.top(); q.pop();
            if(dist[curr.node] != -2) continue;
            dist[curr.node] = curr.dist;
            prev[curr.node] = curr.prev;
            for(auto& edge : adj[curr.node]){
                if(dist[edge.first] == -2){
                    q.push({curr.dist + edge.second, edge.first, curr.node});
                }
            }
        }
        return dist;
    }
};
