//
// Created by User on 10-Feb-20.
//

#include "Event.h"


Event::Event(Machine &m_p, Batch& b_p, unsigned int time):_m_ptr(m_p),_b_ptr(b_p),_time(time){}
Event::Event(Event const &p):_m_ptr(p._m_ptr),_b_ptr(p._b_ptr),_time(p._time) {}

/*
std::istream & operator>> (std::istream & is, Event & p)//перегрузка оператора сдвига для потока ввода
{
    is>>p._time;
    return is;
}
*/

std::ostream &operator<<(std::ostream & os, Event & p)//перегрузка оператора сдвига для вывода
{
    return os<<p._m_ptr.get_name()<<' '<<p._b_ptr.get_name()<<' '<<p._time;
}




