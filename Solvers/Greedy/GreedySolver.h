//
// Created by burak on 21.02.2019.
//

#ifndef TSP_SOLVER_GREEDYSOLVER_H
#define TSP_SOLVER_GREEDYSOLVER_H


#include "../ConstructionHeuristic.h"

class GreedySolver : public ConstructionHeuristic {
public:
    Solutions *construct(int **distance_matrix, unsigned int n) override;

};


#endif //TSP_SOLVER_GREEDYSOLVER_H
