//
// Created by User on 10-Feb-20.
//

#include "Machine.h"
//конструкторы базового класса
Machine::Machine(std::string name, std::vector<Recipe> recipes, bool state):
_name(name), _recipes(recipes), _state(state), _current_env_time(0) {}

Machine::Machine(std::string name, std::vector<Batch> batches, std::vector<Recipe> recipes, bool state):
_name(name), _bathces(batches),_recipes(recipes), _state(state), _current_env_time(0) {}

Machine::Machine(const Machine &p):
_name(p._name), _bathces(p._bathces),_recipes(p._recipes), _state(p._state), _current_env_time(p._current_env_time) {}
/*
//конструкторы класса потоковой обработки
M_flow::M_flow(std::string name, std::vector<Recipe> recipes, bool state):
Machine(name,recipes,state) {}

M_flow::M_flow(std::string name,std::vector <Batch> batches,std::vector <Recipe> recipes, bool state):
Machine(name,batches,recipes,state){}
*/