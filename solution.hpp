#ifndef SOLUTION
#define SOLUTION

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>
#include <queue>

#include "input.hpp"
#include "output.hpp"
#include "pair_sorter.hpp"

using namespace std;

class Solution : public Output {
public:

    Solution(const Input* pin);

    void solve();
    void construct_phase();
    void update_pq(int k);
    int add_item(int item, int knap);
    void add_pair(int a, int b, int k, int profit);

    priority_queue<PairSorter> p_list;
    vector<int> i_list;
    vector<int> k_curr_caps;
    vector<int> i_knap;
};

#endif
