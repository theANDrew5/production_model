//
// Created by User on 10-Feb-20.
//

#ifndef MODEL_MACHINE_H
#define MODEL_MACHINE_H

#include <string>
#include <vector>
#include "Batch.h"
#include "Recipe.h"

//Базовый класс
class Machine {
public:
    Machine(std::string name,std::vector <Recipe> recipes, bool state);
    Machine(std::string name,std::vector <Batch> batches,std::vector <Recipe> recipes, bool state);
    Machine(const Machine & p);

  //  virtual ~Machine();

   // virtual void execution() =0;
private:
    std::string _name;//имя
    std::vector <Batch> _bathces;//входная очередь
    std::vector <Recipe> _recipes;//рецепты на машине
    bool _state;//состояние
    unsigned int _current_env_time;//длительность текущего события
};
/*
//наследник для потоковой обработки
class M_flow:Machine
{
public:
    M_flow(std::string name,std::vector <Recipe> recipes, bool state);
    M_flow(std::string name,std::vector <Batch> batches,std::vector <Recipe> recipes, bool state);
    //M_flow(const M_flow & p);

    void execution();
};

//наследник обработки группой партий
class M_group:Machine
{
public:
    M_group(std::string name,std::vector <Recipe> recipes, bool state);
    M_group(std::string name,std::vector <Batch> batches,std::vector <Recipe> recipes, bool state);
    //M_group(const M_group & p);

    void execution();
};

//наследник обработки пачкой пластин
class M_stack:Machine
{
public:
    M_stack(std::string name,std::vector <Recipe> recipes, bool state);
    M_stack(std::string name,std::vector <Batch> batches,std::vector <Recipe> recipes, bool state);
    //M_stack(const M_stack & p);

    void execution();
};
*/


#endif //MODEL_MACHINE_H
