//
// Created by burak on 21.02.2019.
//

#ifndef TSP_SOLVER_SOLVERDISPATCHER_H
#define TSP_SOLVER_SOLVERDISPATCHER_H

#include <vector>
#include <map>
#include "Solvers/Greedy/GreedySolver.h"
#include "Solvers/NGreedy/NGreedySolver.h"
#include "Solvers/Croes/CroesSolver.h"
#include "Visualize/MatlabVisualizer.h"
#include "Solvers/TwoOpt/TwoOptSolver.h"


typedef std::pair<std::vector<unsigned int> *, int> Solution;
typedef std::vector<Solution *> Solutions;

class SolverDispatcher {
public:
    static void dispatch(const char *filename, std::vector<std::string> *methods) {
        auto instance = TSPLIBInstanceBuilder::buildFromFile(filename);

        auto construction_method = methods->at(0);
        Solutions *solutions = nullptr;

        if (construction_method == "greedy") {
            auto greedy_solver = new GreedySolver();
            solutions = greedy_solver->construct(instance->distance_matrix, instance->dimension);
            delete greedy_solver;
        } else if (construction_method == "n-greedy") {
            auto n_greedy_solver = new NGreedySolver;
            solutions = n_greedy_solver->construct(instance->distance_matrix, instance->dimension);
            delete n_greedy_solver;
        } else if (construction_method == "croes") {
            auto croes_solver = new CroesSolver;
            solutions = croes_solver->construct(instance->distance_matrix, instance->dimension);
            delete croes_solver;
        }

        unsigned long method_size = methods->size();


        for (unsigned int i = 1; i < method_size; ++i) {
            if (methods->at(i) == "2opt") {
                auto two_opt_solver = new TwoOptSolver;
                solutions = two_opt_solver->improve(instance->distance_matrix, instance->dimension, solutions);
                delete two_opt_solver;
            }
        }


        auto t = solutions->at(0);
        MatlabVisualizer::visualize(instance, t->first);

        delete instance;
    }
};


#endif //TSP_SOLVER_SOLVERDISPATCHER_H
