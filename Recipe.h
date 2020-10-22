//
// Created by User on 10-Feb-20.
//

#ifndef MODEL_RECIPE_H
#define MODEL_RECIPE_H

#include "pch.h"// pch.h: This is a precompiled header file.


class Recipe {
public:
    Recipe(unsigned int ID=0, unsigned int time=0);//конструктор
    Recipe(const Recipe &p);//конструктор копирования

    unsigned int get_ID() ;//геттер ID рецепта
    unsigned int get_time() ;//геттер времени рецепта

    friend std::istream & operator>> (std::istream & is, Recipe & p);//перегрузка оператора сдвига для потока ввода
    friend std::ostream &operator<<(std::ostream & os, Recipe & p);//перегрузка оператора сдвига для вывода
    friend bool operator==(Recipe &left, Recipe &right);//перегрузка оператора сравнения
    friend bool operator!=(Recipe &left, Recipe &right);//перегрузка оператора сравнения
    friend bool operator==(const Recipe &left, const Recipe &right);//перегрузка оператора сравнения
private:
    unsigned int _ID; //имя рецепта
    unsigned int _time; //константа времени рецепта
};





#endif //MODEL_RECIPE_H
