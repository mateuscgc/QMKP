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
    void local_search();
    void restore_current_solution(int item, int first_knap);
    int get_best_shift_move(int knap, int forbidden_item);
    int get_heaviest_assigned_item();
    int remove_item(int item);
    int reassign_item(int item, int forbidden_knap);
    int get_assignment_profit(int item, int knap);
    int evaluate_solution();

    // struct Move {
    //     int item;
    //     int ori;
    //     int dest;
    //     Move(int i, o, d) {
    //         item = i;
    //         ori = o;
    //         dest = d;
    //     }
    // };

    priority_queue<PairSorter> p_list;
    vector<int> k_curr_caps;
    vector<int> i_knap;
    int current_solution;
    int best_solution;
    int reference_solution;
    int trial_solution;
    stack < pair < int, int > > moves;
};

#endif
