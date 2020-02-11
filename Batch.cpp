//
// Created by User on 10-Feb-20.
//

#include "Batch.h"

Batch::Batch(std::string name, unsigned int count):_name(name),_count(count) {}
Batch::Batch(const Batch &p): _name(p._name), _count(p._count) {}

