//
// Created by User on 10-Feb-20.
//

#ifndef MODEL_EVENT_H
#define MODEL_EVENT_H

#include <iostream>
#include <string>
#include "Batch.h"
#include "Machine.h"

class Environment;//для функции read_machines


class Event
{
public:
    Event();
    Event(Machine &m_p, Batch& b_p, unsigned int time);
    Event(Event const  &p);

    friend std::ostream &operator<<(std::ostream & os, Event & p);//перегрузка оператора сдвига для вывода

private:
    Machine& _m_ptr;
    Batch& _b_ptr;
    unsigned int _time;//длительность события

    //friend void read_ev(std::istream & is, Event &ptr_ev, Environment &ptr_e);
};


#endif //MODEL_EVENT_H
