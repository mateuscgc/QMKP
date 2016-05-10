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

        k_values[knap] += in->i_values[item]; // Já está dentro do profit
        reference_solution += in->i_values[item];
        for(int i = 0; i < in->n; i++) {
            if(i_knap[i] == i_knap[item]) {
                k_values[i_knap[item]] += in->p_values[i][item];
                reference_solution += in->p_values[i][item];
            }
        }
        return 1;
    }
    return 0;
}

void Solution::add_pair(int a, int b, int k) {
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

        add_pair(next.a, next.b, next.k);
    }
}

int Solution::evaluate_solution() {
    int ans = 0;
    for(int k = 0; k < in->k; k++) {
        ans += k_values[k];
    }
    return ans;
}

int Solution::get_assignment_profit(int item, int knap) {
    int ans = 0;
    if(k_curr_caps[knap] >= in->i_weights[item]) {
        ans = in->i_values[item];
        for(int i = 0; i < in->n; i++) {
            ans += (i_knap[i] == knap)*in->p_values[i][item];
        }
    }
    return ans;
}

int Solution::reassign_item(int item, int forbidden_knap = -1) {
    int max = 0;
    int best_knap = -1;
    for(int k = 0; k < in->k; k++) {
        if(k != forbidden_knap) {
            int assignment_profit = get_assignment_profit(item, k);
            if(assignment_profit > max) {
                max = assignment_profit;
                best_knap = k;
            }
        }
    }

    if(best_knap > -1) {
        // cout << best_knap << endl;
        return add_item(item, best_knap);
    }
    return 0;
}

int Solution::remove_item(int item) {
    if(i_knap[item] > -1) {
        k_values[i_knap[item]] -= in->i_values[item];
        reference_solution -= in->i_values[item];
        for(int i = 0; i < in->n; i++) {
            if(i_knap[i] == i_knap[item]) {
                k_values[i_knap[item]] -= in->p_values[i][item];
                reference_solution -= in->p_values[i][item];
            }
        }
        k_curr_caps[i_knap[item]] += in->i_weights[item];
        i_knap[item] = -1;
        return 1;
    }
    return 0;
}

int Solution::get_heaviest_assigned_item() {
    int ans = -1;

    for(int i = 0; i < in->n; i++) {
        if (i_knap[i] > -1 && (ans == -1 || in->i_weights[i] > in->i_weights[ans]))
            ans = i;
    }
    return ans;
}

int Solution::get_best_shift_move(int knap, int forbidden_item) {
    int max = 0;
    int best = -1;
    int profit;
    for(int i = 0; i < in->n; i++) {
        if(i != forbidden_item && k_curr_caps[knap] > in->i_weights[i]) {
            profit = get_assignment_profit(i, knap);
            if(i_knap[i] > -1)
                profit -= get_assignment_profit(i, i_knap[i]);
            if(profit > max) {
                max = profit;
                best = i;
            }
        }
    }
    return best;
}

void Solution::restore_current_solution(int item, int first_knap) {
    pair<int, int> next;
    while(!moves.empty()) {
        next = moves.top();
        moves.pop();

        remove_item(next.first);
        if(next.second > -1)
            add_item(next.first, next.second);
    }

    remove_item(item);
    add_item(item, first_knap);
}

void Solution::local_search() {
    for(int i = 0; i < in->n; i++) {
        // cout << endl << "==> Current Solution " << current_solution << endl;
        // int fre = get_heaviest_assigned_item();
        int fre = i;
        if(fre > -1 && i_knap[fre] > -1) {
            int free_origin_knap = i_knap[fre];
            remove_item(fre);
            // cout << "Reference Solution after fisrt removal (" << fre << ") " << reference_solution << endl;

            stack< pair <int, int> > empty;
            swap(moves, empty); // Clear stack;

            for(int j = 0; j < CL; j++) {
                trial_solution = reference_solution;
                if(reassign_item(fre, free_origin_knap)) {
                    // trial_solution = evaluate_solution();
                    trial_solution = reference_solution;
                    // cout << "Free item was reassigned " << trial_solution << endl;
                    if(trial_solution > current_solution) {
                        current_solution = trial_solution; // Lidar com os itens adicionados ou não
                        return;
                    }
                    remove_item(fre);
                    // cout << "Current solution not improved, item removed " << reference_solution << endl;
                }

                int item_to_shift = get_best_shift_move(free_origin_knap, fre);
                // cout << "Shift item " << item_to_shift << endl;
                if(item_to_shift > -1) {
                    moves.push({item_to_shift, i_knap[item_to_shift]});
                    remove_item(item_to_shift);
                    add_item(item_to_shift, free_origin_knap);
                }
                // cout << "Reference solution after shift move " << reference_solution << endl;
            }
            restore_current_solution(fre, free_origin_knap);
        }
    }
}

void Solution::solve() {
    reference_solution = 0;
    construct_phase();
    current_solution = reference_solution;
    construct_solution = current_solution;
    best_solution = current_solution;

    k_values_construct = k_values;


    // cout << "Construct Fase solution " << current_solution << endl;

    while(true) {
        // cout << "NEW LOCAL SEARCH INTERACTION" << endl;
        local_search();
        // cout << "Solution after local search " <<  current_solution << endl;
        if(current_solution > best_solution) {
            best_solution = current_solution;
            // cout << "best solution improved!" << endl;;
        } else
            break;
    }
    local_search_solution = best_solution;
}
