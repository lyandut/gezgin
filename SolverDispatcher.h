//
// Created by burak on 21.02.2019.
//

#ifndef TSP_SOLVER_SOLVERDISPATCHER_H
#define TSP_SOLVER_SOLVERDISPATCHER_H

#include <vector>
#include "Solvers/LK/LKSolver.h"
#include "Solvers/Greedy/GreedySolver.h"

struct SolverDispatcherResult {
    int status; //0 is ok, otherwise exception
    int objective;
    std::vector<int> *tour;
    TSPLIBInstance *instance;
};


class SolverDispatcher {
public:
    static SolverDispatcherResult *dispatch(char *filename, char *solver_name) {
        auto *tuple = TSPLIBInstanceBuilder::buildFromFile(filename);

        auto *result = new SolverDispatcherResult;

        if (tuple->status != 0) {
            result->status = tuple->status;
            result->objective = -1;
            result->tour = nullptr;
            result->instance = nullptr;
            return result;
        }


        auto *TSPLIB_instance = tuple->instance;
        result->instance = tuple->instance;

        if (strcmp("greedy", solver_name) == 0) {
            auto *greedySolver = new GreedySolver();
            auto *solver_result = greedySolver->solve(TSPLIB_instance);
            result->status = solver_result->status;
            result->tour = solver_result->tour;
            result->objective = solver_result->objective;
        }

        return result;
    }
};


#endif //TSP_SOLVER_SOLVERDISPATCHER_H
