//
// Created by burak on 21.02.2019.
//

#include "GreedySolver.h"
#include <vector>

SolverResult *GreedySolver::solve(TSPLIBInstance *instance) {
    auto res = new SolverResult;

    int n = instance->dimension;

    int *travelled = new int[n];
    for (int i = 1; i < n; ++i)
        travelled[i] = 0;
    travelled[0] = 1;

    auto tour = new std::vector<int>();
    tour->emplace_back(0);

    int total = 1;
    int objective = 0;
    int node = 0;
    int min_index = -1;
    while (total < n) {
        int min = -1;
        min_index = -1;
        for (int i = 0; i < n; ++i) {
            if (i == node || travelled[i] == 1)continue;
            if (min == -1) {
                min = instance->distance_matrix[node][i];
                min_index = i;
            } else if (min > instance->distance_matrix[node][i]) {
                min = instance->distance_matrix[node][i];
                min_index = i;
            }
        }
        objective += instance->distance_matrix[node][min_index];
        tour->emplace_back(min_index);
        node = min_index;
        total++;
        travelled[node] = 1;
    }

    objective += instance->distance_matrix[min_index][0];

    res->objective = objective;
    res->tour = tour;
    res->status = 0;
    return res;
}
