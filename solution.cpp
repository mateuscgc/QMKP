#include "solution.h"

Solution::Solution(const Input* pin):Output(pin) {
    k_curr_caps.resize(in->k, 0);
    for(int i = 0; i < in->k; i++)
        k_curr_caps[i] = in->k_caps[i];
    i_knap.resize(in->n, -1);
    i_desc.resize(in->n, )
}

int Solution::add_item(int item, int knap) {
    if(i_knap[item] == -1 && k_curr_caps[knap] >=  in->i_weights[item]) {
        i_knap[item] = knap;
        k_curr_caps[knap] -= in->i_weights[item];
        k_values[knap] += in->i_values[item];
        return 1;
    }
    return 0;
}

int Solution::add_pair(int par) {
    // Mochila atual dos dois itens do par
    int f_knap = i_knap[p_list[par].first];
    int s_knap = i_knap[p_list[par].second];

    if (f_knap == -1 && s_knap == -1) { // Caso nenhum dos dois itens esteja em mochila
        for(int i = 0; i < in->k; i++) { // Encontra uma mochila que tenha capacidade para os dois itens
            if (k_curr_caps[i] >= in->i_weights[p_list[par].first] + in->i_weights[p_list[par].second]) {
                if (add_item(p_list[par].first, i) && add_item(p_list[par].second, i))
                    k_values[i] += in->p_values[p_list[par].first][p_list[par].second];
            }
        }
    } else if(f_knap > -1) { // Se apenas o primeiro item estiver em uma mochila
        if (add_item(p_list[par].second, f_knap))
            k_values[f_knap] += in->p_values[p_list[par].first][p_list[par].second];
    } else if (s_knap > -1) { // Se apenas o segundo item estiver em uma mochila
        if (add_item(p_list[par].first, s_knap))
            k_values[s_knap] += in->p_values[p_list[par].first][p_list[par].second];
    }

    return (par+1)%p_list.size();
}

void Solution::construct_phase() {
    // Construção de lista de pares não zeros
    for(int i = 0; i < in->n; i++) {
        for(int j = 0; j < in->n; j++) {
            if(in->p_values[i][j] >= 0)
                p_list.insert({i, j});
        }
    }

    int next = 0;
    while(next = add_pair(next)); // Preenche mochilas considerando valores quadraticos

    for(int x : i_desc) { // Preenche mochilas com os itens restantes
        for(int i = 0; i < in->k; i++) {
            if(add_item(x, i))
                break;
        }
    }
}

void Solution::solve() {

    construct_phase();

}
