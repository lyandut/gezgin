//
// Created by burak on 25.02.2019.
//

#include "NGreedySolver.h"

//solves greedy algorithm for n starting points
//removes the same tours
Solutions *NGreedySolver::construct(int **distance_matrix, unsigned int n) {

    auto result = new Solutions();

    for (int starting_node = 0; starting_node < n; ++starting_node) {
        int *travelled = new int[n];
        for (int i = 0; i < n; ++i)
            travelled[i] = 0;
        travelled[starting_node] = 1;

        auto tour = new std::vector<unsigned int>();
        tour->emplace_back(starting_node);

        int total = 1;
        int objective = 0;
        int node = starting_node;
        int min_index = -1;
        while (total < n) {
            int min = -1;
            min_index = -1;
            for (int i = 0; i < n; ++i) {
                if (i == node || travelled[i] == 1)continue;
                if (min == -1) {
                    min = distance_matrix[node][i];
                    min_index = i;
                } else if (min > distance_matrix[node][i]) {
                    min = distance_matrix[node][i];
                    min_index = i;
                }
            }
            objective += distance_matrix[node][min_index];
            tour->emplace_back(min_index);
            node = min_index;
            total++;
            travelled[node] = 1;
        }

        objective += distance_matrix[min_index][starting_node];

        auto sol = new Solution;
        sol->second = objective;
        sol->first = tour;
        result->emplace_back(sol);
    }


    return result;
}
