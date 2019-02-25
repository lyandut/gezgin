//
// Created by burak on 21.02.2019.
//

#ifndef TSP_SOLVER_GREEDYSOLVER_H
#define TSP_SOLVER_GREEDYSOLVER_H


#include "../SingleChainSolverBaseClass.h"

class GreedySolver : SCConstructiveSolverBaseClass {
public:
    SolverResult *solve(TSPLIBInstance *instance) override;

};


#endif //TSP_SOLVER_GREEDYSOLVER_H
