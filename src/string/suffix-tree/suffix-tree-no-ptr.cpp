int root = 0, id = 1;
const int INF = 1e9;

vector<int> lft;
vector<int> length;
vector<int> link;
vector<map<int, int>> adj;

struct ActivePoint {
    int node;
    int edge;
    int length;
};

int create_node(int l, int len) {
    lft[id] = l;
    length[id] = len;
    return id++;
}

void build(string s, int n) {
    // ----------------------------------------------
    // resources:
    // - https://codeforces.com/blog/entry/16780
    // - https://www.youtube.com/watch?v=aPRqocoBsFQ
    // ----------------------------------------------

    int N = n*30;

    lft.resize(N, 0);
    length.resize(N, INF);
    link.resize(N, 0);
    adj.resize(N);

    ActivePoint active = {root, -1, 0};
    for (int end = 0; end < n; end++) {
        active.length++;
        int last = 0;
        while (active.length > 0) {
            // update the active point
            // the edge might be too short
            while (active.length > length[adj[active.node][s[end+1-active.length]]]) {
                active.node = adj[active.node][s[end+1-active.length]];
                active.length -= length[active.node];
            }
            // find the active edge
            // find the next node where data is
            // and find the active letter
            active.edge = end+1-active.length;
            int& nei = adj[active.node][s[active.edge]];
            int active_letter = s[lft[nei]+active.length-1];
            // there are 3 scenarios
            // 1: there is no next node
            // 2: the active letter is already equal to the letter we try to insert
            // 3: the active letter is not equal to the letter we try to insert
            if (nei == 0) {
                // in this case we create a node
                // and thereby an edge with the letter
                // we also handle suffix link here
                nei = create_node(end+1-active.length, INF);
                link[last] = active.node;
                last = 0;
            } else if (s[end] == active_letter) {
                // in this case we do nothing but handle suffix link
                // this is a "show stopper"
                link[last] = active.node;
                break;
            } else {
                // in this case we split the egde
                // creating two branches
                // 1 - is the rest of the original edge
                // 2 - is the letter we try to insert
                // we also handle suffix link here
                int split = create_node(lft[nei], active.length-1);
                adj[split][s[end]] = create_node(end, INF);
                adj[split][active_letter] = nei;
                lft[nei] += active.length-1;
                length[nei] -= active.length-1;
                nei = split;
                link[last] = split;
                last = split;
            }
            // if active node is not root
            // we set active node to the node it links to
            if (active.node != root) active.node = link[active.node];
            else active.length--;
        }
    }
}
