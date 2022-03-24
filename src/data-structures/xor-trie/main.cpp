class Node {
public:
    int value;
    int index;
    vector<Node*> child;
    Node(int value, int index, Node* l, Node* r):
        value(value), index(index), child({l, r}) {}
    ~Node() {
        for (int i = 0; i < 2; i++) {
            if (child[i] != nullptr) {
                delete child[i];
            }
        }
    }
    void set(int value, int index) {
        this->value = value;
        this->index = index;
    }
    tuple<int, int> get() {
        return {value, index};
    }
};
 
class XOR_Trie {
public:
    Node* root;
    XOR_Trie() {
        root = new_node();
    }
    ~XOR_Trie() {
        delete root;
    }
    Node* new_node() {
        return new Node(-1, -1, nullptr, nullptr);
    }
    void insert(int value, int index) {
        Node* node = root;
        for (int bit = 30; bit >= 0; bit--) {
            int b = value>>bit&1;
            if (bit == 0) {
                if (node->child[b] == nullptr) {
                    node->child[b] = new_node();
                }
                node->child[b]->set(value, index);
            } else {
                Node* next;
                if (node->child[b] == nullptr) {
                    node->child[b] = new_node();
                }
                next = node->child[b];
                node = next;
            }
        }
    }
    void remove(int value, int index) {
        remove(value, index, 30, root);
    }
    bool remove(int value, int index, int bit, Node* node) {
        if (bit == -1) {
            return false;
        }
        int b = value>>bit&1;
        if (remove(value, index, bit-1, node->child[b])) {
            return true;
        }
        if (bit == 0) {
            delete node->child[b];
            node->child[b] = nullptr;
        } else {
            if (node->child[b]->child[0] == nullptr && 
                node->child[b]->child[1] == nullptr) 
            {
                delete node->child[b];
                node->child[b] = nullptr;
            } else {
                return true;
            }
        }
        return false;
    }
    tuple<int, int> query(int value) {
        Node* node = root;
        for (int bit = 30; bit >= 0; bit--) {
            int b = value>>bit&1;
            if (bit == 0) {
                if (node->child[b] != nullptr) {
                    return node->child[b]->get();
                } else {
                    return node->child[!b]->get();
                }
            } else {
                if (node->child[0] == nullptr) {
                    node = node->child[1];
                } else if (node->child[1] == nullptr) {
                    node = node->child[0];
                } else {
                    node = node->child[b];
                }
            }
        }
        return {-1, -1};
    }
};
