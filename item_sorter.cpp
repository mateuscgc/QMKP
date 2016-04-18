#include "item_sorter.h"

using namespace std;

ItemSorter::ItemSorter(const Input* pin) : in(pin) {}

bool ItemSorter::operator()(int lhs, int rhs){
    double lhs_denst = in->i_values[lhs]/in->i_weights[lhs];
    double rhs_denst = in->i_values[rhs]/in->i_weights[rhs];
    if(lhs_denst == rhs_denst)
        return in->i_values[lhs] > in->i_values[rhs];
    return lhs_denst > rhs_denst;
}
