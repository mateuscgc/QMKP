#include "input.h"

Input::Input() {
    n = 0;
    k = 0;
}

void Input::load(const string& file_name) {
    ifstream inputFile(file_name);
    if(inputFile.is_open()) {
        string line;
        getline(inputFile, line);

        // Leitura da quantidade de itens
        inputFile >> n;

        // Leitura dos valores individuais
        i_values.resize(n, 0);
        for(int i = 0; i < n; i++) {
            inputFile >> i_values[i];
        }

        // Leitura dos valores dos pares
        p_values.resize(n, vector<int>(n));
        for(int i = 0; i < n-1; i++) {
            for(int j = i+1; j < n; j++) {
                inputFile >> p_values[i][j];
                p_values[j][i] = p_values[i][j];
            }
        }

        getline(inputFile, line);


        // Leitura da quantidade de mochilas
        inputFile >> k;
        k_caps.resize(k, 0);
        for(ini i = 0; i < k; i++) {
            inputFile >> k_caps[i];
        }

        // Leitura dos pesos dos itens
        for(int i = 0; i < n; i++) {
            inputFile >> i_weights[i];
        }
    }
}
