//
// Created by burak on 21.02.2019.
//

#ifndef TSP_SOLVER_SOLVERBASECLASS_H
#define TSP_SOLVER_SOLVERBASECLASS_H


#include <vector>
#include "../TSPLIBInstance/TSPLIBInstance.h"

class SolverBaseClass {
public:
    virtual std::vector<int> solve(TSPLIBInstance *instance) = 0;
};


#endif //TSP_SOLVER_SOLVERBASECLASS_H
