//
// Created by User on 10-Feb-20.
//

#ifndef MODEL_RECIPE_H
#define MODEL_RECIPE_H

#include <string>
#include <iostream>


class Recipe {
public:
    Recipe();
    Recipe(std::string name, unsigned int time);//конструктор
    Recipe(const Recipe &p);//конструктор копирования

    std::string get_name() ;//геттер имени рецепта
    unsigned int get_time() ;//геттер времени рецепта

    friend std::istream & operator>> (std::istream & is, Recipe & p);//перегрузка оператора сдвига для потока ввода
    friend std::ostream &operator<<(std::ostream & os, Recipe & p);//перегрузка оператора сдвига для вывода
    friend bool operator==(Recipe &left, Recipe &right);//перегрузка оператора сравнения
    friend bool operator==(const Recipe &left, const Recipe &right);//перегрузка оператора сравнения
private:
    std::string _name; //имя рецепта
    unsigned int _time; //константа времени рецепта
};





#endif //MODEL_RECIPE_H
