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

std::istream & operator>> (std::istream & is, Batch & p)//перегрузка оператора сдвига для потока ввода
{
    //std::cout<<is.eof()<<' ';
    is>>p._name;
    //std::cout<<is.eof()<<' ';
    is>>p._count;
    //std::cout<<is.eof()<<' ';
    while (is.peek()!='\t')
    {
        Recipe buf;
        is>>buf;
        p._recipes.push_back(buf);
    }
    std::cout<<is.tellg()<<'\t';
    //std::cout<<is.eof()<<' ';
    is.get();
    //std::cout<<is.eof()<<'\n';
    std::cout<<is.tellg()<<'\n';
    return is;
}

std::ostream &operator<<(std::ostream & os, Batch & p)//перегрузка оператора сдвига для вывода
{
    os<<p._name<<' '<<p._count;
    for (Recipe n:p._recipes) os<<' '<<n;
    return os;
}
