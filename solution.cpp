#include "solution.hpp"

Solution::Solution(const Input* pin):Output(pin) {
    // srand(time(NULL));
    srand(1);
    k_curr_caps.resize(in->k, 0);
    for(int i = 0; i < in->k; i++)
        k_curr_caps[i] = in->k_caps[i];
    i_knap.resize(in->n, -1);
}

void Solution::update_pq(int k) {
    for(int i = 0; i < in->n; i++) {
        for(int j = i; j < in->n; j++) {
            if(i_knap[i] == -1 && i_knap[j] == -1 && (in->p_values[i][j] > 0 || i == j)) {
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
    if (i_knap[a] == -1 && i_knap[b] == -1) { // Caso nenhum dos dois itens esteja em mochila
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
                if(i_knap[i] == -1 && i_knap[j] == -1 && (in->p_values[i][j] > 0 || i == j)) {
                    PairSorter aux(in, i, j, k, i_knap);
                    p_list.push(aux);
                }
            }
        }
    }

    PairSorter aux;
    PairSorter next;
    while(!p_list.empty()) {

        next = p_list.top();
        p_list.pop();

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

int Solution::get_best_shift_move(int knap, int forbidden_item, int last_item) {
    int max = 0;
    int best = -1;
    int profit;
    for(int i = 0; i < in->n; i++) {
        if(i != forbidden_item && i != last_item && k_curr_caps[knap] >= in->i_weights[i]) {
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

void Solution::get_best_swap_move(int forbidden_item, int& best1, int& best2) {
    int max = 0;
    best1 = -1;
    best2 = -1;
    int profit;
    for(int i = 0; i < in->n; i++) {
        for(int j = 0; j < in->n; j++) {
            if (i != j && i != forbidden_item && j != forbidden_item) {
                if((i_knap[i] == -1 || k_curr_caps[i_knap[i]] + in->i_weights[i] >= in->i_weights[j])
                && (i_knap[j] == -1 || k_curr_caps[i_knap[j]] + in->i_weights[j] >= in->i_weights[i])) {
                    profit = 0;
                    if (i_knap[j] > -1) {
                        profit += get_assignment_profit(i, i_knap[j]);
                        profit -= get_assignment_profit(j, i_knap[j]);
                    }
                    if (i_knap[i] > -1) {
                        profit += get_assignment_profit(j, i_knap[i]);
                        profit -= get_assignment_profit(i, i_knap[i]);
                    }

                    if(profit > max) {
                        max = profit;
                        best1 = i;
                        best2 = j;
                    }
                }
            }
        }
    }
}

void Solution::swap_move(int i1, int i2) {
    int aux1 = i_knap[i1];
    remove_item(i1);

    int aux2 = i_knap[i2];
    remove_item(i2);

    if (aux1 > -1) add_item(i2, aux1);
    if (aux2 > -1) add_item(i1, aux2);
}

void Solution::restore_current_solution(int item, int first_knap) {
    pair<double, int> next;
    while(!moves.empty()) {
        next = moves.top();
        moves.pop();

        if (fmod(next.first, 1) == 0) { // Se foi um movimento de shift
            remove_item(next.first);
            if(next.second > -1)
                add_item(next.first, next.second);
        } else { // Se foi um movimento de swap
            next.first = (int)next.first;
            swap_move(next.first, next.second);
        }

    }

    remove_item(item);
    add_item(item, first_knap);
}

int Solution::local_search(int last) {
    int item_to_shift = -1;
    int aux;
    pair<int, int> items_to_swap;
    for(int i = (last+1) % in->n; i != last; i++, i %= in->n) {
        // cout << endl << "==> Current Solution " << current_solution << endl;
        // int fre = get_heaviest_assigned_item();
        int fre = i;
        if(i_knap[fre] > -1) {
            int free_origin_knap = i_knap[fre];
            int last_free_knap = free_origin_knap;
            remove_item(fre);
            // cout << "Reference Solution after first removal (" << fre << ") " << reference_solution << endl;

            stack< pair <double, int> > empty;
            swap(moves, empty); // Clear stack;

            // int lower_finder, upper_finder;
            for(int j = 0; j < CL; j++) {
                trial_solution = reference_solution;
                if(reassign_item(fre, free_origin_knap)) {
                    // trial_solution = evaluate_solution();
                    trial_solution = reference_solution;
                    // cout << "Free item was reassigned " << trial_solution << endl;
                    if(trial_solution > current_solution) {
                        current_solution = trial_solution; // Lidar com os itens adicionados ou não
                        return i;
                    }
                    remove_item(fre);
                    // cout << "Current solution not improved, item removed " << reference_solution << endl;
                }
                if (((double) rand() / (RAND_MAX)) <= (double)4/5) { // Greedy shift move
                    item_to_shift = get_best_shift_move(last_free_knap, fre, item_to_shift);
                    // cout << "Knap " << last_free_knap <<  " Shift item " << item_to_shift << endl;

                    if(item_to_shift > -1) {
                        moves.push({item_to_shift, i_knap[item_to_shift]});
                        aux = i_knap[item_to_shift];
                        remove_item(item_to_shift);
                        add_item(item_to_shift, last_free_knap);
                        last_free_knap = aux;
                        if(last_free_knap == -1) { // Caso o ultimo shift tenha sido de um item fora de mochila, atualiza para mochila mais vazia
                            for(int k = 0; k < in->k; k++) {
                                if(last_free_knap == -1 || k_curr_caps[k] > k_curr_caps[last_free_knap]) {
                                    last_free_knap = k;
                                }
                            }
                        }
                    }
                } else { // Greedy swap move
                    get_best_swap_move(fre, items_to_swap.first, items_to_swap.second);
                    // cout << "===> Swap move " << items_to_swap.first << " " << items_to_swap.second << endl;

                    if(items_to_swap.first > -1) { // Se tem swap
                        moves.push({items_to_swap.first + 0.1, items_to_swap.second});
                        swap_move(items_to_swap.first, items_to_swap.second);
                    }
                }
                // } else { // Random shift move
                //     item_to_shift = -1;
                //     lower_finder = rand() % in->n; // Randomize number in items range
                //     upper_finder = lower_finder;
                //     while(item_to_shift == -1 && (upper_finder < in->n || lower_finder >= 0)) { // find first valid item for shift
                //         if(lower_finder >= 0 && lower_finder != fre && k_curr_caps[free_origin_knap] > in->i_weights[lower_finder])
                //             item_to_shift = lower_finder;
                //         else if(upper_finder < in->n && upper_finder != fre && k_curr_caps[free_origin_knap] > in->i_weights[upper_finder])
                //             item_to_shift = upper_finder;
                //         lower_finder--;
                //         upper_finder++;
                //     }
                // }

                // cout << "Reference solution after shift / swap move " << reference_solution << endl;
            }
            restore_current_solution(fre, free_origin_knap);
        }
    }
}

void Solution::random_remove(int num_of_removals) {
    int item;
    for(int i = 0; i < num_of_removals; i++) {
        item = rand() % in->n;
        remove_item(item);
    }
}

void Solution::adaptive_perturbation() {
    // cout << "reference solution before removals " << reference_solution << endl;
    random_remove(in->n/20);
    // cout << "reference solution after removals " << reference_solution << endl;
    construct_phase();

    // cout << "reference solution after reconstruction " << reference_solution << endl;
    current_solution = reference_solution;
}

void Solution::solve() {
    begin = clock();

    reference_solution = 0;
    construct_phase();
    current_solution = reference_solution;
    construct_solution = current_solution;
    best_local_search_solution = current_solution;
    best_solution = current_solution;

    k_values_construct = k_values;

    // cout << "Construct Fase solution " << current_solution << endl;

    // no_improv_iter = 0;
    int last = 0;
    num_lc = 0;
    while (double(clock() - begin) / CLOCKS_PER_SEC < in->time_limit) {
        num_lc++;
        while(true) { // Ejection chain local search phase
            // cout << endl << "NEW LOCAL SEARCH INTERACTION" << endl;
            last = local_search(last);
            // cout << endl << "Solution after local search " <<  current_solution << endl;
            if(current_solution > best_local_search_solution) {
                best_local_search_solution = current_solution;
                // cout << "local search solution improved!" << endl;
            } else
                break;
        }

        if(best_local_search_solution > best_solution) { // Verifica se a solução gerada na busca local é melhor que a melhor solução atual
            // cout << "Best solution improved!!!" << endl;
            best_solution = best_local_search_solution;
            // no_improv_iter = 0;
        }
        // else {
            // no_improv_iter++;
        // }
        adaptive_perturbation();
        if(current_solution > best_solution) {
            best_solution = current_solution;
            // cout << "Perturbation improved best solution!!" << endl;
        }
    }
    // total_time = double(clock() - begin) / CLOCKS_PER_SEC;
    // cout << "NUMBER OF LOCAL SEARCH ITERATIONS " << num_lc << endl;

    // cout << "BEST SOLUTION " << best_solution << endl;
}
