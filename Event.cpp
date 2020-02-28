//
// Created by User on 10-Feb-20.
//

#include "Event.h"
Event::Event(){}
Event::Event(unsigned int time): _time(time) {}
Event::Event(const Event &p): _time(p._time) {}

std::istream & operator>> (std::istream & is, Event & p)//перегрузка оператора сдвига для потока ввода
{
    is>>p._time;
    return is;
}
std::ostream &operator<<(std::ostream & os, Event & p)//перегрузка оператора сдвига для вывода
{
    return os<<p._time;
}