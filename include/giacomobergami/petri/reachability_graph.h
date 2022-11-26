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

#include <yaucl/hashing/umap_hash.h>
#include <string>
#include <unordered_map>
#include <giacomobergami/petri/elementary_net.h>
#include <queue>

namespace giacomobergami::petri {
    reachability_graph as_reachability_graph(const giacomobergami::petri::elementary_net& net);
    reachability_graph as_probabilistic_reachability_graph(const giacomobergami::petri::elementary_net& net);
}
#endif //PETRI_REACHABILITY_GRAPH_H
