//
// Created by User on 10-Feb-20.
//

#include "pch.h"// pch.h: This is a precompiled header file.
#include "Event.h"

Event::Event(Machine &m_ptr, unsigned int time):_m_ptr(&m_ptr), _time(time) {}

bool operator<(Event& r_ev, Event& l_ev)
{
    return r_ev._time<l_ev._time;
}

std::ostream &operator<<(std::ostream & os, Event & p)//перегрузка оператора сдвига для вывода
{
    return os<<p._m_ptr->get_ID()<<' '<<p._time;
}



bool operator>(Event &r_ev, Event &l_ev)
{
    return r_ev._time>l_ev._time;;
}

unsigned int Event::get_time()
{
    return this->_time;
}

Machine *Event::get_ptr()
{
    return this->_m_ptr;
}

void Event::execute(std::ostream *log)
{
    this->_m_ptr->execute(log);
    *log<<"\ttime: "<< this->_time<<'\n';
}

void Event::time_shift(unsigned int shift)
{
    this->_time-=shift;
}
