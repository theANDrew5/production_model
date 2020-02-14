//
// Created by User on 10-Feb-20.
//
//
#include "Machine.h"
#include <algorithm>
//конструкторы и деструктор интерфейса
Machine::Machine() {}

Machine::Machine(std::string name, std::vector<Recipe> recipes, bool state):
_name(name), _recipes(recipes), _state(state) {}

Machine::Machine(std::string name, std::vector<Batch> batches, std::vector<Recipe> recipes, bool state):
_name(name), _bathces(batches),_recipes(recipes), _state(state) {}

Machine::Machine(const Machine &p):
_name(p._name), _bathces(p._bathces),_recipes(p._recipes), _state(p._state), _events(p._events) {}

Machine::~Machine() = default;

Global_event::Global_event(Event &ev, Machine *p):Event(ev),_pointer(p) {}

//конструкторы и деструктор класса потоковой обработки
M_flow::M_flow() {}

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

std::istream & operator>> (std::istream & is, M_flow & p)//перегрузка оператора сдвига для потока ввода
{
    is>>p._name;
    char ch1=0;
    while (is.get(ch1) && ch1!='#')
    {
        char ch2=0;
        while (is.get(ch2) && ch2!='\n')
        {
            Batch buf;
            is>>buf;
            p._bathces.push_back(buf);
        }
        while (is.get(ch2) && ch2!='\n')
        {
            Recipe buf;
            is>>buf;
            p._recipes.push_back(buf);
        }
        while (is.get(ch2) && ch2!='\n')
        {
            Event buf;
            is>>buf;
            p._events.push_back(buf);
        }
    }
    return is;
}
std::ostream &operator<<(std::ostream & os, M_flow & p)//перегрузка оператора сдвига для вывода
{
    os<<p._name<<'\n';
    for(Batch n:p._bathces) os<<n<<' ';
    os<<'\n';
    for(Recipe n:p._recipes) os<<n<<' ';
    os<<'\n';
    for(Event n:p._events) os<<n<<' ';
    os<<p._state;

    return os;
}