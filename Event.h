//
// Created by User on 10-Feb-20.
//

#ifndef MODEL_EVENT_H
#define MODEL_EVENT_H

#include "pch.h"// pch.h: This is a precompiled header file.
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
void time_shift(unsigned int shift);

friend std::ostream &operator<<(std::ostream & os, Event & p);
friend bool operator<(Event& r_ev, Event& l_ev);
friend bool operator>(Event& r_ev, Event& l_ev);

private:
    Machine* _m_ptr;
    unsigned int _time;//длительность события
};



#endif //MODEL_EVENT_H
