#include <iostream>
#include <cstring>
#include <unistd.h>
#include "TSPLIBInstance/TSPLIBInstanceBuilder.h"
#include "SolverDispatcher.h"

void usage();

int main(int argc, char **argv) {

    if (argc == 1) {
        std::cout << "'tsp_solver help' for help" << std::endl;
        return 0;
    } else if (argc > 1 && strcmp(argv[1], "help") == 0) {
        usage();
        return 0;
    } else if (argc < 3) { //for now
        std::cerr << "Incorrect use" << std::endl;
        std::cerr << "'tsp_solver help' for help" << std::endl;
        return 0;
    }

    char *TSPLIB_file = argv[2];
    char *method = argv[1];

    SolverDispatcher::dispatch(TSPLIB_file, method);
    return 0;
}


void usage() {
    std::cout << "tsp_solver is a program that is designed to solve TSPLIB instances" << std::endl << std::endl;

    std::cout << "In order to run the program, a TSPLIB directory and a method name must be specified" << std::endl;
    std::cout << "Additional options can be specified also" << std::endl;
    std::cout << "     'tsp_solver method_name input.tsp [OPTIONS]'" << std::endl;
    std::cout << "i.e, 'tsp_solver 2opt a280.tsp '" << std::endl << std::endl;

    std::cout << "At a given time, only one input and one method must be specified" << std::endl;
    std::cout << "This constraint will be relaxed in future releases" << std::endl << std::endl;

    std::cout << "To see the available methods, 'tsp_solver methods'" << std::endl;
}