/*
 * elementary_net.cpp
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

#include "giacomobergami/petri/elementary_net.h"

namespace giacomobergami {
    namespace petri {
        void elementary_net::add_place_with_tokens(const std::string &mark, size_t n) {
            if (n > 0) M.emplace(mark, n);
            net.P.emplace(mark);
        }

        void elementary_net::add_transition(const std::string &transition) {
            net.T.insert(transition);
        }

        bool elementary_net::add_input_place(const std::string &s, const std::string &t, size_t n) {
            if (net.P.contains(s) && net.T.contains(t)) {
                net.F.emplace(s, t);
                input_places[t][s] = n;
                return true;
            } else return false;
        }

        bool elementary_net::add_output_place(const std::string &t, const std::string &s, size_t n) {
            if (net.P.contains(s) && net.T.contains(t)) {
                net.F.emplace(t, s);
                output_places[t][s] = n;
                return true;
            } else return false;
        }

        elementary_net::elementary_net(const std::unordered_map<std::string, size_t> &M,
                                       const std::map<std::pair<std::string, std::string>, size_t> &W,
                                       const std::unordered_set<std::string> &T) {
            for (const auto& it : M) {
                add_place_with_tokens(it.first, it.second);
            }
            for (const auto& t : T)
                add_transition(t);
            for (const auto& it : W) {
                if (it.second > 0) net.F.emplace(it.first);
                if (net.P.contains(it.first.first) && net.T.contains(it.first.second) && (it.second > 0)) {
                    add_input_place(it.first.first, it.first.second, it.second);
                } else if (net.P.contains(it.first.second) && (net.T.contains(it.first.first)) && (it.second > 0)) {
                    add_output_place(it.first.first, it.first.second, it.second);
                } else {
                    throw std::runtime_error("Invalid transition being stated!");
                }
            }
        }

        std::vector<std::string> elementary_net::enabledTransitions() const {
            std::vector<std::string> M;
            for (const auto& T : net.T)
                if (isEnabled(T)) M.emplace_back(T);
            return M;
        }

        bool elementary_net::isEnabled(const std::string &T_name) const {
            auto it = input_places.find(T_name);
            if (it == input_places.end()) return false;
            for (const auto & beg : it->second) {
                auto it2 = M.find(beg.first);
                if (it2 == M.end()) return false;
                if (it2->second < beg.second) return false;
            }
            return true;
        }

        std::optional<elementary_net> elementary_net::fireEnabledTransition(const std::string &t_name) const {
            elementary_net result = *this;
            auto it = result.input_places.find(t_name);
            if (it == result.input_places.end()) return {};
            for (auto & beg : it->second) {
                auto it2 = result.M.find(beg.first);
                if (it2 == M.end()) return {};
                if (it2->second < beg.second) return {};
                it2->second -= beg.second;
                if (it2->second == 0) {
                    result.M.erase(it2);
                }
            }
            it = result.output_places.find(t_name);
            if (it == result.output_places.end()) return {result};
            for (auto& beg : it->second) {
                auto it = result.M.find(beg.first);
                if (it == result.M.end())
                    result.M[beg.first] = beg.second;
                else
                    it->second += beg.second;
            }
            return {result};
        }

        std::string elementary_net::toReachability() const {
            std::stringstream os;
            os << "[";
            for (auto beg = M.begin(), end = M.end(); beg != end; ) {
                os << beg->first << "=" << beg->second;
                beg++;
                if (beg != end) os << ", ";
            }
            os << "]";
            return os.str();
        }

        std::ostream &operator<<(std::ostream &os, const elementary_net &net) {
            return os << net.net << " " << net.toReachability();
        }

    } // giacomobergami
} // petri
