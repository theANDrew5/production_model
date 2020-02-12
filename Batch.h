//
// Created by User on 10-Feb-20.
//

#ifndef MODEL_BATCH_H
#define MODEL_BATCH_H

#include <string>
#include "Recipe.h"
#include <vector>
//класс партии
class Batch {
public:
    Batch(std::string name, unsigned int count, std::vector <Recipe> recipes);
    Batch(const Batch &p);


    Recipe * get_first();//возвращает первый рецепт в маршрутном листе
    const unsigned int get_count();

private:
    std::string _name; //имя партии
    unsigned int _count; //число пластин
    std::vector <Recipe> _recipes;//вектор рецептов партии он же маршрутный лист

};


#endif //MODEL_BATCH_H
