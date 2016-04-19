#include "solution.hpp"

Solution::Solution(const Input* pin):Output(pin) {
    k_curr_caps.resize(in->k, 0);
    for(int i = 0; i < in->k; i++)
        k_curr_caps[i] = in->k_caps[i];
    i_knap.resize(in->n, -1);
}

int Solution::add_item(int item, int knap)   {
    if(i_knap[item] == -1 && k_curr_caps[knap] >=  in->i_weights[item]) {
        i_knap[item] = knap;
        k_curr_caps[knap] -= in->i_weights[item];
        k_values[knap] += in->i_values[item];
        return 1;
    }
    return 0;
}

void Solution::add_pair(pair<int, int> par) {
    // Mochila atual dos dois itens do par
    int f_knap = i_knap[par.first];
    int s_knap = i_knap[par.second];

    if (f_knap == -1 && s_knap == -1) { // Caso nenhum dos dois itens esteja em mochila
        for(int i = 0; i < in->k; i++) { // Encontra uma mochila que tenha capacidade para os dois itens
            if (k_curr_caps[i] >= in->i_weights[par.first] + in->i_weights[par.second]) {
                if (add_item(par.first, i) && add_item(par.second, i))
                    k_values[i] += in->p_values[par.first][par.second];
            }
        }
    } else if(f_knap > -1) { // Se apenas o primeiro item estiver em uma mochila
        if (add_item(par.second, f_knap))
            k_values[f_knap] += in->p_values[par.first][par.second];
    } else if (s_knap > -1) { // Se apenas o segundo item estiver em uma mochila
        if (add_item(par.first, s_knap))
            k_values[s_knap] += in->p_values[par.first][par.second];
    }
}

void Solution::construct_phase() {
    // Construção de lista de pares não zeros
    for(int i = 0; i < in->n; i++) {
        for(int j = i; j < in->n; j++) {
            if(in->p_values[i][j] > 0 || i == j)
                p_list.push_back({i, j});
        }
    }
    PairSorter p_sorter(in);
    sort(p_list.begin(), p_list.end(), p_sorter);

    for(pair<int, int> next : p_list) { // Preenche mochilas considerando valores quadraticos
        // double next_denst = in->i_values[next.first] + in->i_values[next.second] + in->p_values[next.first][next.second];
        // next_denst /= (in->i_weights[next.first]+in->i_weights[next.second]);
        // cout << "(" << next.first << ", " << next.second << ")" << " -> " << next_denst << endl;
        add_pair(next);
    }

}

void Solution::solve() {
    construct_phase();
}
