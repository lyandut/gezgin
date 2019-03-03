//
// Created by burak on 26.02.2019.
//

#ifndef TSP_SOLVER_TWOOPTSOLVER_H
#define TSP_SOLVER_TWOOPTSOLVER_H


#include "../ImprovementHeuristic.h"

class TwoOptSolver : public ImprovementHeuristic {
public:
    Solutions *improve(int **distance_matrix, unsigned int n, Solutions *previous_solutions) override;
};


#endif //TSP_SOLVER_TWOOPTSOLVER_H
