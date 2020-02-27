//
// Created by User on 10-Feb-20.
//

#include "Event.h"
Event::Event(){}
Event::Event(std::string name, unsigned int time): _machine_name(name), _time(time) {}
Event::Event(const Event &p):_machine_name(p._machine_name), _time(p._time) {}

std::istream & operator>> (std::istream & is, Event & p)//перегрузка оператора сдвига для потока ввода
{
    is>>p._machine_name>>p._time;
    return is;
}
std::ostream &operator<<(std::ostream & os, Event & p)//перегрузка оператора сдвига для вывода
{
    return os<<p._machine_name<<' '<<p._time;
}