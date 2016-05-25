#ifndef SOLUTION
#define SOLUTION

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <utility>
#include <set>
#include <algorithm>
#include <queue>

#include "input.hpp"
#include "output.hpp"
#include "pair_sorter.hpp"

#define CL 6

using namespace std;

class Solution : public Output {
public:

    Solution(const Input* pin);

    void solve();
    void construct_phase();
    void update_pq(int k);
    int add_item(int item, int knap);
    void add_pair(int a, int b, int k);
    int local_search(int last);
    void get_best_swap_move(int forbidden_item, int& best1, int& best2);
    void swap_move(int i1, int i2);
    void restore_current_solution(int item, int first_knap);
    int get_best_shift_move(int knap, int forbidden_item, int last_item);
    int get_heaviest_assigned_item();
    int remove_item(int item);
    int reassign_item(int item, int forbidden_knap);
    int get_assignment_profit(int item, int knap);
    int evaluate_solution();
    void adaptive_perturbation();
    void random_remove(int num_of_removals);

    void convert_solution(int k, const vector<int>& knap_itens);
    int get_dp_assignment_profit(int item, const vector<int>& knap_itens);
    void dp_knap_fill(int k);
    void dp_construct_phase();

    priority_queue<PairSorter> p_list;
    vector<int> k_curr_caps;
    vector<int> i_knap;
    int current_solution;
    int reference_solution;
    int trial_solution;
    int best_local_search_solution;
    // int no_improv_iter = 0;
    stack < pair < double, int > > moves;

    vector< vector <int> > b;
    vector<int> dp;
};

#endif
