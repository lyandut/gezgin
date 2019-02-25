//
// Created by burak on 25.02.2019.
//


#ifndef TSP_SOLVER_MULTICHAINSOLVERBASECLASS_H
#define TSP_SOLVER_MULTICHAINSOLVERBASECLASS_H

#include <vector>
#include "../TSPLIBInstance/TSPLIBInstance.h"


struct SolverResult {
    int status;
    int objective;
    std::vector<int> *tour;
};

class MultiChainSolverBaseClass {

};


class MCConstructiveSolverBaseClass : public MultiChainSolverBaseClass{
public:
    virtual std::vector<SolverResult> *solve(TSPLIBInstance *instance) = 0;

};

class MCImprovingSolverBaseClass : public MultiChainSolverBaseClass {
public:
    virtual std::vector<SolverResult> *improve(TSPLIBInstance *instance, std::vector<int> *starting_route) = 0;
};



#endif //TSP_SOLVER_MULTICHAINSOLVERBASECLASS_H
