#include <iostream>
#include <vector>
#include <memory>
#include <cstring>

using namespace std;


struct Node {
    int value;
    unique_ptr<Node> children[32]; 

    Node(int v = 0) : value(v) {
        memset(children, 0, sizeof(children));
    }
};

class PersistentSegmentTree5D {
public:
    PersistentSegmentTree5D(int sizeX, int sizeY, int sizeZ, int sizeW, int sizeV)
        : sizeX(sizeX), sizeY(sizeY), sizeZ(sizeZ), sizeW(sizeW), sizeV(sizeV) {
        roots.push_back(build(0, 0, 0, 0, 0, sizeX - 1, sizeY - 1, sizeZ - 1, sizeW - 1, sizeV - 1));
    }

    
    void rangeUpdate(int version, int x1, int y1, int z1, int w1, int v1, int x2, int y2, int z2, int w2, int v2, int delta) {
        roots.push_back(update(roots[version], 0, 0, 0, 0, 0, sizeX - 1, sizeY - 1, sizeZ - 1, sizeW - 1, sizeV - 1,
                               x1, y1, z1, w1, v1, x2, y2, z2, w2, v2, delta));
    }

    
    int rangeQuery(int version, int x1, int y1, int z1, int w1, int v1, int x2, int y2, int z2, int w2, int v2) {
        return query(roots[version], 0, 0, 0, 0, 0, sizeX - 1, sizeY - 1, sizeZ - 1, sizeW - 1, sizeV - 1,
                     x1, y1, z1, w1, v1, x2, y2, z2, w2, v2);
    }

private:
    int sizeX, sizeY, sizeZ, sizeW, sizeV;
    vector<unique_ptr<Node>> roots;

    
    unique_ptr<Node> build(int x1, int y1, int z1, int w1, int v1, int x2, int y2, int z2, int w2, int v2) {
        auto node = make_unique<Node>();
        if (x1 == x2 && y1 == y2 && z1 == z2 && w1 == w2 && v1 == v2) return move(node);

        int midX = (x1 + x2) / 2;
        int midY = (y1 + y2) / 2;
        int midZ = (z1 + z2) / 2;
        int midW = (w1 + w2) / 2;
        int midV = (v1 + v2) / 2;

        
        node->children[0] = build(x1, y1, z1, w1, v1, midX, midY, midZ, midW, midV);
        node->children[1] = build(midX + 1, y1, z1, w1, v1, x2, midY, midZ, midW, midV);
        node->children[2] = build(x1, midY + 1, z1, w1, v1, midX, y2, midZ, midW, midV);
        node->children[3] = build(midX + 1, midY + 1, z1, w1, v1, x2, y2, midZ, midW, midV);
        node->children[4] = build(x1, y1, midZ + 1, w1, v1, midX, midY, z2, midW, midV);
        node->children[5] = build(midX + 1, y1, midZ + 1, w1, v1, x2, midY, z2, midW, midV);
        node->children[6] = build(x1, midY + 1, midZ + 1, w1, v1, midX, y2, z2, midW, midV);
        node->children[7] = build(midX + 1, midY + 1, midZ + 1, w1, v1, x2, y2, z2, midW, midV);
        node->children[8] = build(x1, y1, z1, midW + 1, v1, midX, midY, z2, w2, midV);
        node->children[9] = build(midX + 1, y1, z1, midW + 1, v1, x2, midY, z2, w2, midV);
        node->children[10] = build(x1, midY + 1, z1, midW + 1, v1, midX, y2, z2, w2, midV);
        node->children[11] = build(midX + 1, midY + 1, z1, midW + 1, v1, x2, y2, z2, w2, midV);
        node->children[12] = build(x1, y1, z1, w2 + 1, midV + 1, midX, midY, z2, w2, v2);
        node->children[13] = build(midX + 1, y1, z1, w2 + 1, midV + 1, x2, midY, z2, w2, v2);
        node->children[14] = build(x1, midY + 1, z1, w2 + 1, midV + 1, midX, y2, z2, w2, v2);
        node->children[15] = build(midX + 1, midY + 1, z1, w2 + 1, midV + 1, x2, y2, z2, w2, v2);
        node->children[16] = build(x1, y1, z1, w2 + 1, v1, midX, midY, z2, midW, midV);
        node->children[17] = build(midX + 1, y1, z1, w2 + 1, v1, x2, midY, z2, midW, midV);
        node->children[18] = build(x1, midY + 1, z1, w2 + 1, v1, midX, y2, z2, midW, midV);
        node->children[19] = build(midX + 1, midY + 1, z1, w2 + 1, v1, x2, y2, z2, midW, midV);
        node->children[20] = build(x1, y1, midZ + 1, w1, v1, midX, midY, z2, midW, midV);
        node->children[21] = build(midX + 1, y1, midZ + 1, w1, v1, x2, midY, z2, midW, midV);
        node->children[22] = build(x1, midY + 1, midZ + 1, w1, v1, midX, y2, z2, midW, midV);
        node->children[23] = build(midX + 1, midY + 1, midZ + 1, w1, v1, x2, y2, z2, midW, midV);
        node->children[24] = build(x1, y1, midZ + 1, w2 + 1, v1, midX, midY, z2, midW, midV);
        node->children[25] = build(midX + 1, y1, midZ + 1, w2 + 1, v1, x2, midY, z2, midW, midV);
        node->children[26] = build(x1, midY + 1, midZ + 1, w2 + 1, v1, midX, y2, z2, midW, midV);
        node->children[27] = build(midX + 1, midY + 1, midZ + 1, w2 + 1, v1, x2, y2, z2, midW, midV);
        node->children[28] = build(x1, y1, z1, midW + 1, midV + 1, midX, midY, z2, w2, v2);
        node->children[29] = build(midX + 1, y1, z1, midW + 1, midV + 1, x2, midY, z2, w2, v2);
        node->children[30] = build(x1, midY + 1, z1, midW + 1, midV + 1, midX, y2, z2, w2, v2);
        node->children[31] = build(midX + 1, midY + 1, z1, midW + 1, midV + 1, x2, y2, z2, w2, v2);

        return move(node);
    }

    
    unique_ptr<Node> update(unique_ptr<Node>& node, int x1, int y1, int z1, int w1, int v1, 
                            int x2, int y2, int z2, int w2, int v2,
                            int qx1, int qy1, int qz1, int qw1, int qv1, 
                            int qx2, int qy2, int qz2, int qw2, int qv2, int delta) {
        if (qx1 > x2 || qx2 < x1 || qy1 > y2 || qy2 < y1 || qz1 > z2 || qz2 < z1 || 
            qw1 > w2 || qw2 < w1 || qv1 > v2 || qv2 < v1) {
            return make_unique<Node>(*node); 
        }

        auto newNode = make_unique<Node>(node->value + (qx1 >= x1 && qx2 <= x2 && 
                                                         qy1 >= y1 && qy2 <= y2 && 
                                                         qz1 >= z1 && qz2 <= z2 && 
                                                         qw1 >= w1 && qw2 <= w2 && 
                                                         qv1 >= v1 && qv2 <= v2 ? delta : 0));

        for (int i = 0; i < 32; ++i) {
            newNode->children[i] = make_unique<Node>(*node->children[i]); 
        }

        if (x1 == x2 && y1 == y2 && z1 == z2 && w1 == w2 && v1 == v2) {
            newNode->value += delta; 
            return newNode;
        }

        int midX = (x1 + x2) / 2;
        int midY = (y1 + y2) / 2;
        int midZ = (z1 + z2) / 2;
        int midW = (w1 + w2) / 2;
        int midV = (v1 + v2) / 2;

        
        newNode->children[0] = update(newNode->children[0], x1, y1, z1, w1, v1, midX, midY, midZ, midW, midV, qx1, qy1, qz1, qw1, qv1, qx2, qy2, qz2, qw2, qv2, delta);
        newNode->children[1] = update(newNode->children[1], midX + 1, y1, z1, w1, v1, x2, midY, midZ, midW, midV, qx1, qy1, qz1, qw1, qv1, qx2, qy2, qz2, qw2, qv2, delta);
        newNode->children[2] = update(newNode->children[2], x1, midY + 1, z1, w1, v1, midX, y2, midZ, midW, midV, qx1, qy1, qz1, qw1, qv1, qx2, qy2, qz2, qw2, qv2, delta);
        newNode->children[3] = update(newNode->children[3], midX + 1, midY + 1, z1, w1, v1, x2, y2, midZ, midW, midV, qx1, qy1, qz1, qw1, qv1, qx2, qy2, qz2, qw2, qv2, delta);
        newNode->children[4] = update(newNode->children[4], x1, y1, midZ + 1, w1, v1, midX, midY, z2, midW, midV, qx1, qy1, qz1, qw1, qv1, qx2, qy2, qz2, qw2, qv2, delta);
        newNode->children[5] = update(newNode->children[5], midX + 1, y1, midZ + 1, w1, v1, x2, midY, z2, midW, midV, qx1, qy1, qz1, qw1, qv1, qx2, qy2, qz2, qw2, qv2, delta);
        newNode->children[6] = update(newNode->children[6], x1, midY + 1, midZ + 1, w1, v1, midX, y2, z2, midW, midV, qx1, qy1, qz1, qw1, qv1, qx2, qy2, qz2, qw2, qv2, delta);
        newNode->children[7] = update(newNode->children[7], midX + 1, midY + 1, midZ + 1, w1, v1, x2, y2, z2, midW, midV, qx1, qy1, qz1, qw1, qv1, qx2, qy2, qz2, qw2, qv2, delta);
        newNode->children[8] = update(newNode->children[8], x1, y1, z1, midW + 1, v1, midX, midY, z2, w2, midV, qx1, qy1, qz1, qw1, qv1, qx2, qy2, qz2, qw2, qv2, delta);
        newNode->children[9] = update(newNode->children[9], midX + 1, y1, z1, midW + 1, v1, x2, midY, z2, w2, midV, qx1, qy1, qz1, qw1, qv1, qx2, qy2, qz2, qw2, qv2, delta);
        newNode->children[10] = update(newNode->children[10], x1, midY + 1, z1, midW + 1, v1, midX, y2, z2, w2, midV, qx1, qy1, qz1, qw1, qv1, qx2, qy2, qz2, qw2, qv2, delta);
        newNode->children[11] = update(newNode->children[11], midX + 1, midY + 1, z1, midW + 1, v1, x2, y2, z2, w2, midV, qx1, qy1, qz1, qw1, qv1, qx2, qy2, qz2, qw2, qv2, delta);
        newNode->children[12] = update(newNode->children[12], x1, y1, z1, w2 + 1, midV + 1, midX, midY, z2, w2, v2, qx1, qy1, qz1, qw1, qv1, qx2, qy2, qz2, qw2, qv2, delta);
        newNode->children[13] = update(newNode->children[13], midX + 1, y1, z1, w2 + 1, midV + 1, x2, midY, z2, w2, v2, qx1, qy1, qz1, qw1, qv1, qx2, qy2, qz2, qw2, qv2, delta);
        newNode->children[14] = update(newNode->children[14], x1, midY + 1, z1, w2 + 1, midV + 1, midX, y2, z2, w2, v2, qx1, qy1, qz1, qw1, qv1, qx2, qy2, qz2, qw2, qv2, delta);
        newNode->children[15] = update(newNode->children[15], midX + 1, midY + 1, z1, w2 + 1, midV + 1, x2, y2, z2, w2, v2, qx1, qy1, qz1, qw1, qv1, qx2, qy2, qz2, qw2, qv2, delta);
        newNode->children[16] = update(newNode->children[16], x1, y1, midZ + 1, w1, v1, midX, midY, z2, midW, midV, qx1, qy1, qz1, qw1, qv1, qx2, qy2, qz2, qw2, qv2, delta);
        newNode->children[17] = update(newNode->children[17], midX + 1, y1, midZ + 1, w1, v1, x2, midY, z2, midW, midV, qx1, qy1, qz1, qw1, qv1, qx2, qy2, qz2, qw2, qv2, delta);
        newNode->children[18] = update(newNode->children[18], x1, midY + 1, midZ + 1, w1, v1, midX, y2, z2, midW, midV, qx1, qy1, qz1, qw1, qv1, qx2, qy2, qz2, qw2, qv2, delta);
        newNode->children[19] = update(newNode->children[19], midX + 1, midY + 1, midZ + 1, w1, v1, x2, y2, z2, midW, midV, qx1, qy1, qz1, qw1, qv1, qx2, qy2, qz2, qw2, qv2, delta);
        newNode->children[20] = update(newNode->children[20], x1, y1, midZ + 1, w2 + 1, midV + 1, midX, midY, z2, midW, midV, qx1, qy1, qz1, qw1, qv1, qx2, qy2, qz2, qw2, qv2, delta);
        newNode->children[21] = update(newNode->children[21], midX + 1, y1, midZ + 1, w2 + 1, midV + 1, x2, midY, z2, midW, midV, qx1, qy1, qz1, qw1, qv1, qx2, qy2, qz2, qw2, qv2, delta);
        newNode->children[22] = update(newNode->children[22], x1, midY + 1, midZ + 1, w2 + 1, midV + 1, midX, y2, z2, midW, midV, qx1, qy1, qz1, qw1, qv1, qx2, qy2, qz2, qw2, qv2, delta);
        newNode->children[23] = update(newNode->children[23], midX + 1, midY + 1, midZ + 1, w2 + 1, midV + 1, x2, y2, z2, midW, midV, qx1, qy1, qz1, qw1, qv1, qx2, qy2, qz2, qw2, qv2, delta);
        newNode->children[24] = update(newNode->children[24], x1, y1, midZ + 1, w2 + 1, midV + 1, midX, midY, z2, midW, midV, qx1, qy1, qz1, qw1, qv1, qx2, qy2, qz2, qw2, qv2, delta);
        newNode->children[25] = update(newNode->children[25], midX + 1, y1, midZ + 1, w2 + 1, midV + 1, x2, midY, z2, midW, midV, qx1, qy1, qz1, qw1, qv1, qx2, qy2, qz2, qw2, qv2, delta);
        newNode->children[26] = update(newNode->children[26], x1, midY + 1, midZ + 1, w2 + 1, midV + 1, midX, y2, z2, midW, midV, qx1, qy1, qz1, qw1, qv1, qx2, qy2, qz2, qw2, qv2, delta);
        newNode->children[27] = update(newNode->children[27], midX + 1, midY + 1, midZ + 1, w2 + 1, midV + 1, x2, y2, z2, midW, midV, qx1, qy1, qz1, qw1, qv1, qx2, qy2, qz2, qw2, qv2, delta);
        newNode->children[28] = update(newNode->children[28], x1, y1, z1, midW + 1, midV + 1, midX, midY, z2, w2, v2, qx1, qy1, qz1, qw1, qv1, qx2, qy2, qz2, qw2, qv2, delta);
        newNode->children[29] = update(newNode->children[29], midX + 1, y1, z1, midW + 1, midV + 1, x2, midY, z2, w2, v2, qx1, qy1, qz1, qw1, qv1, qx2, qy2, qz2, qw2, qv2, delta);
        newNode->children[30] = update(newNode->children[30], x1, midY + 1, z1, midW + 1, midV + 1, midX, y2, z2, w2, v2, qx1, qy1, qz1, qw1, qv1, qx2, qy2, qz2, qw2, qv2, delta);
        newNode->children[31] = update(newNode->children[31], midX + 1, midY + 1, z1, midW + 1, midV + 1, x2, y2, z2, w2, v2, qx1, qy1, qz1, qw1, qv1, qx2, qy2, qz2, qw2, qv2, delta);

        return newNode;
    }

    
    int query(unique_ptr<Node>& node, int x1, int y1, int z1, int w1, int v1, 
              int x2, int y2, int z2, int w2, int v2,
              int qx1, int qy1, int qz1, int qw1, int qv1, 
              int qx2, int qy2, int qz2, int qw2, int qv2) {
        if (qx1 > x2 || qx2 < x1 || qy1 > y2 || qy2 < y1 || qz1 > z2 || qz2 < z1 || 
            qw1 > w2 || qw2 < w1 || qv1 > v2 || qv2 < v1) {
            return 0; 
        }

        if (qx1 <= x1 && qx2 >= x2 && qy1 <= y1 && qy2 >= y2 && 
            qz1 <= z1 && qz2 >= z2 && qw1 <= w1 && qw2 >= w2 && 
            qv1 <= v1 && qv2 >= v2) {
            return node->value; 
        }

        int midX = (x1 + x2) / 2;
        int midY = (y1 + y2) / 2;
        int midZ = (z1 + z2) / 2;
        int midW = (w1 + w2) / 2;
        int midV = (v1 + v2) / 2;

        
        int result = 0;
        for (int i = 0; i < 32; ++i) {
            result += query(node->children[i], x1, y1, z1, w1, v1, 
                            i < 16 ? midX : x2, 
                            i % 4 < 2 ? midY : y2, 
                            i % 8 < 4 ? midZ : z2, 
                            i % 16 < 8 ? midW : w2, 
                            i % 32 < 16 ? midV : v2,
                            qx1, qy1, qz1, qw1, qv1, 
                            qx2, qy2, qz2, qw2, qv2);
        }

        return result;
    }

public:
    SegmentTree5D(int sizeX, int sizeY, int sizeZ, int sizeW, int sizeV) {
        root = build(0, 0, 0, 0, 0, sizeX - 1, sizeY - 1, sizeZ - 1, sizeW - 1, sizeV - 1);
    }

    
    void update(int x1, int y1, int z1, int w1, int v1, 
                int x2, int y2, int z2, int w2, int v2,
                int delta) {
        root = update(root, 0, 0, 0, 0, 0, 
                        x1, y1, z1, w1, v1, 
                        x2, y2, z2, w2, v2, delta);
    }

    
    int query(int x1, int y1, int z1, int w1, int v1, 
              int x2, int y2, int z2, int w2, int v2) {
        return query(root, 0, 0, 0, 0, 0, 
                     x1, y1, z1, w1, v1, 
                     x2, y2, z2, w2, v2);
    }
};

int main() {
    SegmentTree5D segTree(10, 10, 10, 10, 10);
    segTree.update(1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 5); 
    cout << segTree.query(1, 1, 1, 1, 1, 3, 3, 3, 3, 3); 
    return 0;
}
