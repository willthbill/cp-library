class Node {
public:
    int left, length;
    Node* link;
    map<int, Node*> adj;

    Node (int left, int length, Node* link) : left(left), length(length), link(link) {}

    ~Node() {
        delete link;
        for (auto it = adj.begin(); it != adj.end(); it++) {
            delete it->second;
        }
    }
};

class ActivePoint {
public:
    Node* node;
    int edge;
    int length;

    ActivePoint(Node* node, int edge, int length) : node(node), edge(edge), length(length) {}
};

Node* root = new Node(-1, -1, nullptr);

function<void(string, int)> build = [&] (string s, int n) {
	// ----------------------------------------------
  // resources:
  // - https://codeforces.com/blog/entry/16780
  // - https://www.youtube.com/watch?v=aPRqocoBsFQ
  // ----------------------------------------------

    ActivePoint active = Active_Point(root, -1, 0);

    const int INF = 1e9;
    for (int end = 0; end < n; end++) {
        active.length++;
        Node* last = nullptr;
        while (active.length > 0) {
            // update the active point
            // the edge might be too short
            while (active.node->adj[s[end+1-active.length]] != nullptr && 
                   active.length > active.node->adj[s[end+1-active.length]]->length
            ) {
                active.node = active.node->adj[s[end+1-active.length]];
                active.length -= active.node->length;
            }
            // find the active edge
            // find the next node where data is
            // and find the active letter
            active.edge = end+1-active.length;
            Node* nei = active.node->adj[s[active.edge]];
            int active_letter = nei == nullptr ? 0 : s[nei->left+active.length-1];
            // there are 3 scenarios
            // 1: there is no next node
            // 2: the active letter is already equal to the letter we try to insert
            // 3: the active letter is not equal to the letter we try to insert
            if (nei == nullptr) {
                // in this case we create a node
                // and thereby an edge with the letter
                // we also handle suffix link here
                active.node->adj[s[active.edge]] = new Node(end+1-active.length, INF, root);
                if (last != nullptr) last->link = active.node;
                last = nullptr;
            } else if (s[end] == active_letter) {
                // in this case we do nothing but handle suffix link
                // this is a "show stopper"
                if (last != nullptr) last->link = active.node;
                break;
            } else {
                // in this case we split the egde
                // creating two branches
                // 1 - is the rest of the original edge
                // 2 - is the letter we try to insert
                // we also handle suffix link here
                Node* split = new Node(nei->left, active.length-1, root);
                split->adj[s[end]] = new Node(end, INF, root);
                split->adj[active_letter] = nei;
                nei->left += active.length-1;
                nei->length -= active.length-1;
                active.node->adj[s[active.edge]] = split;
                if (last != nullptr) last->link = split;
                last = split;
            }
            // if active node is not root
            // we set active node to the node it links to
            if (active.node != root) active.node = active.node->link;
            else active.length--;
        }
    }
};
