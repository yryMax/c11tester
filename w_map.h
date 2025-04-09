//
// Created by jiang on 09/04/2025.
//

#ifndef C11TESTER_W_MAP_H
#define C11TESTER_W_MAP_H
#include <map>
#include <set>
#include <string>
class ModelAction;

class w_map {
public:
    w_map();
    ~w_map();

    void add(ModelAction* act);
    std::set<ModelAction*> get_set(ModelAction* act) const;

private:
    std::map<std::string, std::map<int, ModelAction*>> latest_writes;
};
#endif //C11TESTER_W_MAP_H
