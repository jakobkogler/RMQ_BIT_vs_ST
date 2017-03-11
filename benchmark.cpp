#include <iostream>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include "BIT.h"
#include "SegmentTreeTopDown.h"
#include "SegmentTreeBottomUp.h"

using namespace std;
using namespace std::chrono;

int main() {
    cout.precision(6);
    cout << fixed;

    int N = 1e5;
    int M = 1e7;

    srand(time(NULL));

    vector<int> data(N);
    for (int i = 0; i < N; i++)
        data[i] = rand();

    BIT_MIN bit(N);
    for (int i = 0; i < N; i++) 
        bit.set(i+1, data[i]);

    SegmentTreeBottomUp st_bu(N);
    for (int i = 0; i < N; i++) 
        st_bu.update(i+1, data[i]);

    SegmentTreeTopDown st_td(N);
    for (int i = 0; i < N; i++)
        st_td.update(1, 0, N-1, i, data[i]);

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

        vector<int> result_st_bu(M, 0);
        high_resolution_clock::time_point start_st_bu = high_resolution_clock::now();
        for (int i = 0; i < M; i++)
            result_st_bu[i] = st_bu.range(queries[i].first, queries[i].second+1);
        high_resolution_clock:: time_point end_st_bu = high_resolution_clock::now();
        auto duration_st_bu = duration_cast<microseconds>(end_st_bu - start_st_bu).count();

        vector<int> result_st_td(M, 0);
        high_resolution_clock::time_point start_st_td = high_resolution_clock::now();
        for (int i = 0; i < M; i++)
            result_st_td[i] = st_td.query(1, 1, N, queries[i].first, queries[i].second);
        high_resolution_clock:: time_point end_st_td = high_resolution_clock::now();
        auto duration_st_td = duration_cast<microseconds>(end_st_td - start_st_td).count();

        bool b = true;
        for (int i = 0; i < M; i++) {
            b &= result_bit[i] == result_st_bu[i];
            b &= result_st_td[i] == result_st_bu[i];
        }

        cout << "QUERY BENCHMARK\n";
        cout << "Result identical: " << (b ? "true" : "false") << '\n';
        cout << "BIT:   " << duration_bit / 1e6 << "s\n";
        cout << "ST_BU: " << duration_st_bu / 1e6 << "s\n";
        cout << "ST_TD: " << duration_st_td / 1e6 << "s\n";
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

        high_resolution_clock::time_point start_st_bu = high_resolution_clock::now();
        for (int i = 0; i < M; i++)
            st_bu.update(queries[i].first, queries[i].second);
        high_resolution_clock:: time_point end_st_bu = high_resolution_clock::now();
        auto duration_st_bu = duration_cast<microseconds>(end_st_bu - start_st_bu).count();

        high_resolution_clock::time_point start_st_td = high_resolution_clock::now();
        for (int i = 0; i < M; i++)
            st_td.update(1, 1, N, queries[i].first, queries[i].second);
        high_resolution_clock:: time_point end_st_td = high_resolution_clock::now();
        auto duration_st_td = duration_cast<microseconds>(end_st_td - start_st_td).count();

        cout << "UPDATE BENCHMARK\n";
        cout << "BIT:   " << duration_bit / 1e6 << "s\n";
        cout << "ST_BU: " << duration_st_bu / 1e6 << "s\n";
        cout << "ST_TD: " << duration_st_td / 1e6 << "s\n";
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

        vector<int> result_st_bu(M, 0);
        high_resolution_clock::time_point start_st_bu = high_resolution_clock::now();
        for (int i = 0; i < M; i++)
            result_st_bu[i] = st_bu.range(queries[i].first, queries[i].second+1);
        high_resolution_clock:: time_point end_st_bu = high_resolution_clock::now();
        auto duration_st_bu = duration_cast<microseconds>(end_st_bu - start_st_bu).count();

        vector<int> result_st_td(M, 0);
        high_resolution_clock::time_point start_st_td = high_resolution_clock::now();
        for (int i = 0; i < M; i++)
            result_st_td[i] = st_td.query(1, 1, N, queries[i].first, queries[i].second);
        high_resolution_clock:: time_point end_st_td = high_resolution_clock::now();
        auto duration_st_td = duration_cast<microseconds>(end_st_td - start_st_td).count();

        bool b = true;
        for (int i = 0; i < M; i++) {
            b &= result_bit[i] == result_st_bu[i];
            b &= result_st_td[i] == result_st_bu[i];
        }

        cout << "QUERY BENCHMARK\n";
        cout << "Result identical: " << (b ? "true" : "false") << '\n';
        cout << "BIT:   " << duration_bit / 1e6 << "s\n";
        cout << "ST_BU: " << duration_st_bu / 1e6 << "s\n";
        cout << "ST_TD: " << duration_st_td / 1e6 << "s\n";
        cout << '\n';
    }
}

