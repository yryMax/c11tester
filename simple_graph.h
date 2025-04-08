#ifndef SIMPLE_GRAPH_H
#define SIMPLE_GRAPH_H

#include <map>
#include <set>
#include <vector>

class Graph {
public:
    Graph();
    void add_edge(unsigned int src, unsigned int dest);
    bool has_cycle();
    bool is_reachable(unsigned int a, unsigned int b);
    bool dfs_reachable(unsigned int current, unsigned int target, std::set<unsigned int>& visited);


private:
    std::map<unsigned int, std::set<unsigned int>> adj;

    bool has_cycle_util(unsigned int v, std::set<unsigned int> &visited, std::set<unsigned int> &rec_stack,
                        std::vector<unsigned int> &path);
};

#endif // SIMPLE_GRAPH_H