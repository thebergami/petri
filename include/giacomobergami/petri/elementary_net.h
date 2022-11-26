/*
 * elementary_net.h
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

#ifndef PETRI_ELEMENTARY_NET_H
#define PETRI_ELEMENTARY_NET_H

#include <string>
#include <yaucl/hashing/umap_hash.h>
#include <vector>
#include <optional>
#include <giacomobergami/petri/petri.h>
#include <sstream>
#include <yaucl/graphs/NodeLabelBijectionFA.h>

namespace giacomobergami::petri {

    using reachability_graph = NodeLabelBijectionFA<std::map<std::string, size_t>, std::pair<std::string, double>>;

        struct elementary_net {
            struct petri net;
            std::map<std::string, size_t> M;
            std::unordered_map<std::string, double> firing_weight;
            std::unordered_map<std::string, std::unordered_map<std::string, size_t>> input_places, output_places;

            void add_place_with_tokens(const std::string& mark, size_t n = 0);
            void add_transition(const std::string& transition, double firing_weight = 1.0);
            bool add_input_place(const std::string& s, const std::string& t, size_t n = 1);
            bool add_output_place(const std::string& t, const std::string& s, size_t n = 1);

            elementary_net(const std::unordered_map<std::string, size_t>& M,
                           const std::map<std::pair<std::string, std::string>, size_t>& W,
                           const std::unordered_set<std::string>& T
            );

            std::vector<std::string> enabledTransitions() const;

            bool isEnabled(const std::string& T_name) const;

            std::optional<elementary_net> fireEnabledTransition(const std::string& t_name) const;

            std::string toReachability() const;

            friend std::ostream &operator<<(std::ostream &os, const elementary_net &net);

            elementary_net() = default;
            elementary_net(const elementary_net&) = default;
            elementary_net(elementary_net&&) = default;
            elementary_net& operator=(const elementary_net&) = default;
            elementary_net& operator=(elementary_net&&) = default;
        };

    } // petri

#endif //PETRI_ELEMENTARY_NET_H
