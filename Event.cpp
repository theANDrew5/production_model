//
// Created by User on 10-Feb-20.
//

#include "Event.h"

/*
std::istream & operator>> (std::istream & is, Event & p)//перегрузка оператора сдвига для потока ввода
{
    is>>p._time;
    return is;
}
*/

std::ostream &operator<<(std::ostream & os, Event & p)//перегрузка оператора сдвига для вывода
{
    return os<<p._m_ptr->get_name()<<' '<<p._time;
}

Event::Event(Machine &m_ptr, unsigned int time):_m_ptr(&m_ptr), _time(time) {}
