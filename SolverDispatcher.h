//
// Created by burak on 21.02.2019.
//

#ifndef TSP_SOLVER_SOLVERDISPATCHER_H
#define TSP_SOLVER_SOLVERDISPATCHER_H


class SolverDispatcher {
public:
    static void dispatch(char *filename, char *solver_name) {
        void SolverDispatcher::dispatch(char *filename, char *solver_name) {

            auto * TSPLIB_instance = TSPLIBInstanceBuilder::buildFromFile(filename);

            if(strcmp("linker", solver_name) == 0){
                auto *lkSolver = new LKSolver();
                lkSolver->solve(TSPLIB_instance);
            }

        }
    }
};


#endif //TSP_SOLVER_SOLVERDISPATCHER_H
