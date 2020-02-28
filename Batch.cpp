//
// Created by User on 10-Feb-20.
//

#include "Batch.h"
Batch::Batch() {}
Batch::Batch(std::string name,
        unsigned int count, std::deque<Recipe> recipes):_name(name),_count(count),_recipes(recipes) {}
Batch::Batch(const Batch &p): _name(p._name), _count(p._count),_recipes(p._recipes) {}

Recipe & Batch::get_first() {
     Recipe &t= this->_recipes.front();
    return t ;
}

const unsigned int Batch::get_count() {
    return this->_count;
}

std::istream & operator>> (std::istream & is, Batch & p)//перегрузка оператора сдвига для потока ввода
{
    is>>p._name;
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
    os<<p._name<<' '<<p._count;
    for (Recipe n:p._recipes) os<<' '<<n;
    return os;
}
