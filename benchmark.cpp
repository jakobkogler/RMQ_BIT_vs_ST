#include <iostream>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include "BIT.h"
#include "SegmentTree.h"

using namespace std;
using namespace std::chrono;

int main() {
    int N = 1e6;
    int M = 1e7;

    srand(time(NULL));

    vector<int> data(N);
    for (int i = 0; i < N; i++)
        data[i] = rand();

    BIT_MIN bit(N);
    for (int i = 0; i < N; i++) 
        bit.set(i+1, data[i]);

    SegmentTree st(N);
    for (int i = 0; i < N; i++) 
        st.update(i+1, data[i]);

    {
        // benchmark queries
        vector<pair<int, int>> queries(M);
        for (int i = 0; i < M; i++) {
            int l = rand() % N;
            int r = rand() % N;
            if (l > r)
                swap(l, r);
            l++;
            r++;
            queries[i] = {l, r};
        }

        vector<int> result_bit(M, 0);
        high_resolution_clock::time_point start_bit = high_resolution_clock::now();
        for (int i = 0; i < M; i++)
            result_bit[i] = bit.get_min(queries[i].first, queries[i].second);
        high_resolution_clock:: time_point end_bit = high_resolution_clock::now();
        auto duration_bit = duration_cast<microseconds>(end_bit - start_bit).count();

        vector<int> result_st(M, 0);
        high_resolution_clock::time_point start_st = high_resolution_clock::now();
        for (int i = 0; i < M; i++)
            result_st[i] = st.range(queries[i].first, queries[i].second+1);
        high_resolution_clock:: time_point end_st = high_resolution_clock::now();
        auto duration_st = duration_cast<microseconds>(end_st - start_st).count();

        bool b = true;
        for (int i = 0; i < M; i++) {
            b &= result_bit[i] == result_st[i];
        }

        cout << "QUERY BENCHMARK\n";
        cout << "Result identical: " << (b ? "true" : "false") << '\n';
        cout << "BIT: " << duration_bit << " microsecond\n";
        cout << "ST:  " << duration_st << " microsecond\n";
        cout << '\n';
    }

    {
        // benchmark updates
        vector<pair<int, int>> queries(M);
        for (int i = 0; i < M; i++) {
            queries[i] = { (rand() % N) + 1, rand() };
        }

        high_resolution_clock::time_point start_bit = high_resolution_clock::now();
        for (int i = 0; i < M; i++)
            bit.set(queries[i].first, queries[i].second);
        high_resolution_clock:: time_point end_bit = high_resolution_clock::now();
        auto duration_bit = duration_cast<microseconds>(end_bit - start_bit).count();

        high_resolution_clock::time_point start_st = high_resolution_clock::now();
        for (int i = 0; i < M; i++)
            st.update(queries[i].first, queries[i].second);
        high_resolution_clock:: time_point end_st = high_resolution_clock::now();
        auto duration_st = duration_cast<microseconds>(end_st - start_st).count();

        cout << "UPDATE BENCHMARK\n";
        cout << "BIT: " << duration_bit << " microsecond\n";
        cout << "ST:  " << duration_st << " microsecond\n";
        cout << '\n';
    }

    {
        // benchmark queries
        vector<pair<int, int>> queries(M);
        for (int i = 0; i < M; i++) {
            int l = rand() % N;
            int r = rand() % N;
            if (l > r)
                swap(l, r);
            l++;
            r++;
            queries[i] = {l, r};
        }

        vector<int> result_bit(M, 0);
        high_resolution_clock::time_point start_bit = high_resolution_clock::now();
        for (int i = 0; i < M; i++)
            result_bit[i] = bit.get_min(queries[i].first, queries[i].second);
        high_resolution_clock:: time_point end_bit = high_resolution_clock::now();
        auto duration_bit = duration_cast<microseconds>(end_bit - start_bit).count();

        vector<int> result_st(M, 0);
        high_resolution_clock::time_point start_st = high_resolution_clock::now();
        for (int i = 0; i < M; i++)
            result_st[i] = st.range(queries[i].first, queries[i].second+1);
        high_resolution_clock:: time_point end_st = high_resolution_clock::now();
        auto duration_st = duration_cast<microseconds>(end_st - start_st).count();

        bool b = true;
        for (int i = 0; i < M; i++) {
            b &= result_bit[i] == result_st[i];
        }

        cout << "QUERY BENCHMARK\n";
        cout << "Result identical: " << (b ? "true" : "false") << '\n';
        cout << "BIT: " << duration_bit << " microsecond\n";
        cout << "ST:  " << duration_st << " microsecond\n";
        cout << '\n';
    }
}

