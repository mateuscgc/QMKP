#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include "input.hpp"
#include "output.hpp"
#include "solution.hpp"

using namespace std;

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

    // cout << "<!DOCTYPE html>" << endl;
    // cout << "<html>" << endl;
    // cout << "    <body>" << endl;
    // cout << "        <table>" << endl;
    // cout << "            <thead>" << endl;
    // cout << "                <style> table, th, td { border: 1px solid black; } td { padding: 10px; }</style>" << endl;
    // cout << "                <tr>" << endl;
    // cout << "                    <th>n</th>" << endl;
    // cout << "                    <th>m</th>" << endl;
    // cout << "                    <th>I</th>" << endl;
    // cout << "                    <th>c</th>" << endl;
    // cout << "                    <th>Time</th>" << endl;
    // cout << "                    <th>Construct</th>" << endl;
    // cout << "                    <th>Local Search</th>" << endl;
    // cout << "                </tr>" << endl;
    // cout << "            </thead>" << endl;
    // cout << "            <tbody>" << endl;

    // int num_k[] = {3, 5, 10};

    // for(int d = 25; d <= 75; d += 50) {
    //     for(int n = 100; n <= 200; n += 100) {
    //         for(int ki = 0; ki <= 2; ki++) {
    //             for(int i = 1; i <= 5; i++) {
                    char instance_file_name[100] = "instances/jeu_100_25_10_3.txt";
    //                 cout << "fgd" << endl;
    //                 char instance_file_name[100] = "instances/jeu";
    //                 get_intance_file_name(instance_file_name, n, d, num_k[ki], i);

                    Input in;
                    in.load(instance_file_name);

                    Solution s(&in);
                    s.solve();

                    cout << s << endl;

    //                 cout << "                <tr>" << endl;
    //                 cout << "                    <td rowspan=\" " << num_k[ki]+1 << " \">" << n << "</td>" << endl;
    //                 cout << "                    <td rowspan=\" " << num_k[ki]+1 << " \">" << num_k[ki] << "</td>" << endl;
    //                 cout << "                    <td rowspan=\" " << num_k[ki]+1 << " \">" << i << "</td>" << endl;
    //                 cout << "                    <td rowspan=\" " << num_k[ki]+1 << " \">" << in.k_caps[0] << "</td>" << endl;
    //                 cout << fixed << setprecision(2) << "                    <td rowspan=\" " << num_k[ki]+1 << " \">" << in.time_limit << "</td>" << endl;
    //                 cout << "                    <td>" << s.k_values_construct[0] << "</td>" << endl;
    //                 cout << "                    <td>" << s.k_values[0] << "</td>" << endl;
    //                 cout << "                </tr>" << endl;

    //                 for(int k = 1; k < in.k; k++) {
    //                     cout << "                   <tr>" << endl;
    //                     cout << "                       <td>" << s.k_values_construct[k] << "</td>" << endl;
    //                     cout << "                       <td>" << s.k_values[k] << "</td>" << endl;
    //                     cout << "                   </tr>" << endl;
    //                 }
    //                 cout << "                   <tr>" << endl;
    //                 cout << "                       <td><b>" << s.construct_solution << "</b></td>" << endl;
    //                 cout << "                       <td><b>" << s.best_solution << "</b></td>" << endl;
    //                 cout << "                   </tr>" << endl;
    //             }
    //         }
    //     }
    // }

    // cout << "            </tbody>" << endl;
    // cout << "        </table>" << endl;
    // cout << "    </body>" << endl;
    // cout << "</html>" << endl;

    return 0;
}

