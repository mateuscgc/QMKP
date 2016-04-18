#ifndef ITEMSORTER
#define ITEMSORTER

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <set>

#include "input.h"

using namespace std;

class ItemSorter {
public:
    ItemSorter(const Input* pin);

    bool operator()(int lhs, int rhs);

    const Input *in;
};

#endif
