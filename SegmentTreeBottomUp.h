#include <vector>

class SegmentTreeBottomUp {
private:
    std::vector<int> data;
    int n;

public:
    SegmentTreeBottomUp(int n) {
        this->n = n;
        data.assign(2*n, 0);
    }

    void update(int idx, int val) {
        idx += n;
        data[idx] = val;

        while (idx > 1) {
            idx >>= 1;
            int new_min = std::min(data[idx<<1], data[idx<<1|1]);
            if (new_min == data[idx]) break;
            data[idx] = new_min;
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
