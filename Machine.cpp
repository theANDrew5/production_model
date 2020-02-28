//
// Created by User on 10-Feb-20.
//
//
#include "Machine.h"
#include <algorithm>
//конструкторы и деструктор интерфейса
Machine::Machine() {}

Machine::Machine(std::string name, std::deque<Recipe> recipes, bool state):
_name(name), _recipes(recipes), _state(state){}

Machine::Machine(std::string name,
                 std::list <std::reference_wrapper<Batch>> batches,std::deque <Recipe> recipes, bool state):
_name(name), _bathces(batches),_recipes(recipes), _state(state){}

Machine::Machine(std::string name, std::list <std::reference_wrapper<Batch>> batches,
        std::deque <Recipe> recipes, std::list<Event> events, bool state):
_name(name), _bathces(batches),_recipes(recipes),_events(events), _state(state) {}

Machine::Machine(const Machine &p):
_name(p._name), _bathces(p._bathces),_recipes(p._recipes), _state(p._state), _events(p._events) {}

Machine::~Machine() = default;

Global_event::Global_event(Event &ev, Machine *p):Event(ev),_pointer(p) {}

//конструкторы и деструктор класса потоковой обработки
M_flow::M_flow() {}

M_flow::M_flow(std::string name, std::deque <Recipe> recipes, bool state):
        Machine(name,recipes,state)
{
    _type="flow";
}

M_flow::M_flow(std::string name, std::list<std::reference_wrapper<Batch>> batches, std::deque<Recipe> recipes, bool state):
        Machine(name, batches, recipes, state)
{
    _type="flow";
}

M_flow::M_flow(std::string name,
               std::list <std::reference_wrapper<Batch>> batches,std::deque <Recipe> recipes, std::list<Event> events, bool state):
Machine(name,batches,recipes,events,state)
{
    _type="flow";
}

M_flow::M_flow(const M_flow &p):Machine(p)
{
    _type="flow";
}

M_flow::~M_flow() = default;

//Метод выполняет рассчёт последовательности по порядку
void M_flow::make_event_vector()
{

        if (!_bathces.empty())
        {
            for (Batch &it : _bathces)
            {
                Recipe &rcp = it.get_first();
                if(std::any_of(_recipes.begin(),_recipes.end(),[rcp](Recipe const r){return rcp==r;}))
                //проверка рецептов
                {
                    this->_events.push_back (Event(rcp.get_time()*it.get_count()));
                }
                else throw (it);//ошибка в очереди партия с неверным рецептом
            }
            //throw;//ок очередь обработана
        }
        else
        {
            Batch *ptr= nullptr;
            throw (ptr) ; //очередь пуста
        }

 }

Global_event M_flow::push_event()
{
    return Global_event(*_events.begin(),this);
}

void M_flow::execute()
{
    _events.pop_front();

}

std::istream &operator>>(std::istream &is, Machine &p) {
    is>>p._type;
    is>>p._name;
    is>>p._state;
    is.get();//потому что >> не читает /n и его захватывает getline
    while (is.peek()!='\n')
    {
        std::stringstream buf_str;
        std::string buf_string;
        std::getline(is,buf_string,'\t');
        buf_str.str(buf_string);
        Batch buf;
        buf_str>>buf;
        p._bathces.push_back(buf);
    }
    is.get();//потому что >> не читает /n
    while (is.peek()!='\n')
    {
        Recipe buf;
        is >> buf;
        p._recipes.push_back(buf);
    }
    is.get();//потому что >> не читает /n
    while (is.peek()!='\n')
    {
        Event buf;
        is >> buf;
        p._events.push_back(buf);
    }
    return is;
}


std::ostream &operator<<(std::ostream & os, Machine &p)//перегрузка оператора сдвига для вывода
{
    os<<p._type<<'\n';
    os<<p._name<<'\n';
    os<<p._state<<'\n';
    for(Batch n:p._bathces) os<<n<<'\t';
    os<<'\n';
    for(Recipe n:p._recipes) os<<n<<' ';
    os<<'\n';
    for(Event n:p._events) os<<n<<' ';
    os<<'\n';
    return os;
}

