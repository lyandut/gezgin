//
// Created by burak on 10.02.2019.
//

#ifndef TSP_SOLVER_TSPLIBINSTANCE_H
#define TSP_SOLVER_TSPLIBINSTANCE_H


#include <stdio.h>
#include <string>

class TSPLIBInstance {

public:
    std::string name;
    std::string comment;
    std::string instance_type;
    std::string graph_type;
    std::string edge_type;
    std::string edge_weight_type;
    std::string edge_weight_format;
    std::string edge_data_format;
    std::string node_type;
    std::string node_coord_type;
    std::string display_data_type;

    int dimension;
    int capacity;

    float coord1_offset;
    float coord1_scale;

    float coord2_offset;
    float coord2_scale;

    float coord3_offset;
    float coord3_scale;

    TSPLIBInstance(){
        name = "not specified";
        comment = "not specified";
        instance_type = "TSP";
        graph_type = "COMPLETE_GRAPH";
        edge_type = "UNDIRECTED";
        edge_weight_type = "not specified";
        edge_weight_format = "not specified";
        edge_data_format = "COMPLETE";
        node_type = "UNWEIGHTED_NODES";
        node_coord_type = "NO_COORDS";
        dimension = 0;
        capacity = 0;

        coord1_offset = 0;
        coord2_offset = 0;
        coord3_offset = 0;

        coord1_scale = 1;
        coord2_scale = 1;
        coord3_scale = 1;

        display_data_type = "NO_DISPLAY";
    }



};


#endif //TSP_SOLVER_TSPLIBINSTANCE_H
