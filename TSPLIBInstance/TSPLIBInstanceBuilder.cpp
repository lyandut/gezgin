//
// Created by burak on 16.02.2019.
//

#include <unistd.h>
#include "TSPLIBInstanceBuilder.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include <vector>

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    std::not1(std::ptr_fun<int, int>(std::isspace))));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}


static void readStringInside(std::istringstream &str_stream, std::string &str) {
    std::getline(str_stream, str);
    trim(str);
    if (str[0] == ':') {
        str.erase(0, 1);
        ltrim(str);
    }
}


//On error buildFromFile method will return nullptr
//and set the error_no
BuilderResult *TSPLIBInstanceBuilder::buildFromFile(char *filename) {
    if (access(filename, R_OK) == -1) {
        auto *result = new BuilderResult;
        result->status = 1; //access fail
        result->instance = nullptr;
        return result;
    }

    std::ifstream file(filename);
    if (!file.is_open()) {
        auto *result = new BuilderResult;
        result->status = 1; //access fail
        result->instance = nullptr;
        return result;
    }

    auto instance = new TSPLIBInstance();

    std::string line;
    std::string keyword;

    while (!file.eof()) {
        std::getline(file, line);
        std::istringstream str_stream(line);
        str_stream >> keyword;

        if (keyword.compare(keyword.length() - 1, 1, ":") == 0) {
            keyword.pop_back();
        }

        //later better fix this ugly part :/
        if (keyword == "NAME") {
            readStringInside(str_stream, instance->name);
        } else if (keyword == "COMMENT") {
            readStringInside(str_stream, instance->comment);
        } else if (keyword == "TYPE") {
            readStringInside(str_stream, instance->instance_type);
        } else if (keyword == "DIMENSION") {
            str_stream >> instance->dimension;
        } else if (keyword == "CAPACITY") {
            str_stream >> instance->capacity;
        } else if (keyword == "GRAPH_TYPE") {
            readStringInside(str_stream, instance->graph_type);
        } else if (keyword == "EDGE_TYPE") {
            readStringInside(str_stream, instance->edge_type);
        } else if (keyword == "EDGE_WEIGHT_TYPE") {
            readStringInside(str_stream, instance->edge_weight_type);
        } else if (keyword == "EDGE_WEIGHT_FORMAT") {
            readStringInside(str_stream, instance->edge_weight_format);
        } else if (keyword == "EDGE_DATA_FORMAT") {
            readStringInside(str_stream, instance->edge_data_format);
        } else if (keyword == "NODE_TYPE") {
            readStringInside(str_stream, instance->node_type);
        } else if (keyword == "NODE_COORD_TYPE") {
            readStringInside(str_stream, instance->node_coord_type);
        } else if (keyword == "COORD1_OFFSET") {
            str_stream >> instance->coord1_offset;
        } else if (keyword == "COORD2_OFFSET") {
            str_stream >> instance->coord2_offset;
        } else if (keyword == "COORD3_OFFSET") {
            str_stream >> instance->coord3_offset;
        } else if (keyword == "COORD1_SCALE") {
            str_stream >> instance->coord1_scale;
        } else if (keyword == "COORD2_SCALE") {
            str_stream >> instance->coord2_scale;
        } else if (keyword == "COORD3_SCALE") {
            str_stream >> instance->coord3_scale;
        } else if (keyword == "DISPLAY_DATA_TYPE") {
            readStringInside(str_stream, instance->display_data_type);
        }

        if (keyword == "NODE_COORD_SECTION") {
            int n = instance->dimension;
            int xyz = 0;
            instance->coordinates = new double *[n];

            if (instance->node_coord_type == "TWOD_COORDS") {
                for (int i = 0; i < n; i++) {
                    instance->coordinates[i] = new double[2];
                }
                xyz = 2;
            } else if (instance->node_coord_type == "THREED_COORDS") {
                for (int i = 0; i < n; i++) {
                    instance->coordinates[i] = new double[3];
                }
                xyz = 3;
            } else {
                //NODE_COORD_SECTION started however node_coord_type is NO_COORDS
                auto *result = new BuilderResult;
                result->status = 2; //Inconsistent attributes
                result->instance = nullptr;
                file.close();
                return result;
            }

            for (int i = 0; i < n; i++) {
                int node_index;
                str_stream >> node_index;
                for (int j = 0; j < xyz; ++j) {
                    str_stream >> instance->coordinates[node_index][j];
                }
            }
        } else if (keyword == "DEPOT_SECTION") {
            auto alternate_depots = new std::vector<int>();
            int i;
            str_stream >> i;
            while (i != -1) {
                alternate_depots->push_back(i);
                str_stream >> i;
            }

            instance->alternate_depots = alternate_depots;
        } else if (keyword == "DEMAND_SECTION") {
            int n = instance->dimension;
            instance->demands = new int[n];
            for (int i = 0; i < n; ++i) {
                int node_index;
                str_stream >> node_index;
                str_stream >> instance->demands[node_index];
            }
        } else if (keyword == "FIXED_EDGES_SECTION") {
            auto pairs = new std::vector<std::pair<int, int>>();
            int i, j;
            str_stream >> i;
            while (i != -1) {
                str_stream >> j;
                pairs->emplace_back(i, j);
                str_stream >> i;
            }
            instance->fixed_edges = pairs;
        } else if (keyword == "DISPLAY_DATA_SECTION") {
            int n = instance->dimension;
            instance->display_coordinates = new double *[n];
            for (int i = 0; i < n; i++) {
                instance->display_coordinates[i] = new double[2];
            }

            for (int i = 0; i < n; i++) {
                int node_index;
                str_stream >> node_index;
                str_stream >> instance->display_coordinates[node_index][0];
                str_stream >> instance->display_coordinates[node_index][1];
            }
        } else if (keyword == "NODE_WEIGHT_SECTION") {
            int i, j;
            int n = instance->dimension;
            int *node_weights = new int[n];
            str_stream >> i;
            while (i != -1) {
                str_stream >> j;
                node_weights[i] = j;
                str_stream >> i;
            }
            instance->node_weights = node_weights;
        } else if (keyword == "TOUR_SECTION") {
            auto tours = new std::vector<std::vector<int> *>();
            int i;
            str_stream >> i;
            while (i != -1) {
                auto tour = new std::vector<int>();
                while (i != -1) {
                    tour->push_back(i);
                    str_stream >> i;
                }
                tours->push_back(tour);
            }
        } else if (keyword == "EDGE_DATA_SECTION") {
            if (instance->edge_data_format == "EDGE_LIST") {
                auto edge_list = new std::vector<std::pair<int, int>>();
                int i, j;
                str_stream >> i;
                while (i != -1) {
                    str_stream >> j;
                    edge_list->emplace_back(i, j);
                    str_stream >> i;
                }
                instance->edge_list = edge_list;
            } else if (instance->edge_data_format == "ADJ_LIST") {
                auto adj_list = new std::vector<std::pair<int, std::vector<int> *> *>();
                int i;
                str_stream >> i;
                while (i != -1) {
                    int node_index = i;
                    auto adjacency_list = new std::vector<int>();
                    str_stream >> i;
                    while (i != -1) {
                        adjacency_list->push_back(i);
                        str_stream >> i;
                    }
                    adj_list->push_back(new std::pair<int, std::vector<int> *>(node_index, adjacency_list));
                    str_stream >> i;
                }

                instance->adj_list = adj_list;
            }
        } else if(keyword == "EDGE_WEIGHT_SECTION"){
            
        }


    }


    file.close();


    auto *result = new BuilderResult;
    result->status = 0; //success
    result->instance = instance;
    return result;
}





