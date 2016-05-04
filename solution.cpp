#include "solution.hpp"

Solution::Solution(const Input* pin):Output(pin) {
    k_curr_caps.resize(in->k, 0);
    for(int i = 0; i < in->k; i++)
        k_curr_caps[i] = in->k_caps[i];
    i_knap.resize(in->n, -1);
}

void Solution::update_pq(int k) {
    for(int i = 0; i < in->n; i++) {
        for(int j = i; j < in->n; j++) {
            if(i_knap[i] == -1 && i_knap[j] == -1) {
                PairSorter aux(in, i, j, k, i_knap);
                p_list.push(aux);
            }
        }
    }
}

int Solution::add_item(int item, int knap)   {
    if(i_knap[item] == -1 && k_curr_caps[knap] >=  in->i_weights[item]) {
        i_knap[item] = knap;
        k_curr_caps[knap] -= in->i_weights[item];
        // k_values[knap] += in->i_values[item]; // Já está dentro do profit
        return 1;
    }
    return 0;
}

void Solution::add_pair(int a, int b, int k, int profit) {
    // Mochila atual dos dois itens do par
    int f_knap = i_knap[a];
    int s_knap = i_knap[b];
    // cout << a << " --> " << f_knap << endl;
    // cout << b << " --> " << s_knap << endl;
    // cout << "============" << endl << endl;


    if (f_knap == -1 && s_knap == -1) { // Caso nenhum dos dois itens esteja em mochila
        if (k_curr_caps[k] >= in->i_weights[a] + in->i_weights[b]) {
            add_item(a, k);
            add_item(b, k);
            k_values[k] += profit;
            update_pq(k);
        }
    }
}

void Solution::construct_phase() {
    // Construção de lista de pares não zeros
    for(int i = 0; i < in->n; i++) {
        for(int j = i; j < in->n; j++) {
            for(int k = 0; k < in->k; k++) {
                if(in->p_values[i][j] > 0 || i == j) {
                    PairSorter aux(in, i, j, k, i_knap);
                    p_list.push(aux);
                }
            }
        }
    }

    PairSorter aux;
    PairSorter next;
    while(!p_list.empty()) {

        // int i = 0;
        // priority_queue<PairSorter> pq(p_list);
        // while(i < 10) {
        //     aux = pq.top();
        //     pq.pop();
        //     i++;
        //     cout << aux.dnst << endl;
        // }

        next = p_list.top();
        p_list.pop();
        // cout << "--> " << next.profit << " - " << next.dnst << " - " << next.k << endl;



        add_pair(next.a, next.b, next.k, next.profit);
    }
}

void Solution::solve() {
    construct_phase();
}
