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

std::istream & operator>> (std::istream & is, Recipe & p)//перегрузка оператора сдвига для потока ввода
{
    is>>p._name>>p._time;
    return is;
}
std::ostream &operator<<(std::ostream & os, Recipe & p)//перегрузка оператора сдвига для вывода
{
    return os<<p._name<<' '<<p._time;
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
    if(left._name==right._name && left._time==right._time) return true;
    else return false;
}
bool operator==(const Recipe &left, const Recipe &right)
{
    if(left._name==right._name && left._time==right._time) return true;
    else return false;
}
