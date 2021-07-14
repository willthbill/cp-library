class Node {
public:
    int64_t value;
    int x, y;
    Node* left;
    Node* right;
    
    Node(int64_t value, int x, int y, Node* left, Node* right) : value(value), x(x), y(y), left(left), right(right) {}
};

int n;
int N = __builtin_popcount(n) == 1 ? n : (1 << (32-__builtin_clz(n)));

vector<Node*> trees;
vector<int64_t> A(N, 0);

function<void(Node*)> build = [&] (Node* node) {
    if (node->x != node->y) {
        int d = node->x+(node->y-node->x)/2;
        node->left = new Node(0, node->x, d, nullptr, nullptr);
        node->right = new Node(0, d+1, node->y, nullptr, nullptr);
        build(node->left);
        build(node->right);
        node->value = node->left->value+node->right->value;
    } else {
        node->value = A[node->x];
    }
};

function<int64_t(int, int, Node*)> qry = [&] (int a, int b, Node* node) {
    if (node->y < a || b < node->x) return (int64_t)0;
    if (node->x >= a && b >= node->y) return node->value;
    return qry(a, b, node->left)+qry(a, b, node->right);
};

function<void(Node*, int, int64_t)> upd = [&] (Node* node, int idx, int64_t x) {
    if (node->left != nullptr && node->left->y < idx) {
        node->right = new Node(node->right->value, node->right->x, node->right->y, node->right->left, node->right->right);
        upd(node->right, idx, x);
    } else if (node->right != nullptr && node->right->x > idx) {
        node->left = new Node(node->left->value, node->left->x, node->left->y, node->left->left, node->left->right);
        upd(node->left, idx, x);
    }
    if (node->x == node->y) {
        node->value = x;
    } else {
        node->value = node->left->value+node->right->value;
    }
};

for (int i = 0; i < n; i++) cin >> A[i];

trees.push_back(new Node(0, 0, N-1, nullptr, nullptr));
build(trees[0]);
