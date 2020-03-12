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

//интерфейс
class Event
{
public:

Event(Machine& m_ptr, unsigned int time);

unsigned int get_time();
Machine* get_ptr();
void execute(std::ostream *log);

friend std::ostream &operator<<(std::ostream & os, Event & p);
friend bool operator<(Event& r_ev, Event& l_ev);
friend bool operator>(Event& r_ev, Event& l_ev);

private:
    Machine* _m_ptr;
    unsigned int _time;//длительность события
};



#endif //MODEL_EVENT_H
