#include <bits/stdc++.h>
using namespace std;

struct Node {
    int value, lazy;
    Node *left, *right;
    Node(int v = 0) : value(v), lazy(0), left(nullptr), right(nullptr) {}
};

class PersistentSegmentTree2D {
public:
    PersistentSegmentTree2D(int rows, int cols) : rows(rows), cols(cols) {
        roots.push_back(build(0, 0, rows - 1, cols - 1));
    }

    void rangeUpdate(int version, int x1, int y1, int x2, int y2, int delta) {
        roots.push_back(update(roots[version], 0, 0, rows - 1, cols - 1, x1, y1, x2, y2, delta));
    }

    int rangeQuery(int version, int x1, int y1, int x2, int y2) {
        return query(roots[version], 0, 0, rows - 1, cols - 1, x1, y1, x2, y2);
    }

private:
    int rows, cols;
    vector<Node*> roots;

    Node* build(int x1, int y1, int x2, int y2) {
        Node* node = new Node();
        if (x1 == x2 && y1 == y2) return node;
        int midX = (x1 + x2) / 2, midY = (y1 + y2) / 2;
        node->left = build(x1, y1, midX, midY);
        node->right = build(midX + 1, midY + 1, x2, y2);
        return node;
    }

    void propagate(Node* node, int x1, int y1, int x2, int y2) {
        if (node->lazy) {
            node->value += (x2 - x1 + 1) * (y2 - y1 + 1) * node->lazy;
            if (x1 != x2 || y1 != y2) {
                if (!node->left) node->left = new Node();
                if (!node->right) node->right = new Node();
                node->left->lazy += node->lazy;
                node->right->lazy += node->lazy;
            }
            node->lazy = 0;
        }
    }

    Node* update(Node* prev, int x1, int y1, int x2, int y2, int qx1, int qy1, int qx2, int qy2, int delta) {
        if (!prev) return nullptr;
        if (qx1 > x2 || qy1 > y2 || qx2 < x1 || qy2 < y1) return prev; 

        Node* node = new Node(*prev);
        propagate(node, x1, y1, x2, y2);

        if (qx1 <= x1 && qy1 <= y1 && qx2 >= x2 && qy2 >= y2) {
            node->lazy += delta;
            propagate(node, x1, y1, x2, y2);
            return node;
        }

        int midX = (x1 + x2) / 2, midY = (y1 + y2) / 2;
        node->left = update(prev->left, x1, y1, midX, midY, qx1, qy1, qx2, qy2, delta);
        node->right = update(prev->right, midX + 1, midY + 1, x2, y2, qx1, qy1, qx2, qy2, delta);
        node->value = (node->left ? node->left->value : 0) + (node->right ? node->right->value : 0);

        return node;
    }

    int query(Node* node, int x1, int y1, int x2, int y2, int qx1, int qy1, int qx2, int qy2) {
        if (!node || qx1 > x2 || qy1 > y2 || qx2 < x1 || qy2 < y1) return 0;
        propagate(node, x1, y1, x2, y2);

        if (qx1 <= x1 && qy1 <= y1 && qx2 >= x2 && qy2 >= y2) return node->value;

        int midX = (x1 + x2) / 2, midY = (y1 + y2) / 2;
        int leftSum = query(node->left, x1, y1, midX, midY, qx1, qy1, qx2, qy2);
        int rightSum = query(node->right, midX + 1, midY + 1, x2, y2, qx1, qy1, qx2, qy2);

        return leftSum + rightSum;
    }
};

int main() {
    int rows = 10, cols = 10;
    PersistentSegmentTree2D pst2d(rows, cols);

    pst2d.rangeUpdate(0, 1, 1, 3, 3, 5);
    pst2d.rangeUpdate(1, 2, 2, 5, 5, 10);

    cout << "Sum in range (1, 1) to (3, 3) in version 0: " << pst2d.rangeQuery(0, 1, 1, 3, 3) << endl;
    cout << "Sum in range (2, 2) to (5, 5) in version 1: " << pst2d.rangeQuery(1, 2, 2, 5, 5) << endl;

    return 0;
}
