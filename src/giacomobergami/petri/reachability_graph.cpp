/*
 * reachability_graph.cpp
 * This file is part of petri
 *
 * Copyright (C) 2022 - Giacomo Bergami
 *
 * petri is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * petri is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with petri. If not, see <http://www.gnu.org/licenses/>.
 */

 
//
// Created by giacomo on 26/11/22.
//

#include "giacomobergami/petri/reachability_graph.h"

std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_set<std::string>>>
giacomobergami::petri::reachability_graph(const giacomobergami::petri::elementary_net &net) {
    std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_set<std::string>>> mark_edges;
    std::unordered_map<std::string, giacomobergami::petri::elementary_net> places_memo;
    std::queue<giacomobergami::petri::elementary_net> Q;
    Q.emplace(net);
    while (!Q.empty()) {
        giacomobergami::petri::elementary_net& ref = Q.front();
        std::string current = ref.toReachability();
        if (places_memo.contains(current)) {
            Q.pop();
        } else {
            places_memo[current] = net;
            for (const auto& fired : ref.enabledTransitions()) {
                auto val = ref.fireEnabledTransition(fired);
                if (val) {
                    mark_edges[current][fired].insert(val.value().toReachability());
                    Q.emplace(val.value());
                }
            }
            Q.pop();
        }
    }
    return mark_edges;
}

std::string giacomobergami::petri::reachability_to_graphviz(
        const std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_set<std::string>>> &mark_edges) {
    std::unordered_set<std::string> marks;
    std::unordered_map<std::string, size_t> id;
    for (const auto& it : mark_edges) {
        if (marks.insert(it.first).second) {
            id[it.first] = marks.size()-1;
        }
        for (const auto& e : it.second) {
            for (const auto& target : e.second) {
                if (marks.insert(target).second) {
                    id[target] = marks.size()-1;
                }
            }
        }
    }
    std::stringstream os;
    os << "digraph G {\n"
          "  center=true; margin=1; \n"
          "\n"
          "  fontsize=12;\n"
          "  normalize=true;\n"
          " \n"
          "  edge [len=1.3, minlen=1];\n"
          "  node [shape=none, fixedsize=true];\n"
          "\n"
          "  i [label=\"[i]\"];\n";
    for (const auto& it : id) {
        os << "p" << it.second << " [label=<&#91;" << it.first << "&#93;>];\n";
    }
    for (const auto& it : mark_edges) {
        for (const auto& e : it.second) {
            for (const auto& target : e.second) {
                os << "p" << id[it.first] << "->p" << id[target] << "[label="<<e.first<<"];\n";
            }
        }
    }
    os << "\n"
          "}";
    return os.str();
}
