//
// Created by burak on 27.02.2019.
//

#include "CroesSolver.h"
#include <vector>
#include <stack>
#include <iostream>
#include <fstream>

typedef std::pair<int, int> int_pair;
typedef std::pair<int, int_pair> cost_coordinate_pair;

int ccp_partition(cost_coordinate_pair *arr, int low, int high) {
    int pivot = arr[high].first;    // pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j].first <= pivot) {
            i++;    // increment index of smaller element
            cost_coordinate_pair t = arr[i];
            arr[i] = arr[j];
            arr[j] = t;
        }
    }
    cost_coordinate_pair t = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = t;
    return (i + 1);
}

void ccp_quickSort(cost_coordinate_pair *arr, int low, int high) {
    if (low < high) {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = ccp_partition(arr, low, high);

        // Separately sort elements before
        // partition and after ccp_partition
        ccp_quickSort(arr, low, pi - 1);
        ccp_quickSort(arr, pi + 1, high);
    }
}

unsigned long
ip_partition(std::vector<std::pair<unsigned int, unsigned int>> *arr, unsigned long low, unsigned long high) {
    int pivot = arr->at(high).first;// pivot
    unsigned long i = (low - 1);  // Index of smaller element

    for (unsigned long j = low; j <= high - 1; j++) {
        // If current element is smaller than or
        // equal to pivot
        if ((arr->at(j)).first <= pivot) {
            i++;    // increment index of smaller element
            unsigned int f = arr->at(i).first;
            unsigned int s = arr->at(i).second;

            arr->at(i).first = arr->at(j).first;
            arr->at(i).second = arr->at(j).second;

            arr->at(j).first = f;
            arr->at(j).second = s;
        }
    }
    unsigned int f = arr->at(i + 1).first;
    unsigned int s = arr->at(i + 1).second;

    arr->at(i + 1).first = arr->at(high).first;
    arr->at(i + 1).second = arr->at(high).second;

    arr->at(high).first = f;
    arr->at(high).second = s;

    return (i + 1);
}

void ip_quickSort(std::vector<std::pair<unsigned int, unsigned int>> *arr, unsigned long low, unsigned long high) {
    if (low < high) {
        /* pi is partitioning index, arr[p] is now
           at right place */
        unsigned long pi = ip_partition(arr, low, high);

        // Separately sort elements before
        // partition and after ccp_partition
        ip_quickSort(arr, low, pi - 1);
        ip_quickSort(arr, pi + 1, high);
    }
}

unsigned int *find_adjacent_vertices(std::vector<std::pair<unsigned int, unsigned int>> *adj_list, unsigned int node) {
    //we assume adj list is sorted
    unsigned long p = 0;
    unsigned long r = adj_list->size() - 1;
    unsigned long q = (p + r) / 2;
    int element;
    while ((element = adj_list->at(q).first) != node && p < r) {
        if (element > node) {
            r = q - 1;
            q = (p + r) / 2;
        } else {
            p = q + 1;
            q = (p + r) / 2;
        }
    }

    auto *ret = new unsigned int[2];

    if (adj_list->at(q).first == node) {
        ret[0] = adj_list->at(q).second;
        if (q > 0 && adj_list->at(q - 1).first == node) {
            ret[1] = adj_list->at(q - 1).second;
        } else if (q < adj_list->size() - 1 && adj_list->at(q + 1).first == node) {
            ret[1] = adj_list->at(q + 1).second;
        } else {
            ret[1] = node;
        }
    } else {
        ret[0] = node;
        ret[1] = node;
    }

    return ret;
}

Solutions *CroesSolver::construct(int **distance_matrix, unsigned int n) {

    int lower_bound = 0;
    auto adj_list = new std::vector<std::pair<unsigned int, unsigned int>>();

    const int len = n * (n - 1) / 2;


    auto cost_coordinate_arr = new cost_coordinate_pair[len];
    int index = 0;
    for (int j = 0; j < n; ++j) {
        for (int i = j + 1; i < n; ++i) {
            cost_coordinate_arr[index].first = distance_matrix[j][i];
            cost_coordinate_arr[index].second.first = j;
            cost_coordinate_arr[index].second.second = i;
            index++;
        }
    }

    ccp_quickSort(cost_coordinate_arr, 0, len - 1);

    auto order_matrix = new int[n];
    for (int k = 0; k < n; ++k) {
        order_matrix[k] = 0;
    }

    for (int ind = 0; ind < len; ++ind) {
        auto item = cost_coordinate_arr[ind];
        int i = item.second.first;
        int j = item.second.second;

        if (order_matrix[i] < 2 && order_matrix[j] < 2) {
            ++order_matrix[i];
            ++order_matrix[j];
            lower_bound += item.first;
            adj_list->emplace_back(i, j);
            adj_list->emplace_back(j, i);
        }
    }


    delete[] cost_coordinate_arr;
    delete[] order_matrix;


    //sort the adjacency list
    ip_quickSort(adj_list, 0, adj_list->size() - 1);

    int visited = 0;
    auto visited_arr = new int[n];
    for (int l = 0; l < n; ++l) {
        visited_arr[l] = 0;
    }

    auto cycle_vector = new std::vector<std::vector<unsigned int> *>;

    while (visited < n) {
        unsigned int start = 0;
        for (unsigned int i = 0; i < n; ++i) {
            if (visited_arr[i] == 0) {
                start = i;
                break;
            }
        }
        visited++;
        visited_arr[start] = 1;

        auto new_tour = new std::vector<unsigned int>;
        new_tour->push_back(start);
        cycle_vector->push_back(new_tour);

        unsigned int node = start;
        unsigned int coming_from = start;

        unsigned int *adjacent_vertices = find_adjacent_vertices(adj_list, node);
        while ((adjacent_vertices[0] != start || adjacent_vertices[1] != coming_from) &&
               (adjacent_vertices[0] != coming_from || adjacent_vertices[1] != start)) {

            if (adjacent_vertices[0] != node && adjacent_vertices[0] != coming_from) {
                new_tour->push_back(adjacent_vertices[0]);
                visited++;
                coming_from = node;
                node = adjacent_vertices[0];
                visited_arr[node] = 1;
            } else if (adjacent_vertices[1] != node && adjacent_vertices[1] != coming_from) {
                new_tour->push_back(adjacent_vertices[1]);
                visited++;
                coming_from = node;
                node = adjacent_vertices[1];
                visited_arr[node] = 1;
            }
            delete[] adjacent_vertices;
            adjacent_vertices = find_adjacent_vertices(adj_list, node);
        }
        delete[] adjacent_vertices;
    }

    auto tour = new std::vector<unsigned int>();
    int cost = 0;
    int first_i = -1;
    unsigned first = 0;
    unsigned before = 0;
    for (auto item : *cycle_vector) {
        for (unsigned int i : *item) {
            if (first_i == -1) {
                first_i = 0;
                first = i;
            } else {
                cost += distance_matrix[before][i];
            }
            tour->emplace_back(i);
            before = i;
        }
    }
    cost += distance_matrix[before][first];

    auto solutions = new Solutions;

    auto sol = new Solution;
    sol->first = tour;
    sol->second = cost;

    solutions->push_back(sol);

    delete[] visited_arr;
    for (auto &m : *cycle_vector) {
        delete m;
    }
    delete cycle_vector;
    delete adj_list;

    return solutions;
}
