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
    double elapsed_secs;
    clock_t begin;
    int num_lc;
    int best_solution;
    double total_time;

    friend ostream& operator<<(ostream&, const Output &);
};

#endif
