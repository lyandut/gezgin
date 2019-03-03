//
// Created by burak on 26.02.2019.
//

#ifndef TSP_SOLVER_IMPROVEMENTHEURISTIC_H
#define TSP_SOLVER_IMPROVEMENTHEURISTIC_H

#include <stdio.h>
#include <vector>


typedef std::pair<std::vector<unsigned int> *, int> Solution;
typedef std::vector<Solution *> Solutions;

class ImprovementHeuristic {
public:
    virtual Solutions *improve(int **distance_matrix, unsigned int n, Solutions *previous_solutions) = 0;
};


#endif //TSP_SOLVER_IMPROVEMENTHEURISTIC_H
