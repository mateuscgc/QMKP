#include <bits/stdc++.h>
#include "../input.hpp"

using namespace std;
Input in;
vector< vector<double> > dnst;
vector<int> k_curr_caps;
vector<int> i_knap;
vector<int> k_values;

void update(int item, int k) {
    for(int i = 0; i < in.n; i++) {
        dnst[i][k] += (double)in.p_values[item][i] / (double)in.i_weights[i];
    }
}

int add_item(int item, int knap)   {
    // cout << k_curr_caps[knap] << " >= " << in.i_weights[item] << endl;
    if(item > -1 && i_knap[item] == -1 && k_curr_caps[knap] >=  in.i_weights[item]) {
        i_knap[item] = knap;
        k_curr_caps[knap] -= in.i_weights[item];
        k_values[knap] += in.i_values[item];
        for(int i = 0; i < in.n; i++)
            if(i_knap[i] == knap)
                k_values[knap] += in.p_values[item][i];
        update(item, knap);
        return 1;
    }
    return 0;
}

int getbest(int k) {
    int best = -1;
    int ans = -1;
    for(int j = 0; j < in.n; j++) {
        if (i_knap[j] == -1 && dnst[j][k] > best) {
            best = dnst[j][k];
            ans = j;
        }
    }
    return ans;
}

void solve() {

    k_curr_caps.clear();
    k_curr_caps.resize(in.k, 0);
    for(int i = 0; i < in.k; i++) {
        k_curr_caps[i] = in.k_caps[i];
    }

    i_knap.clear();
    i_knap.resize(in.n, -1);

    k_values.clear();
    k_values.resize(in.k, 0);

    dnst.clear();
    dnst.resize(in.n, vector<double>(in.k, 0));

    // for(int i = 0; i < in.n; i++) {
        // cout << in.i_weights[i] << endl;
    // }

    for(int i = 0; i < in.n; i++) {
        for(int j = 0; j < in.k; j++) {
            dnst[i][j] = (double)in.i_values[i] / (double)in.i_weights[i];
            // cout << dnst[i][j] << " ";
            // cout << in.i_weights[i] << " ";
        }
        // cout << endl;
    }

    // for(int i = 0; i < in.n; i++) {
        // cout << in.i_weights[i] << endl;
    // }

    for(int k = 0; k < in.k; k++) {
        while(add_item(getbest(k), k));
    }
}

void get_intance_file_name(char *in, int n, int d, int k, int i) {
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

    cout << "<!DOCTYPE html>" << endl;
    cout << "<html>" << endl;
    cout << "    <body>" << endl;
    cout << "        <table>" << endl;
    cout << "            <thead>" << endl;
    cout << "                <style> table, th, td { border: 1px solid black; } td { padding: 10px; }</style>" << endl;
    cout << "                <tr>" << endl;
    cout << "                    <th>n</th>" << endl;
    cout << "                    <th>m</th>" << endl;
    cout << "                    <th>I</th>" << endl;
    cout << "                    <th>c</th>" << endl;
    cout << "                    <th>Best</th>" << endl;
    cout << "                </tr>" << endl;
    cout << "            </thead>" << endl;
    cout << "            <tbody>" << endl;

    int num_k[] = {3, 5, 10};

    for(int n = 100; n <= 200; n += 100) {
        for(int d = 25; d <= 75; d += 50) {
            for(int ki = 0; ki <= 2; ki++) {
                for(int i = 1; i <= 5; i++) {
                    // char instance_file_name[100] = "../instances/jeu_100_25_10_1.txt";
                    char instance_file_name[100] = "../instances/jeu";
                    get_intance_file_name(instance_file_name, n, d, num_k[ki], i);

                    // cout << instance_file_name << endl;
                    in.load(instance_file_name);

                    solve();

                    cout << "                <tr>" << endl;
                    cout << "                    <td rowspan=\" " << num_k[ki]+1 << " \">" << n << "</td>" << endl;
                    cout << "                    <td rowspan=\" " << num_k[ki]+1 << " \">" << num_k[ki] << "</td>" << endl;
                    cout << "                    <td rowspan=\" " << num_k[ki]+1 << " \">" << i << "</td>" << endl;
                    cout << "                    <td rowspan=\" " << num_k[ki]+1 << " \">" << in.k_caps[0] << "</td>" << endl;
                    cout << "                    <td>" << k_values[0] << "</td>" << endl;
                    cout << "                </tr>" << endl;

                    long long sum = k_values[0];
                    for(int k = 1; k < in.k; k++) {
                        cout << "                    <tr><td>" << k_values[k] << "</td></tr>" << endl;
                        sum += k_values[k];
                    }
                    // cout << "sum " << sum << endl << endl;


                    cout << "                    <tr><td><b>" << sum << "</b></td></tr>" << endl;

                }
            }
        }
    }

    cout << "            </tbody>" << endl;
    cout << "        </table>" << endl;
    cout << "    </body>" << endl;
    cout << "</html>" << endl;

    return 0;
}
