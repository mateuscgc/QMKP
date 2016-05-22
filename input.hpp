#ifndef INPUT
#define INPUT
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <set>
#include <fstream>

using namespace std;

class Input {

    public:

        Input();

        Input(const string& file_name) {
            load(file_name);
        }

        void load(const string& file_name);

        int n;
        vector<int> i_values;
        vector<int> i_weights;
        vector<vector<int>> p_values;
        int k;
        vector<int> k_caps;
        double time_limit;

};

#endif
