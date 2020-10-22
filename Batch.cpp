//
// Created by User on 10-Feb-20.
//

#include "pch.h"// pch.h: This is a precompiled header file.
#include "Batch.h"

Batch::Batch(unsigned int ID,
        unsigned int count, std::deque<Recipe> recipes):_ID(ID),_count(count),_recipes(recipes) {}
Batch::Batch(const Batch &p): _ID(p._ID), _count(p._count),_recipes(p._recipes) {}

Recipe & Batch::get_first() {
     Recipe &t= this->_recipes.front();
    return t ;
}

const unsigned int Batch::get_count() {
    return this->_count;
}

std::istream & operator>> (std::istream & is, Batch & p)//перегрузка оператора сдвига для потока ввода
{
    is>>p._ID;
    is>>p._count;
    while (is.peek()!=-1)
    {
        Recipe buf;
        is>>buf;
        p._recipes.push_back(buf);
    }
    is.get();
    return is;
}

std::ostream &operator<<(std::ostream & os, Batch & p)//перегрузка оператора сдвига для вывода
{
    os<<"ID: "<<p._ID<<"\tCOUNT: "<<p._count<<"\tRECIPES:";
    for (Recipe n:p._recipes) os<<'\t'<<n;
    return os;
}

unsigned int Batch::get_ID() {
    return this->_ID;
}

void Batch::execute()
{
    this->_recipes.pop_front();
}
