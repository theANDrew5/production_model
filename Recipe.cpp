//
// Created by User on 10-Feb-20.
//

#include "Recipe.h"
Recipe::Recipe(unsigned int ID, unsigned int time):_ID(ID),_time(time) {}
Recipe::Recipe(const Recipe & p): _ID(p._ID), _time(p._time) {}

unsigned int Recipe::get_ID()
{
    return this->_ID;
}

unsigned int Recipe::get_time()
{
    return this->_time;
}

std::istream & operator>> (std::istream & is, Recipe & p)//перегрузка оператора сдвига для потока ввода
{
    is>>p._ID>>p._time;
    return is;
}

std::ostream &operator<<(std::ostream & os, Recipe & p)//перегрузка оператора сдвига для вывода
{
    return os<<p._ID<<' '<<p._time;
}

bool operator==(Recipe &left, Recipe &right)
{
    if(left._ID==right._ID && left._time==right._time) return true;
    else return false;
}

bool operator==(const Recipe &left, const Recipe &right)
{
    if(left._ID==right._ID && left._time==right._time) return true;
    else return false;
}

bool operator!=(Recipe &left, Recipe &right) {
    if(left._ID!=right._ID && left._time!=right._time) return true;
    else return false;
}
