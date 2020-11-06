template<class T>
struct Edge {
    int v;
    T flow;
    T capacity;
    int reversed_edge;
};

template<class T>
class Maxflow {
    vector<vector<Edge<T>>> adj;
    int N;
    vector<int> level;
public:
    Maxflow(vector<vector<Edge<T>>> adj, int N) {
        this->adj = adj;
        this->N = N;
        level.resize(N);
    }

    bool BFS(int s, int t) {
        for (int i = 0; i < N; i++)
            level[i] = -1;
        level[s] = 0;

        list<int> q;
        q.push_back(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop_front();

            for (auto i = adj[u].begin(); i != adj[u].end(); i++) {
                Edge<T>& e = *i;
                if (level[e.v] < 0  && e.flow < e.capacity) {
                    level[e.v] = level[u]+1;
                    q.push_back(e.v);
                }
            }
        }

        return (level[t] < 0) ? false : true;
    }

    int sendFlow(int u, int flow, int t, vector<int>& start) {
        if (u == t)
            return flow;

        for (; start[u] < (int)adj[u].size(); start[u]++) {
            Edge<T>& e = adj[u][start[u]];

            if (level[e.v] == level[u]+1 && e.flow < e.capacity) {
                int curr_flow = min(flow, e.capacity-e.flow);
                int temp_flow = sendFlow(e.v, curr_flow, t, start);

                if (temp_flow > 0) {
                    e.flow += temp_flow;
                    adj[e.v][e.reversed_edge].flow -= temp_flow;

                    return temp_flow;
                }
            }
        }

        return 0;
    }

    int dinic_maxflow(int s, int t) {
        if (s == t)
            return -1;

        int total = 0;
        while (BFS(s, t) == true) {
            vector<int> start(N+1);

            while (int flow = sendFlow(s, INT_MAX, t, start))
                total += flow;
        }

        return total;
    }
};

template<class T>
void add_edge(vector<vector<Edge<T>>>& adj, int u, int v, T capacity) {
    Edge<T> a{v, 0, capacity, (int)adj[v].size()};
    Edge<T> b{u, 0, 0, (int)adj[u].size()};
    adj[u].push_back(a);
    adj[v].push_back(b);
}