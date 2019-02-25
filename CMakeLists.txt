cmake_minimum_required(VERSION 3.13)
project(tsp_solver)

set(CMAKE_CXX_STANDARD 14)

add_executable(tsp_solver main.cpp TSPLIBInstance/TSPLIBInstance.h TSPLIBInstance/TSPLIBInstanceBuilder.cpp TSPLIBInstance/TSPLIBInstanceBuilder.h Solvers/SingleChainSolverBaseClass.h Solvers/LK/LKSolver.cpp Solvers/LK/LKSolver.h SolverDispatcher.h Solvers/Greedy/GreedySolver.cpp Solvers/Greedy/GreedySolver.h Visualize/MatlabVisualizer.cpp Visualize/MatlabVisualizer.h Solvers/MultiChainSolverBaseClass.h)