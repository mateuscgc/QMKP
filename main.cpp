#include <bits/stdc++.h>
#include "input.h"
#include "output.h"
#include "solution.h"

using namespace std;

void get_intance_file_name(char *in, int n, int d, int i) {
    string aux = to_string(n);
    strcat(in, "_");
    strcat(in, aux.c_str());

    aux = to_string(d);
    strcat(in, "_");
    strcat(in, aux.c_str());

    aux = to_string(k);
    strcat(in, "_");
    strcat(in, aux.c_str());


    aux = to_string(i);
    strcat(in, "_");
    strcat(in, aux.c_str());

    strcat(in, ".txt");
}

int main() {

    for(int n = 100; n <= 200; n += 100) {
        for(int d = 25; d <= 75; d += 50) {
            for(int i = 1; i <= 5; i++) {
                char instance_file_name[100] = "jeu";
                get_intance_file_name(instance_file_name, n, d, i);

                Input in;
                in.load(instance_file_name);

                // for(int l = 0; l < in.n-1; l++) {
                //     for(int j = l+1; j < in.n; j++) {
                //         cout << in.p_values[l][j] << " ";
                //     }
                //     cout << endl;
                // }

                Solution s(&in);
                s.solve();

                cout << s << endl;
            }
        }
    }

    return 0;
}

