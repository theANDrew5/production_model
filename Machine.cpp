//
// Created by User on 10-Feb-20.
//
//
#include "Machine.h"
#include <algorithm>

//конструкторы и деструктор интерфейса
Machine::Machine() {_last_resipe= Recipe ();}
/*
Machine::Machine(std::string name, std::deque<Recipe> recipes, bool state):
_name(name), _recipes(recipes), _state(state){_last_resipe= Recipe (" ", 0);;}

Machine::Machine(std::string name,
                 std::list <Batch*> batches,std::deque <Recipe> recipes, bool state):
_name(name), _bathces(batches),_recipes(recipes), _state(state){_last_resipe= Recipe (" ", 0);;}
*/

Machine::Machine(int ID,std::deque<Recipe> recipes, std::list<Batch*> batches, bool state, unsigned int time):
_ID(ID),_recipes(recipes),_bathces(batches), _state(state),_time(time)
{
    _last_resipe=Recipe ();
}

Machine::Machine(const Machine &p):
_ID(p._ID), _bathces(p._bathces),_recipes(p._recipes), _state(p._state),_time(p._time)
{_last_resipe= Recipe ();}

Machine::~Machine() = default;


//конструкторы и деструктор класса потоковой обработки
M_flow::M_flow()
{
    _type="flow";
}

M_flow::M_flow(int ID,std::deque<Recipe> recipes, std::list<Batch*> batches, bool state):
        Machine(ID,recipes, batches, state)
{
    _type="flow";
}

M_flow::M_flow(const M_flow &p):Machine(p)
{
    _type="flow";
}

M_flow::~M_flow() = default;


//Метод выполняет рассчёт события в очереди
unsigned int M_flow::push_ev()
{
    if (!_bathces.empty())
    {
        Batch *it=_bathces.front();
        Recipe &rcp = it->get_first();
        if(std::any_of(_recipes.begin(),_recipes.end(),[rcp](Recipe const r){return rcp==r;}))
        //проверка рецептов
        {
            return  ((this->_last_resipe==it->get_first())?
            rcp.get_time()*it->get_count():rcp.get_time()*it->get_count()+this->_time ); //OK
        }
        else throw (it);//ошибка в очереди партия с неверным рецептом
    }
    else
    {
        Batch *ptr= nullptr;
        throw (ptr) ; //очередь пуста
    }
 }

void M_flow::execute(std::ostream *log)//выполнение события, просто удаляем ссылку на партию
{

    Batch* bt_ptr=this->_bathces.front();
    if (this->_last_resipe!=bt_ptr->get_first())
    {
        *log<<"Change recipe\nMachine ID:\t"<< this->_ID<<"\ttime:\t"<< this->_time<<'\n';
        _last_resipe=bt_ptr->get_first();
        //вставить вывод в лог
    }
    *log<<"Execute batch\nMachine ID:\t"<< this->_ID<<"\tBatch ID:\t"<<bt_ptr->get_first().get_ID()<<'\t';
    bt_ptr->execute();
    this->_bathces.pop_front();
}

unsigned int M_flow::get_ID()
{
    return this->_ID;
}

/*
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
*/

std::ostream &operator<<(std::ostream & os, Machine &p)//перегрузка оператора сдвига для вывода
{
    os<<p._type<<' ';
    os<<p._ID<<' ';
    os<<p._state<<' ';
    for(Recipe n:p._recipes) os<<n<<' ';
    os<<'\t';
    for(Batch* n:p._bathces) os<<n->get_ID()<<' ';
    os<<'\t';
    return os;
}





