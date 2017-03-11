#include <vector>
#include <limits>

class SegmentTreeTopDown {
private:
    std::vector<int> data;
    int n;

public:
    SegmentTreeTopDown(int n) {
        this->n = n;
        data.assign(4*n, 0);
    }

    void update(int node, int lower_bound, int upper_bound, int idx, int val) {
        if (lower_bound > upper_bound || lower_bound > idx || upper_bound < idx)
            return;

        if (lower_bound == upper_bound) { // leave node
            data[node] = val;
            return;
        }

        update(node<<1, lower_bound, (lower_bound+upper_bound)>>1, idx, val);
        update(node<<1|1, ((lower_bound+upper_bound)>>1)+1, upper_bound, idx, val);
        data[node] = std::min(data[node<<1], data[node<<1|1]);
    }

    int query(int node, int lower_bound, int upper_bound, int l, int r) {
        if (lower_bound > upper_bound || lower_bound > r || upper_bound < l)
            return std::numeric_limits<int>::max();

        if (lower_bound >= l && upper_bound <= r)
            return data[node];

        int q1 = query(node<<1, lower_bound, (lower_bound+upper_bound)>>1, l, r);
        int q2 = query(node<<1|1, ((lower_bound+upper_bound)>>1)+1, upper_bound, l, r);
        return std::min(q1, q2);
    }  
};
