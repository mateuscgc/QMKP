#ifndef OUTPUT
#define OUTPUT

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "input.h"

using namespace std;

class Output {
public:
    Output(const Input* pin);

    const Input *in;

    vector<int> k_values;

    friend ostream& operator<<(ostream&, const Output &);
};

#endif
