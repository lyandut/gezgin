//
// Created by burak on 25.02.2019.
//

#ifndef TSP_SOLVER_NGREEDY_H
#define TSP_SOLVER_NGREEDY_H


#include "../ConstructionHeuristic.h"

class NGreedySolver : public ConstructionHeuristic{
public:
    Solutions *construct(int **distance_matrix, unsigned int n) override;

};


#endif //TSP_SOLVER_NGREEDY_H
