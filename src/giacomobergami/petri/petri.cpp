/*
 * petri.cpp
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

#include "giacomobergami/petri/petri.h"

namespace giacomobergami {
    namespace petri {
        std::ostream &operator<<(std::ostream &os, const petri &petri) {
            os << "P{";
            for (auto it = petri.P.begin(), en = petri.P.end(); it != en; ) {
                os << *it;
                it++;
                if (it != en) os << ", ";
            }
            os << "}.\n T{";
            for (auto it = petri.T.begin(), en = petri.T.end(); it != en; ) {
                os << *it;
                it++;
                if (it != en) os << ", ";
            }
            os << "}.\n F{";
            for (auto it = petri.F.begin(), en = petri.F.end(); it != en; ) {
                os << "(" << it->first << "," << it->second << ")";
                it++;
                if (it != en) os << ", ";
            }
            return os <<"}";
        }

        bool is_valid_configuration(const std::unordered_set<std::string> &C, petri &net) {
            for (const auto& x : C) if (!net.P.contains(x)) return false;
            return true;
        }

    } // giacomobergami
} // petri
