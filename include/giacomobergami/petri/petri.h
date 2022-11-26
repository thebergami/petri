/*
 * petri.h
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

#ifndef PETRI_PETRI_H
#define PETRI_PETRI_H

#include <unordered_set>
#include <set>
#include <string>
#include <ostream>

namespace giacomobergami::petri {

        struct petri {
            std::unordered_set<std::string> P;
            std::unordered_set<std::string> T;
            std::set<std::pair<std::string, std::string>> F;

            petri() = default;
            petri(const petri&) = default;
            petri(petri&&) = default;
            petri& operator=(const petri&) = default;
            petri& operator=(petri&&) = default;

            friend std::ostream &operator<<(std::ostream &os, const petri &petri);
        };

        bool is_valid_configuration(const std::unordered_set<std::string>& C, struct petri& net);
    } // petri

#endif //PETRI_PETRI_H
