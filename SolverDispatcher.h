//
// Created by burak on 21.02.2019.
//

#ifndef TSP_SOLVER_SOLVERDISPATCHER_H
#define TSP_SOLVER_SOLVERDISPATCHER_H

#include <vector>
#include "Solvers/LK/LKSolver.h"

struct SolverDispatcherResult {
    int status; //0 is ok, otherwise exception
    int objective;
    std::vector<int> *tour;
};


class SolverDispatcher {
public:
    static SolverDispatcherResult *dispatch(char *filename, char *solver_name) {
        auto *tuple = TSPLIBInstanceBuilder::buildFromFile(filename);

        if(tuple->status != 0){
            auto *result = new SolverDispatcherResult;
            result->status = tuple->status;
            result->objective = -1;
            result->tour = nullptr;
            return result;
        }


        auto *TSPLIB_instance = tuple->instance;

        if (strcmp("linker", solver_name) == 0) {
            auto *lkSolver = new LKSolver();
            //lkSolver->improve(TSPLIB_instance);
            auto *result = new SolverDispatcherResult;
            result->status = 0; //success
        }

        return nullptr;
    }
};


#endif //TSP_SOLVER_SOLVERDISPATCHER_H
