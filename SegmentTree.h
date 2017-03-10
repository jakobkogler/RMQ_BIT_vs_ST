#include <vector>

class SegmentTree {
private:
    std::vector<int> data;
    int n;

public:
    SegmentTree(int n) {
        this->n = n;
        data.assign(2*n, 0);
    }

    void update(int idx, int val) {
        idx += n;
        data[idx] = val;

        while (idx > 1) {
            idx >>= 1;
            data[idx] = std::min(data[idx<<1], data[idx<<1|1]);
        }
    }

    int range(int left, int right) {
        left += n;
        right += n;

        int result = data[left];
        while (left < right) {
            if (left & 1) result = std::min(result, data[left++]);
            if (right & 1) result = std::min(result, data[--right]);
            left >>= 1;
            right >>= 1;
        }
        return result;
    }  
};