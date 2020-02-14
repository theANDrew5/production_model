//
// Created by User on 10-Feb-20.
//

#include "Batch.h"
Batch::Batch() {}
Batch::Batch(std::string name, unsigned int count, std::vector<Recipe> recipes):_name(name),_count(count),_recipes(recipes) {}
Batch::Batch(const Batch &p): _name(p._name), _count(p._count),_recipes(p._recipes) {}

Recipe * Batch::get_first() {
     Recipe * t= &(this->_recipes.front());
    return t ;
}

const unsigned int Batch::get_count() {
    return this->_count;
}
