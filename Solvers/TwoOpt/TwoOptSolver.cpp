//
// Created by burak on 26.02.2019.
//

#include <iostream>
#include "TwoOptSolver.h"

void singe_improve(int **distance_matrix, unsigned int n, Solution *solution) {
    int min_change;
    int min_i;
    int min_j;
    std::vector<unsigned int> *tour = solution->first;
    int cost = solution->second;

    do {
        min_change = 0;
        min_i = -1;
        min_j = -1;
        for (unsigned int i = 0; i < n - 2; ++i) {
            for (unsigned int j = i + 2; j < n; ++j) {
                int city_i = tour->at(i);
                int city_i1 = tour->at(i + 1);
                int city_j = tour->at(j);
                int city_j1 = (j < n - 1) ? tour->at(j + 1) : tour->at(0);
                int change =
                        distance_matrix[city_i][city_j] + distance_matrix[city_i1][city_j1] -
                        (distance_matrix[city_i][city_i1] + distance_matrix[city_j][city_j1]);
                if (change < min_change) {
                    min_change = change;
                    min_i = i;
                    min_j = j;
                }
            }
        }

        if (min_change < 0) {
            cost += min_change;
            solution->second = cost;
            min_i++;
            while (min_i < min_j) {
                unsigned int temp = tour->at(min_i);
                tour->at(min_i) = tour->at(min_j);
                tour->at(min_j) = temp;
                min_i++;
                min_j--;
            }
        }
    } while (min_change < 0);

}


Solutions *TwoOptSolver::improve(int **distance_matrix, unsigned int n, Solutions *previous_solutions) {
    for (auto item : *previous_solutions) {
        singe_improve(distance_matrix, n, item);
    }
    return previous_solutions;
}
