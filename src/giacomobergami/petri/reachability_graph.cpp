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

size_t generateNewNode(const giacomobergami::petri::elementary_net &net,
                     giacomobergami::petri::reachability_graph &graph,
                     std::unordered_map<std::string, size_t> &places_memo, bool& initialNode,
                     const std::string &M_src) {
    auto src_ptr = places_memo.find(M_src);
    size_t src_id;
    if (src_ptr == places_memo.end()) {
        src_id = graph.addUniqueStateOrGetExisting(net.M);
        places_memo[M_src] = src_id;
        if (initialNode) {
            graph.addToInitialNodesFromId(src_id);
            initialNode = false;
        }
    } else {
        src_id = src_ptr->second;
    }
    return src_id;
}

giacomobergami::petri::reachability_graph
giacomobergami::petri::as_reachability_graph(const giacomobergami::petri::elementary_net &net) {
    giacomobergami::petri::reachability_graph out;
    std::unordered_map<std::string, size_t> places_memo;
    std::unordered_set<std::string> visited;
    std::queue<giacomobergami::petri::elementary_net> Q;
    Q.emplace(net);
    bool isInitialNode = true;
    while (!Q.empty()) {
        giacomobergami::petri::elementary_net& ref = Q.front();
        std::string M_src = ref.toReachability();
        if (visited.contains(M_src)) {
            Q.pop();
        } else {
            visited.insert(M_src);
            auto src_id = generateNewNode(net, out, places_memo, isInitialNode, M_src);
            for (const auto& fired : ref.enabledTransitions()) {
                auto val = ref.fireEnabledTransition(fired);
                if (val) {
                    auto M_dst = val.value().toReachability();
                    auto dst_id = generateNewNode(val.value(), out, places_memo, isInitialNode, M_dst);
                    out.addNewEdgeFromId(src_id, dst_id, std::make_pair(fired, net.firing_weight.at(fired)));
                    Q.emplace(val.value());
                }
            }
            Q.pop();
        }
    }
    return out;
}


giacomobergami::petri::reachability_graph
giacomobergami::petri::as_probabilistic_reachability_graph(const giacomobergami::petri::elementary_net& net) {
    auto g = giacomobergami::petri::as_reachability_graph(net);
    for (size_t i = 0, N = g.maximumNodeId(); i<N; i++) {
        auto out = g.g.getOutgoingEdgesId(i);
        double total = 0.0;
        for (size_t j = 0, M = out.size(); j<M; j++)
            total += g.getEdgeLabel(out.at(j)).second;
        for (size_t j = 0, M = out.size(); j<M; j++)
            g.setEdgeLabel(out.at(j)).second = g.setEdgeLabel(out.at(j)).second / total;
    }
    return g;
}



