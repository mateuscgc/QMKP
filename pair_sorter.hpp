#ifndef PAIRSORTER
#define PAIRSORTER

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <set>

#include "input.hpp"

using namespace std;

class PairSorter {
public:
    PairSorter();
    PairSorter(const Input* pin, int a, int b, int k, const vector<int>& i_knap);

    bool operator<(const PairSorter& rhs) const;

    int a;
    int b;
    int k;

    int profit;
    double dnst;
};

#endif
