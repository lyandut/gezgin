//
// Created by burak on 21.02.2019.
//

#ifndef TSP_SOLVER_SOLVERBASECLASS_H
#define TSP_SOLVER_SOLVERBASECLASS_H


#include <vector>
#include "../TSPLIBInstance/TSPLIBInstance.h"

struct SolverResult {
    int status;
    double objective;
    std::vector<int> *tour;
};

class SolverBaseClass {

private:
    std::string solver_name;
};

class ConstructiveSolverBaseClass : public SolverBaseClass {
public:
    virtual SolverResult *solve(TSPLIBInstance *instance) = 0;

};

class ImprovingSolverBaseClass : public SolverBaseClass {
public:
    virtual SolverResult *improve(TSPLIBInstance *instance, std::vector<int> *starting_route) = 0;
};


#endif //TSP_SOLVER_SOLVERBASECLASS_H
