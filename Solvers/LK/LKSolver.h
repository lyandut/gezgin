//
// Created by burak on 21.02.2019.
//

#ifndef TSP_SOLVER_LKSOLVER_H
#define TSP_SOLVER_LKSOLVER_H


#include "../SolverBaseClass.h"

class LKSolver : public ImprovingSolverBaseClass {


public:
    SolverResult *improve(TSPLIBInstance *instance, std::vector<int> * starting_tour) override;
};


#endif //TSP_SOLVER_LKSOLVER_H
