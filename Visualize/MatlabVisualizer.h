//
// Created by burak on 25.02.2019.
//

#ifndef TSP_SOLVER_MATLABVISUALIZER_H
#define TSP_SOLVER_MATLABVISUALIZER_H


#include "../TSPLIBInstance/TSPLIBInstance.h"
#include <vector>

class MatlabVisualizer {
public:
    static void visualize(TSPLIBInstance *instance);

    static void visualize(TSPLIBInstance *instance, std::vector<int> *tour);
};


#endif //TSP_SOLVER_MATLABVISUALIZER_H
