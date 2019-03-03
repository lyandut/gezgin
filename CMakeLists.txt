cmake_minimum_required(VERSION 3.13)
project(tsp_solver)

set(CMAKE_CXX_STANDARD 14)

add_executable(tsp_solver main.cpp TSPLIBInstance/TSPLIBInstance.h TSPLIBInstance/TSPLIBInstanceBuilder.cpp TSPLIBInstance/TSPLIBInstanceBuilder.h SolverDispatcher.h Solvers/Greedy/GreedySolver.cpp Solvers/Greedy/GreedySolver.h Visualize/MatlabVisualizer.cpp Visualize/MatlabVisualizer.h Solvers/NGreedy/NGreedySolver.cpp Solvers/NGreedy/NGreedySolver.h Solvers/ConstructionHeuristic.h Solvers/ImprovementHeuristic.h Solvers/TwoOpt/TwoOptSolver.cpp Solvers/TwoOpt/TwoOptSolver.h Solvers/Croes/CroesSolver.cpp Solvers/Croes/CroesSolver.h)