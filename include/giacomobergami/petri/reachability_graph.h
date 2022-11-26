/*
 * reachability_graph.h
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

#ifndef PETRI_REACHABILITY_GRAPH_H
#define PETRI_REACHABILITY_GRAPH_H

#include <string>
#include <unordered_map>
#include <giacomobergami/petri/elementary_net.h>
#include <queue>

namespace giacomobergami::petri {
        std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_set<std::string>>>  reachability_graph(const giacomobergami::petri::elementary_net& net);

        std::string reachability_to_graphviz(const std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_set<std::string>>>& mark_edges);
}
#endif //PETRI_REACHABILITY_GRAPH_H
