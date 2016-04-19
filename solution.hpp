#ifndef SOLUTION
#define SOLUTION

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>

#include "input.hpp"
#include "output.hpp"
#include "pair_sorter.hpp"

using namespace std;

class Solution : public Output {
public:

    Solution(const Input* pin);

    void solve();
    void construct_phase();
    int add_item(int item, int knap);
    void add_pair(pair<int, int> par);

    vector< pair<int, int> > p_list;
    vector<int> i_list;
    vector<int> k_curr_caps;
    vector<int> i_knap;
};

#endif
