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
    if (str[0] == ':'){
        str.erase(0, 1);
        ltrim(str);
    }
}


//On error buildFromFile method will return nullptr
//and set the error_no
TSPLIBInstance *TSPLIBInstanceBuilder::buildFromFile(char *filename) {
    if (access(filename, R_OK) == -1) {
        std::cerr << "cannot access " << filename << std::endl;
        return nullptr;
    }

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "cannot open " << filename << std::endl;
        return nullptr;
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
        } else if(keyword == "EDGE_WEIGHT_TYPE"){
            readStringInside(str_stream, instance->edge_weight_type);
        } else if(keyword == "EDGE_WEIGHT_FORMAT"){
            readStringInside(str_stream, instance->edge_weight_format);
        } else if(keyword == "EDGE_DATA_FORMAT"){
            readStringInside(str_stream, instance->edge_data_format);
        } else if(keyword == "NODE_TYPE"){
            readStringInside(str_stream, instance->node_type);
        } else if(keyword == "NODE_COORD_TYPE"){
            readStringInside(str_stream, instance->node_coord_type);
        } else if(keyword == "COORD1_OFFSET"){
            str_stream >> instance->coord1_offset;
        } else if(keyword == "COORD2_OFFSET"){
            str_stream >> instance->coord2_offset;
        } else if(keyword == "COORD3_OFFSET"){
            str_stream >> instance->coord3_offset;
        } else if(keyword == "COORD1_SCALE"){
            str_stream >> instance->coord1_scale;
        } else if(keyword == "COORD2_SCALE"){
            str_stream >> instance->coord2_scale;
        } else if(keyword == "COORD3_SCALE"){
            str_stream >> instance->coord3_scale;
        } else if(keyword == "DISPLAY_DATA_TYPE"){
            readStringInside(str_stream, instance->display_data_type);
        }

    }


    file.close();

    return instance;
}





