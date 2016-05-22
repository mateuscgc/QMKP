#include "output.hpp"

Output::Output(const Input* pin):in(pin) {
    k_values.resize(in->k, 0);
    k_values_construct.resize(in->k, 0);
}

//! Sobrecarda de operador
ostream& operator<<(ostream& os, const Output& out) {
    long long sum = 0;
    os << "Tempo " << out.total_time << " Num of local search iterations " << out.num_lc << endl;
    os << "Construt phase solution " << out.construct_solution << endl;
    for(int i = 0; i < out.in->k; i++) {
        os << out.k_values[i] << endl;
        // sum += out.k_values[i];
    }
    os << "Final solution " << out.best_solution << endl;

  return os;
}
