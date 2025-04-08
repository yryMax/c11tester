#include "simple_graph.h"
#include "common.h"
#include <cstdio>
#include <vector>

Graph::Graph() {
}

void Graph::add_edge(unsigned int src, unsigned int dest) {
    if (src != dest) {
        adj[src].insert(dest);
    }
}

bool Graph::has_cycle_util(unsigned int v, std::set<unsigned int>& visited, std::set<unsigned int>& rec_stack, std::vector<unsigned int>& path) {
    visited.insert(v);
    rec_stack.insert(v);
    path.push_back(v);

    auto it = adj.find(v);
    if (it != adj.end()) {
        for (unsigned int u : it->second) {
            if (visited.find(u) == visited.end()) {

                if (has_cycle_util(u, visited, rec_stack, path)) {
                    return true;
                }
            } else if (rec_stack.find(u) != rec_stack.end()) {

                std::vector<unsigned int> cycle;
                bool in_cycle = false;
                for (unsigned int node : path) {
                    if (node == u) {
                        in_cycle = true;
                    }
                    if (in_cycle) {
                        cycle.push_back(node);
                    }
                }
                cycle.push_back(u);


                model_print("Cycle detected: ");
                for (size_t i = 0; i < cycle.size(); ++i) {
                    model_print("%u", cycle[i]);
                    if (i < cycle.size() - 1) {
                        model_print(" -> ");
                    }
                }
                model_print("\n");

                 return true;
            }
        }
    }

    rec_stack.erase(v);
    path.pop_back();
    return false;
}

bool Graph::has_cycle() {
    std::set<unsigned int> visited;
    std::set<unsigned int> rec_stack;
    std::vector<unsigned int> path;

    for (const auto& pair : adj) {
        unsigned int i = pair.first;
        if (visited.find(i) == visited.end()) {
            if (has_cycle_util(i, visited, rec_stack, path)) {
                return true;
            }
        }
    }
    return false;
}

bool Graph::is_reachable(unsigned int a, unsigned int b) {
    std::set<unsigned int> visited;
    return dfs_reachable(a, b, visited);
}

bool Graph::dfs_reachable(unsigned int current, unsigned int target, std::set<unsigned int>& visited) {

    if (current == target) {
        return true;
    }


    visited.insert(current);


    auto it = adj.find(current);
    if (it != adj.end()) {

        for (unsigned int neighbor : it->second) {

            if (visited.find(neighbor) == visited.end()) {
                if (dfs_reachable(neighbor, target, visited)) {
                    return true;
                }
            }
        }
    }

    return false;
}