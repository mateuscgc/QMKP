#ifndef OUTPUT
#define OUTPUT

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "input.hpp"

using namespace std;

class Output {
public:
    Output(const Input* pin);

    const Input *in;

    vector<int> k_values;
    vector<int> k_values_construct;
    int construct_solution;
    int local_search_solution;

    friend ostream& operator<<(ostream&, const Output &);
};

#endif
