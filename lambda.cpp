#include <iostream>
#include <vector>
#include <climits>

class SegmentTree {
private:
    std::vector<int> tree;         
    std::vector<int> lazy;         
    int n;                          

    
    void buildTree(const std::vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            buildTree(arr, 2 * node + 1, start, mid);
            buildTree(arr, 2 * node + 2, mid + 1, end);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2]; 
        }
    }

    
    void propagate(int node, int start, int end) {
        if (lazy[node] != 0) {
            
            tree[node] += lazy[node] * (end - start + 1);
            if (start != end) {
                
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }
            lazy[node] = 0; 
        }
    }

    
    void rangeUpdateUtil(int node, int start, int end, int L, int R, int value) {
        propagate(node, start, end); 

        if (start > end || start > R || end < L) {
            return; 
        }
        if (start >= L && end <= R) {
            
            tree[node] += value * (end - start + 1);
            if (start != end) {
                lazy[2 * node + 1] += value; 
                lazy[2 * node + 2] += value;
            }
            return;
        }

        int mid = (start + end) / 2;
        rangeUpdateUtil(2 * node + 1, start, mid, L, R, value);
        rangeUpdateUtil(2 * node + 2, mid + 1, end, L, R, value);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2]; 
    }

    
    int rangeQueryUtil(int node, int start, int end, int L, int R) {
        propagate(node, start, end); 

        if (start > end || start > R || end < L) {
            return 0; 
        }
        if (start >= L && end <= R) {
            return tree[node]; 
        }

        int mid = (start + end) / 2;
        int leftSum = rangeQueryUtil(2 * node + 1, start, mid, L, R);
        int rightSum = rangeQueryUtil(2 * node + 2, mid + 1, end, L, R);
        return leftSum + rightSum; 
    }

public:
    
    SegmentTree(const std::vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n); 
        lazy.resize(4 * n, 0); 
        buildTree(arr, 0, 0, n - 1); 
    }

    
    void rangeUpdate(int L, int R, int value) {
        rangeUpdateUtil(0, 0, n - 1, L, R, value);
    }

    
    int rangeQuery(int L, int R) {
        return rangeQueryUtil(0, 0, n - 1, L, R);
    }

    
    void pointUpdate(int idx, int newValue) {
        rangeUpdate(idx, idx, newValue); 
    }

    
    ~SegmentTree() {
        
    }
};

int main() {
    std::vector<int> arr = {1, 2, 3, 4, 5};
    SegmentTree segmentTree(arr);

    std::cout << "Initial sum of range [1, 3]: " << segmentTree.rangeQuery(1, 3) << std::endl; 
    segmentTree.rangeUpdate(1, 3, 2); 
    std::cout << "Updated sum of range [1, 3]: " << segmentTree.rangeQuery(1, 3) << std::endl; 

    segmentTree.pointUpdate(2, 10); 
    std::cout << "Sum of range [0, 4]: " << segmentTree.rangeQuery(0, 4) << std::endl; 

    return 0;
}
