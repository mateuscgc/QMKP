#include <bits/stdc++.h>

using namespace std;

int k = 10;

void get_intance_file_name(char *in, char *out, int n, int d, int i) {
    string aux = to_string(n);
    strcat(in, "_");
    strcat(in, aux.c_str());

    strcat(out, "_");
    strcat(out, aux.c_str());

    aux = to_string(d);
    strcat(in, "_");
    strcat(in, aux.c_str());

    strcat(out, "_");
    strcat(out, aux.c_str());

    aux = to_string(k);
    strcat(out, "_");
    strcat(out, aux.c_str());


    aux = to_string(i);
    strcat(in, "_");
    strcat(in, aux.c_str());

    strcat(out, "_");
    strcat(out, aux.c_str());

    strcat(in, ".txt");
    strcat(out, ".txt");
}

int main() {


    for(int n = 100; n <= 200; n += 100) {
        for(int d = 25; d <= 75; d += 50) {
            for(int i = 1; i <= 5; i++) {
                char instance_input[100] = "jeu";
                char instance_output[100] = "../jeu";
                get_intance_file_name(instance_input, instance_output, n, d, i);

                ifstream inputFile (instance_input);
                ofstream outputFile (instance_output);
                if(inputFile.is_open() && outputFile.is_open()) {

                    // inputFile >> instance_name;
                    // cout << instance_name << endl;

                    // inputFile >> n;

                    string line;
                    for(int j = n+4; j >= 1; j--) {
                        getline(inputFile, line);
                        outputFile << line << endl;

                    }
                    getline(inputFile, line);
                    int weights[n];
                    long long sum = 0;
                    for(int j = 0; j < n; j++) {
                        inputFile >> weights[j];
                        sum += weights[j];
                    }

                    outputFile << k << endl;
                    outputFile << (int)(sum*0.8/k);
                    for(int j = 1; j < k; j++) {
                        outputFile << " " << (int)(sum*0.8/k);
                    }
                    outputFile << endl;

                    outputFile << weights[0];
                    for(int j = 1; j < n; j++) {
                        outputFile << " " << weights[j];
                    }
                    outputFile << endl;

                    inputFile.close();
                }




            }
        }
    }

    return 0;
}
