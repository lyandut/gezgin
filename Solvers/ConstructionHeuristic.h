//
// Created by burak on 26.02.2019.
//

#ifndef TSP_SOLVER_CONSTRUCTIONHEURISTICS_H
#define TSP_SOLVER_CONSTRUCTIONHEURISTICS_H

#include <stdio.h>
#include <vector>

typedef std::pair<std::vector<unsigned int>*, int> Solution;
typedef std::vector<Solution *> Solutions;


class ConstructionHeuristic {
public:
    virtual Solutions *construct(int **distance_matrix, unsigned int n) = 0;
};


#endif //TSP_SOLVER_CONSTRUCTIONHEURISTICS_H
