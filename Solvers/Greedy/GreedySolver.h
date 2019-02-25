//
// Created by burak on 21.02.2019.
//

#ifndef TSP_SOLVER_GREEDYSOLVER_H
#define TSP_SOLVER_GREEDYSOLVER_H


#include "../SolverBaseClass.h"

class GreedySolver : ConstructiveSolverBaseClass {
    SolverResult *solve(TSPLIBInstance *instance) override;

};


#endif //TSP_SOLVER_GREEDYSOLVER_H
