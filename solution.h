#ifndef SOLUTION
#define SOLUTION

#include <bits/stdc++.h>

class Solution : public Output {
public:

    Solution(const Input pin);

    int add_item(int item, int knap);
    int add_pair(int par);
    void construct_phase();
    void solve();

    struct PairComp { // Define prioridade dos pares de itens
        bool operator()(pair a, pair b) {
            double a_denst = in->i_values[a.first] + in->i_values[a.second] + in->p_values[a.first][a.second];
            a_denst /= (in->i_weights[a.first]+in->i_weights[a.second]);
            double b_denst = in->i_values[b.first] + in->i_values[b.second] + in->p_values[b.first][b.second];
            b_denst /= (in->i_weights[b.first]+in->i_weights[b.second]);
            return a_denst > b_denst;
        }
    };

    struct ItemComp { // Define prioridade dos itens
        bool operator()(int a, int b) {
            double a_denst = in->i_values[a]/in->i_weights[a];
            double b_denst = in->i_values[b]/in->i_weights[b];
            if(a_denst == b_denst)
                return in->i_values[a] > in->i_values[b];
            return a_denst > b_denst;
        }
    };

    set<pair<int, int>, PairComp> p_list;
    vector<int> k_curr_caps;
    vector<int> i_knap;
    set<int, ItemComp> i_desc;
};

#endif
