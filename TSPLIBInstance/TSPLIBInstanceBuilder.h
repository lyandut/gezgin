//
// Created by burak on 16.02.2019.
//

#ifndef TSP_SOLVER_TSPLIBINSTANCEBUILDER_H
#define TSP_SOLVER_TSPLIBINSTANCEBUILDER_H


#include "TSPLIBInstance.h"



class TSPLIBInstanceBuilder {
public:
    static TSPLIBInstance *buildFromFile(const char * file_name);

};


#endif //TSP_SOLVER_TSPLIBINSTANCEBUILDER_H
