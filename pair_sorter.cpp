#include "pair_sorter.hpp"

using namespace std;

PairSorter::PairSorter() {
    this->a = 0; // item
    this->b = 0; // item
    this->k = 0; // mochila
}

PairSorter::PairSorter(const Input* pin, int a, int b, int k, const vector<int>& i_knap) {
    this->a = a; // item
    this->b = b; // item
    this->k = k; // mochila

    profit = pin->i_values[a] + pin->i_values[b] + pin->p_values[a][b];
    for(int i = 0; i < pin->n; i++) {
        profit += (i_knap[i] == this->k) * pin->p_values[i][a];
        if(a != b)
           profit += (i_knap[i] == this->k) * pin->p_values[i][b];
    }
    dnst = (double)profit / (pin->i_weights[a] + pin->i_weights[b]);
}

bool PairSorter::operator<(const PairSorter& rhs) const {
    if(this->dnst == rhs.dnst) {
        if(this->profit == rhs.profit) {
            return this->k > rhs.k;
        }
        return this->profit < rhs.profit;
    }
    return this->dnst < rhs.dnst;
}
