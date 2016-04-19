#include "pair_sorter.hpp"

using namespace std;

PairSorter::PairSorter(const Input* pin) : in(pin) {}

bool PairSorter::operator()(pair<int, int> lhs, pair<int, int> rhs){
    double lhs_denst = in->i_values[lhs.first] + in->i_values[lhs.second] + in->p_values[lhs.first][lhs.second];
    lhs_denst /= (in->i_weights[lhs.first]+in->i_weights[lhs.second]);

    double rhs_denst = in->i_values[rhs.first] + in->i_values[rhs.second] + in->p_values[rhs.first][rhs.second];
    rhs_denst /= (in->i_weights[rhs.first]+in->i_weights[rhs.second]);

    return lhs_denst > rhs_denst;
}
