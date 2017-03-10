#include <vector>

class BIT_MIN {
private:
    int n;
    std::vector<int> array;
    std::vector<int> BIT1;
    std::vector<int> BIT2;

public:
    BIT_MIN(int n) {
        this->n = n;
        array.assign(n + 2, 0);
        BIT1.assign(n + 2, 0);
        BIT2.assign(n + 2, 0);
    }

    int get_min(int l, int r) {
        int result = array[l];

        int last = l;
        int cur = last + (last & -last);
        while (cur <= r) {
            result = std::min(result, BIT2[last]);
            last = cur;
            cur = last + (last & -last);
        }
        result = std::min(result, array[last]);

        last = r;
        cur = last - (last & -last);
        while (cur >= l) {
            result = std::min(result, BIT1[last]);
            last = cur;
            cur = last - (last & -last);
        }

        return result;
    }

    void set(int idx, int val) {
        int old_val = array[idx];
        array[idx] = val;

        // update BIT1
        int i = idx;
        int v = val;
        while (i <= n) {
            if (v > BIT1[i]) {
                if (old_val == BIT1[i]) {
                    v = std::min(v, array[i]);
                    for (int r = 1;; r++) {
                        int x = (i & -i) >> r;
                        if (x == 0) break;
                        int child = i - x;
                        v = std::min(v, BIT1[child]);
                    }
                } else break;
            }
            if (v == BIT1[i]) break;
            BIT1[i] = v;
            i += (i & -i);
        }

        // update BIT2
        i = idx;
        v = val;
        while (i > 0) {
            if (v > BIT2[i]) {
                if (old_val == BIT2[i]) {
                    v = std::min(v, array[i]);
                    for (int r = 1;; r++) {
                        int x = (i & -i) >> r;
                        if (x == 0) break;
                        int child = i + x;
                        if (child > n + 1) break;
                        v = std::min(v, BIT2[child]);
                    }
                } else break;
            }
            if (v == BIT2[i]) break;
            BIT2[i] = v;
            i -= (i & -i);
        }
    }
};
