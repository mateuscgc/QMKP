#ifndef INPUT
#define INPUT
#include <bits/stdc++.h>

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

};

#endif
