#include <bits/stdc++.h>
using namespace std;

struct Node {
    int value, lazy;
    Node *leftX, *rightX, *leftY, *rightY, *leftZ, *rightZ, *leftW, *rightW, *leftV, *rightV;
    Node(int v = 0) : value(v), lazy(0), leftX(nullptr), rightX(nullptr), leftY(nullptr),
                      rightY(nullptr), leftZ(nullptr), rightZ(nullptr), leftW(nullptr), rightW(nullptr),
                      leftV(nullptr), rightV(nullptr) {}
};

class PersistentSegmentTree5D {
public:
    PersistentSegmentTree5D(int sizeX, int sizeY, int sizeZ, int sizeW, int sizeV)
        : sizeX(sizeX), sizeY(sizeY), sizeZ(sizeZ), sizeW(sizeW), sizeV(sizeV) {
        roots.push_back(build(0, 0, 0, 0, 0, sizeX - 1, sizeY - 1, sizeZ - 1, sizeW - 1, sizeV - 1));
    }

    void rangeUpdate(int version, int x1, int y1, int z1, int w1, int v1, int x2, int y2, int z2, int w2, int v2, int delta) {
        roots.push_back(update(roots[version], 0, 0, 0, 0, 0, sizeX - 1, sizeY - 1, sizeZ - 1, sizeW - 1, sizeV - 1, x1, y1, z1, w1, v1, x2, y2, z2, w2, v2, delta));
    }

    int rangeQuery(int version, int x1, int y1, int z1, int w1, int v1, int x2, int y2, int z2, int w2, int v2) {
        return query(roots[version], 0, 0, 0, 0, 0, sizeX - 1, sizeY - 1, sizeZ - 1, sizeW - 1, sizeV - 1, x1, y1, z1, w1, v1, x2, y2, z2, w2, v2);
    }

private:
    int sizeX, sizeY, sizeZ, sizeW, sizeV;
    vector<Node*> roots;

    Node* build(int x1, int y1, int z1, int w1, int v1, int x2, int y2, int z2, int w2, int v2) {
        Node* node = new Node();
        if (x1 == x2 && y1 == y2 && z1 == z2 && w1 == w2 && v1 == v2) return node;
        int midX = (x1 + x2) / 2, midY = (y1 + y2) / 2, midZ = (z1 + z2) / 2, midW = (w1 + w2) / 2, midV = (v1 + v2) / 2;

        node->leftX = build(x1, y1, z1, w1, v1, midX, midY, midZ, midW, midV);
        node->rightX = build(midX + 1, midY + 1, midZ + 1, midW + 1, midV + 1, x2, y2, z2, w2, v2);
        return node;
    }

    void propagate(Node* node, int x1, int y1, int z1, int w1, int v1, int x2, int y2, int z2, int w2, int v2) {
        if (node->lazy) {
            node->value += (x2 - x1 + 1) * (y2 - y1 + 1) * (z2 - z1 + 1) * (w2 - w1 + 1) * (v2 - v1 + 1) * node->lazy;
            if (x1 != x2 || y1 != y2 || z1 != z2 || w1 != w2 || v1 != v2) {
                if (!node->leftX) node->leftX = new Node();
                if (!node->rightX) node->rightX = new Node();
                node->leftX->lazy += node->lazy;
                node->rightX->lazy += node->lazy;
            }
            node->lazy = 0;
        }
    }

    Node* update(Node* prev, int x1, int y1, int z1, int w1, int v1, int x2, int y2, int z2, int w2, int v2,
                 int qx1, int qy1, int qz1, int qw1, int qv1, int qx2, int qy2, int qz2, int qw2, int qv2, int delta) {
        if (!prev) return nullptr;
        if (qx1 > x2 || qy1 > y2 || qz1 > z2 || qw1 > w2 || qv1 > v2 || qx2 < x1 || qy2 < y1 || qz2 < z1 || qw2 < w1 || qv2 < v1)
            return prev;

        Node* node = new Node(*prev);
        propagate(node, x1, y1, z1, w1, v1, x2, y2, z2, w2, v2);

        if (qx1 <= x1 && qy1 <= y1 && qz1 <= z1 && qw1 <= w1 && qv1 <= v1 && qx2 >= x2 && qy2 >= y2 && qz2 >= z2 && qw2 >= w2 && qv2 >= v2) {
            node->lazy += delta;
            propagate(node, x1, y1, z1, w1, v1, x2, y2, z2, w2, v2);
            return node;
        }

        int midX = (x1 + x2) / 2, midY = (y1 + y2) / 2, midZ = (z1 + z2) / 2, midW = (w1 + w2) / 2, midV = (v1 + v2) / 2;
        node->leftX = update(prev->leftX, x1, y1, z1, w1, v1, midX, midY, midZ, midW, midV, qx1, qy1, qz1, qw1, qv1, qx2, qy2, qz2, qw2, qv2, delta);
        node->rightX = update(prev->rightX, midX + 1, midY + 1, midZ + 1, midW + 1, midV + 1, x2, y2, z2, w2, v2, qx1, qy1, qz1, qw1, qv1, qx2, qy2, qz2, qw2, qv2, delta);

        node->value = (node->leftX ? node->leftX->value : 0) + (node->rightX ? node->rightX->value : 0);
        return node;
    }

    int query(Node* node, int x1, int y1, int z1, int w1, int v1, int x2, int y2, int z2, int w2, int v2,
              int qx1, int qy1, int qz1, int qw1, int qv1, int qx2, int qy2, int qz2, int qw2, int qv2) {
        if (!node || qx1 > x2 || qy1 > y2 || qz1 > z2 || qw1 > w2 || qv1 > v2 || qx2 < x1 || qy2 < y1 || qz2 < z1 || qw2 < w1 || qv2 < v1)
            return 0;
        propagate(node, x1, y1, z1, w1, v1, x2, y2, z2, w2, v2);

        if (qx1 <= x1 && qy1 <= y1 && qz1 <= z1 && qw1 <= w1 && qv1 <= v1 && qx2 >= x2 && qy2 >= y2 && qz2 >= z2 && qw2 >= w2 && qv2 >= v2)
            return node->value;

        int midX = (x1 + x2) / 2, midY = (y1 + y2) / 2, midZ = (z1 + z2) / 2, midW = (w1 + w2) / 2, midV = (v1 + v2) / 2;
        int leftSum = query(node->leftX, x1, y1, z1, w1, v1, midX, midY, midZ, midW, midV, qx1, qy1, qz1, qw1, qv1, qx2, qy2, qz2, qw2, qv2);
        int rightSum = query(node->rightX, midX + 1, midY + 1, midZ + 1, midW + 1, midV + 1, x2, y2, z2, w2, v2, qx1, qy1, qz1, qw1, qv1, qx2, qy2, qz2, qw2, qv2);

        return leftSum + rightSum;
    }
};

int main() {
    int sizeX = 10, sizeY = 10, sizeZ = 10, sizeW = 10, sizeV = 10;
    PersistentSegmentTree5D pst5d(sizeX, sizeY, sizeZ, sizeW, sizeV);

    pst5d.rangeUpdate(0, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 5);
    pst5d.rangeUpdate(1, 2, 2, 2, 2, 2, 5, 5, 5, 5, 5, 10);

    cout << "Sum in range (1,1,1,1,1) to (3,3,3,3,3) in version 0: " << pst5d.rangeQuery(0, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3) << endl;
    cout << "Sum in range (2,2,2,2,2) to (5,5,5,5,5) in version 1: " << pst5d.rangeQuery(1, 2, 2, 2, 2, 2, 5, 5, 5, 5, 5) << endl;

    return 0;
}
