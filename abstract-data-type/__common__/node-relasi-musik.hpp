#ifndef NODE_RELASI_MUSIK_HPP
#define NODE_RELASI_MUSIK_HPP

#include "../../entitas/musik/musik.hpp"

struct NodeRelasiMusik {
    Musik* musik;
    NodeRelasiMusik* next;
};

#endif