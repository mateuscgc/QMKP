#include "output.hpp"

Output::Output(const Input* pin):in(pin) {
    k_values.resize(in->k, 0);
}

//! Sobrecarda de operador
ostream& operator<<(ostream& os, const Output& out) {
    long long sum = 0;
    for(int i = 0; i < out.in->k; i++) {
        // os << out.k_values[i] << endl;
        sum += out.k_values[i];
    }
    os << sum;

  return os;
}
