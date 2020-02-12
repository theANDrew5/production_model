//
// Created by User on 10-Feb-20.
//

#ifndef MODEL_RECIPE_H
#define MODEL_RECIPE_H

#include <string>


class Recipe {
public:
    Recipe(std::string name, unsigned int time);
    Recipe(const Recipe &p);

    std::string get_name() ;
    unsigned int get_time() ;
private:
    std::string _name; //имя рецепта
    unsigned int _time; //константа времени рецепта
};

bool operator==(Recipe &left, Recipe &right);


#endif //MODEL_RECIPE_H
