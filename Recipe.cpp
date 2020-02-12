//
// Created by User on 10-Feb-20.
//

#include "Recipe.h"

Recipe::Recipe(std::string name, unsigned int time):_name(name),_time(time) {}
Recipe::Recipe(const Recipe & p): _name(p._name), _time(p._time) {}

std::string Recipe::get_name()
{
    return this->_name;
}

unsigned int Recipe::get_time()
{
    return this->_time;
}

bool operator==(Recipe &left, Recipe &right)
{
    if(left.get_name()==right.get_name() && left.get_time()==right.get_time()) return true;
    else return false;
}
