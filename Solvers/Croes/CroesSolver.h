//
// Created by burak on 27.02.2019.
//

#ifndef TSP_SOLVER_CROESSOLVER_H
#define TSP_SOLVER_CROESSOLVER_H


/*
 * This is the initial solution algorithm described in the paper
 * A Method for Solving Traveling-Salesman Problems by G. A. Croes
 * This only involves initial solution, Croes suggests improving those solutions
 * with inversions, therefore it should be backed by 2opt solver to behave
 * as in the article. Quick sort is utilized to make selection of low cost edges
 * faster.
 * */



#include "../ConstructionHeuristic.h"

class CroesSolver : public ConstructionHeuristic{
public:
    Solutions *construct(int **distance_matrix, unsigned int n) override;

};


#endif //TSP_SOLVER_CROESSOLVER_H
