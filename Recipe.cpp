//
// Created by User on 10-Feb-20.
//

#include "Recipe.h"

Recipe::Recipe(std::string name, unsigned int time):_name(name),_time(time) {}
Recipe::Recipe(const Recipe & p): _name(p._name), _time(p._time) {}