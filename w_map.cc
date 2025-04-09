//
// Created by jiang on 09/04/2025.
//

#include "w_map.h"
#include "action.h" // 在 .cc 文件中包含 action.h，避免头文件冲突

w_map::w_map() {

}

w_map::~w_map() {

}

void w_map::add(ModelAction* act) {
    char buffer[32];
    std::snprintf(buffer, sizeof(buffer), "%14p", act->get_location());
    //model_print("add new write: %u to %s\n", act->get_seq_number(), buffer);

    if (act && (act->is_write() || act->is_rmw())) {
        const int tid = act->get_tid();
            latest_writes[buffer][tid] = act;

    }
}

std::set<ModelAction*> w_map::get_set(ModelAction* act) const {
    char buffer[32];
    std::snprintf(buffer, sizeof(buffer), "%14p", act->get_location());
    std::set<ModelAction*> result;
    auto pos_it = latest_writes.find(buffer);
    if (pos_it != latest_writes.end()) {
        for (const auto& pair : pos_it->second) {
            result.insert(pair.second);
        }
    }
    return result;
}