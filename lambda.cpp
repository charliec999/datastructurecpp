#include <bits/stdc++.h>
using namespace std;


struct Node {
    int value, lazy;       
    Node *left, *right;    

    Node(int value = 0) : value(value), lazy(0), left(nullptr), right(nullptr) {}
};

class PersistentSegmentTree {
public:
    PersistentSegmentTree(int n) : n(n) {
        roots.push_back(build(0, n - 1)); 
    }

    
    void pointUpdate(int version, int idx, int newValue) {
        roots.push_back(update(roots[version], 0, n - 1, idx, newValue));
    }

    
    int rangeQuery(int version, int l, int r) {
        return query(roots[version], 0, n - 1, l, r);
    }

private:
    int n;
    vector<Node*> roots; 

    
    Node* build(int l, int r) {
        Node* node = new Node();
        if (l == r) return node; 
        int mid = (l + r) / 2;
        node->left = build(l, mid);
        node->right = build(mid + 1, r);
        return node;
    }

    
    void propagate(Node* node, int l, int r) {
        if (node->lazy != 0) {
            node->value += (r - l + 1) * node->lazy; 
            if (l != r) { 
                if (!node->left) node->left = new Node();
                if (!node->right) node->right = new Node();
                node->left->lazy += node->lazy;
                node->right->lazy += node->lazy;
            }
            node->lazy = 0; 
        }
    }

    
    Node* update(Node* prev, int l, int r, int idx, int newValue) {
        Node* node = new Node();
        *node = *prev; 

        propagate(node, l, r);
        if (l == r) {
            node->value = newValue;
            return node;
        }

        int mid = (l + r) / 2;
        if (idx <= mid) {
            node->left = update(prev->left, l, mid, idx, newValue);
        } else {
            node->right = update(prev->right, mid + 1, r, idx, newValue);
        }
        node->value = node->left->value + node->right->value;
        return node;
    }

    
    int query(Node* node, int l, int r, int ql, int qr) {
        if (!node || ql > r || qr < l) return 0; 
        propagate(node, l, r); 
        if (ql <= l && r <= qr) return node->value; 

        int mid = (l + r) / 2;
        return query(node->left, l, mid, ql, qr) + query(node->right, mid + 1, r, ql, qr);
    }
};

int main() {
    int n = 10; 
    PersistentSegmentTree pst(n);

    
    pst.pointUpdate(0, 2, 5);  
    pst.pointUpdate(1, 4, 10); 

    
    cout << "Sum in range [2, 4] in version 0: " << pst.rangeQuery(0, 2, 4) << endl;
    cout << "Sum in range [2, 4] in version 1: " << pst.rangeQuery(1, 2, 4) << endl;

    return 0;
}
