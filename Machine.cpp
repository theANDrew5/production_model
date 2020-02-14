//
// Created by User on 10-Feb-20.
//
//
#include "Machine.h"
#include <algorithm>
//конструкторы и деструктор интерфейса
Machine::Machine(std::string name, std::vector<Recipe> recipes, bool state):
_name(name), _recipes(recipes), _state(state) {}

Machine::Machine(std::string name, std::vector<Batch> batches, std::vector<Recipe> recipes, bool state):
_name(name), _bathces(batches),_recipes(recipes), _state(state) {}

Machine::Machine(const Machine &p):
_name(p._name), _bathces(p._bathces),_recipes(p._recipes), _state(p._state), _events(p._events) {}

Machine::~Machine() = default;

Global_event::Global_event(Event &ev, Machine *p):Event(ev),_pointer(p) {}

//конструкторы и деструктор класса потоковой обработки
M_flow::M_flow(std::string name, std::vector<Recipe> recipes, bool state):
Machine(name,recipes,state) {}

M_flow::M_flow(std::string name,std::vector <Batch> batches,std::vector <Recipe> recipes, bool state):
Machine(name,batches,recipes,state){}

M_flow::M_flow(const M_flow &p):Machine(p) {}

M_flow::~M_flow() = default;

//Метод выполняет рассчёт последовательности по порядку
void M_flow::make_event_vector()
{

    try
    {
        if (!_bathces.empty())
        {
            for (Batch it : _bathces)
            {
                Recipe * rcp = it.get_first();
                if(std::any_of(_recipes.begin(),_recipes.end(),[rcp](Recipe r){return rcp==&r;}))
                {
                    Machine * t =0;
                    this->_events.push_back(Event(this->_name,it.get_first()->get_time()*it.get_count()));
                }
                else throw (it);//ошибка в очереди партия с неверным рецептом
            }
            std::reverse(_events.begin(),_events.end());//разворот для ускорения обработки, потому что обрезать с конца быстрее
            throw;//ок очередь обработана
        }
        else
        {
            Batch *ptr= nullptr;
            throw (ptr) ; //очередь пуста
        }
    }
    catch (Batch &cat)
    {

    }
}

Global_event M_flow::push_event()
{
    return Global_event(*_events.end(),this);
}

void M_flow::execute()
{
    _events.pop_back();//обрезаем последний потому что вектор развёрнут
}