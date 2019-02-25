#include <iostream>
#include <cstring>
#include <unistd.h>
#include "TSPLIBInstance/TSPLIBInstanceBuilder.h"
#include "SolverDispatcher.h"
#include "Visualize/MatlabVisualizer.h"

void usage();

void methods();

int main(int argc, char **argv) {

    if (argc == 1) {
        std::cout << "'tsp_solver help' for help" << std::endl;
        return 0;
    } else if (argc > 1 && strcmp(argv[1], "help") == 0) {
        usage();
        return 0;
    } else if (argc > 1 && strcmp(argv[1], "methods") == 0) {
        methods();
    } else if (argc < 3) { //for now
        std::cerr << "Incorrect use" << std::endl;
        std::cerr << "'tsp_solver help' for help" << std::endl;
        return 0;
    }

    char *TSPLIB_file = argv[2];
    char *method = argv[1];

    SolverDispatcherResult *result = SolverDispatcher::dispatch(TSPLIB_file, method);
    MatlabVisualizer::visualize(result->instance, result->tour);

    return 0;
}


void usage() {
    std::cout << "tsp_solver is a program that is designed to solve TSPLIB instances" << std::endl << std::endl;

    std::cout << "In order to run the program, a TSPLIB directory and one or more method name must be specified" << std::endl;
    std::cout << "First method must be construction heuristic" << std::endl;
    std::cout << "Other methods must be improvements heuristic" << std::endl;

    std::cout << "Single method example" << std::endl;
    std::cout << "i.e, 'tsp_solver greedy a280.tsp '" << std::endl << std::endl;

    std::cout << "Multiple methods example" << std::endl;
    std::cout << "i.e, 'tsp_solver greedy -> 2opt a280.tsp '" << std::endl << std::endl;


    std::cout << "To see the available methods, 'tsp_solver methods'" << std::endl;
}

void methods(){
    std::cout << "Available methods are:" << std::endl;
    std::cout << "  Available construction heuristics:" << std::endl;
    std::cout << "      greedy"<< std::endl << std::endl;

    std::cout << "  Available improvement heuristics:" << std::endl;
    std::cout << "      2opt"<< std::endl;
}