//
// Created by User on 10-Feb-20.
//

#include "Recipe.h"
Recipe::Recipe()
{

}
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
/*
std::istream & Recipe::operator>>(std::istream &is)
{
is>>this->_name>>this->_time;
    return is;
}

std::ostream & Recipe::operator<<(std::ostream &os)
{
os<<this->_name<<' '<< this->_time<<'\n';
    return os;
}*/
bool operator==(Recipe &left, Recipe &right)
{
    if(left.get_name()==right.get_name() && left.get_time()==right.get_time()) return true;
    else return false;
}
