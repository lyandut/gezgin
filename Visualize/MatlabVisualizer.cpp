//
// Created by burak on 25.02.2019.
//

#include <sstream>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "MatlabVisualizer.h"

//visualize the instance
void MatlabVisualizer::visualize(TSPLIBInstance *instance) {

    //check if we can visualize the instance
    //in order to visualize the instance
    double **coords;
    if (instance->display_coordinates != nullptr) {
        coords = instance->display_coordinates;
    } else if (instance->coordinates != nullptr) {
        coords = instance->coordinates;
    } else {
        //cannot visualize
        std::cerr << "Cannot visualize" << std::endl;
        return;
    }

    //create a matrix n by n
    int n = instance->dimension;
    std::ofstream file_stream("tmp.m");
    file_stream << "x = [ ";
    for (int i = 0; i < n; ++i) {
        file_stream << coords[i][0] << " ";
    }
    file_stream << "]; " << std::endl;
    file_stream << "y = [ ";
    for (int i = 0; i < n; i++) {
        file_stream << coords[i][1] << " ";
    }
    file_stream << "]; " << std::endl;
    file_stream << "G = graph(zeros(" << n << "));" << std::endl;
    file_stream << "plot(G, 'xData', x, 'yData', y);" << std::endl;
    file_stream << "print('tmp','-dpng');" << std::endl;
    file_stream.close();
    system("./export_png_matlab.sh");
}

//visualize the instance and the tour on it
void MatlabVisualizer::visualize(TSPLIBInstance *instance, std::vector<unsigned int> *tour) {
    int n = instance->dimension;
    std::ofstream file_stream("tmp.m");
    file_stream << "x = [ ";
    for (int i = 0; i < n; ++i) {
        file_stream << instance->coordinates[i][0] << " ";
    }
    file_stream << "]; " << std::endl;
    file_stream << "y = [ ";
    for (int i = 0; i < n; i++) {
        file_stream << instance->coordinates[i][1] << " ";
    }
    file_stream << "]; " << std::endl;
    file_stream << "G = graph(zeros(" << n << "));" << std::endl;
    file_stream << "G = addedge(G, [ ";
    for (int j : *tour) {
        file_stream << (j + 1) << " ";
    }
    file_stream << "], [ ";
    int i = 0;
    for (int j : *tour) {
        if (i == 0) {
            i = 1;
            continue;
        }
        file_stream << (j + 1) << " ";
    }
    file_stream << (tour->at(0) + 1) << "], ones(" << n << ", 1));" << std::endl;
    file_stream << "plot(G, 'xData', x, 'yData', y);" << std::endl;
    file_stream << "print('tmp','-dpng');" << std::endl;
    file_stream.close();
    system("./export_png_matlab.sh");
}