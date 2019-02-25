//
// Created by burak on 21.02.2019.
//

#ifndef TSP_SOLVER_SOLVERBASECLASS_H
#define TSP_SOLVER_SOLVERBASECLASS_H


#include <vector>
#include "../TSPLIBInstance/TSPLIBInstance.h"

struct SolverResult {
    int status;
    int objective;
    std::vector<int> *tour;
};

class SingleChainSolverBaseClass {};

class SCConstructiveSolverBaseClass : public SingleChainSolverBaseClass {
public:
    virtual SolverResult *solve(TSPLIBInstance *instance) = 0;

};

class SCImprovingSolverBaseClass : public SingleChainSolverBaseClass {
public:
    virtual SolverResult *improve(TSPLIBInstance *instance, std::vector<int> *starting_route) = 0;
};


#endif //TSP_SOLVER_SOLVERBASECLASS_H
