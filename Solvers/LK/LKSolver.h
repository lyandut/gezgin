//
// Created by burak on 21.02.2019.
//

#ifndef TSP_SOLVER_LKSOLVER_H
#define TSP_SOLVER_LKSOLVER_H


#include "../SingleChainSolverBaseClass.h"

class LKSolver : public SCImprovingSolverBaseClass {


public:
    SolverResult *improve(TSPLIBInstance *instance, std::vector<int> * starting_tour) override;
};


#endif //TSP_SOLVER_LKSOLVER_H
