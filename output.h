#ifndef OUTPUT
#define OUTPUT

#include <bits/stdc++.h>

using namespace std;

class Output {
public:
    Output(const Input* pin);

    const Input* in;

    vector<int> k_values;

    friend ostream& operator<<(ostream&, const Output &);
};

#endif
