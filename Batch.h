//
// Created by User on 10-Feb-20.
//

#ifndef MODEL_BATCH_H
#define MODEL_BATCH_H

#include <string>
#include <vector>
#include <iostream>
#include "Recipe.h"

//класс партии
class Batch {
public:
    Batch();//конструктор пустого экземпляра
    Batch(std::string name, unsigned int count, std::vector <Recipe> recipes);//конструктор с параметрами
    Batch(const Batch &p);//конструктор копирования

    Recipe * get_first();//возвращает первый рецепт в маршрутном листе
    const unsigned int get_count();

    friend std::istream & operator>> (std::istream & is, Batch & p)//перегрузка оператора сдвига для потока ввода
    {
        is>>p._name>>p._count;
        //for (Recipe n:p._recipes) is>>n;
        char ch=0;
        while (is.get(ch) && ch!='\n')
        {
            Recipe buf;
            is>>buf;
            p._recipes.push_back(buf);
        }
        return is;
    }
    friend std::ostream &operator<<(std::ostream & os, Batch & p)//перегрузка оператора сдвига для вывода
    {
        os<<p._name<<' '<<p._count;
        for (Recipe n:p._recipes) os<<' '<<n;
        return os;
    }

private:
    std::string _name; //имя партии
    unsigned int _count; //число пластин
    std::vector <Recipe> _recipes;//вектор рецептов партии он же маршрутный лист

};


#endif //MODEL_BATCH_H
