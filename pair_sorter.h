#ifndef PAIRSORTER
#define PAIRSORTER

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <set>

#include "input.h"

using namespace std;

class PairSorter {
public:
    PairSorter(const Input* pin);

    bool operator()(pair<int, int> lhs, pair<int, int> rhs);

    const Input *in;
};

#endif
