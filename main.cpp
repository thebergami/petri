/*
 * main.cpp
 * This file is part of petri
 *
 * Copyright (C) 2022 - Giacomo Bergami
 *
 *  petri is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 *  petri is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with  petri. If not, see <http://www.gnu.org/licenses/>.
 */

 
#include <giacomobergami_petri.h>
#include <iostream>
using namespace giacomobergami::petri;

void ex1(elementary_net& net) {
    net.add_place_with_tokens("x", 1);
    net.add_place_with_tokens("y");
    net.add_place_with_tokens("z", 1);
    net.add_place_with_tokens("r1", 1);
    net.add_place_with_tokens("r2", 1);
    net.add_place_with_tokens("g1");
    net.add_place_with_tokens("g2");
    net.add_place_with_tokens("o1");
    net.add_place_with_tokens("o2");
    net.add_transition("rg1");
    net.add_transition("rg2");
    net.add_transition("go1");
    net.add_transition("go2");
    net.add_transition("or1");
    net.add_transition("or2");
    net.add_input_place("x", "rg2");
    net.add_input_place("r2","rg2");
    net.add_input_place("y", "rg1");
    net.add_input_place("r1","rg1");
    net.add_input_place("z", "rg1");
    net.add_output_place("rg1", "g1");
    net.add_output_place("rg2", "g2");
    net.add_input_place("g1", "go1");
    net.add_input_place("g2", "go2");
    net.add_output_place("go1", "o1");
    net.add_output_place("go2", "o2");
    net.add_input_place("o1", "or1");
    net.add_input_place("o2", "or2");
    net.add_output_place("or1", "x");
    net.add_output_place("or1", "r1");
    net.add_output_place("or2", "y");
    net.add_output_place("or2", "r2");
}

void ex2(elementary_net& net) {
    net.add_place_with_tokens("p1", 3);
    net.add_place_with_tokens("p2");
    net.add_transition("t1");
    net.add_transition("t2");
    net.add_transition("t3");
    net.add_input_place("p1", "t1");
    net.add_input_place("p2", "t2");
    net.add_input_place("p2", "t3");
    net.add_output_place("t1", "p2");
    net.add_output_place("t2", "p1");
}

int main() {
    elementary_net net;
    ex1(net);

    auto l = reachability_graph(net);
    std::cout << reachability_to_graphviz(l) << std::endl;
    return 0;
}
