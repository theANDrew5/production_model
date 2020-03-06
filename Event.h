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

friend std::ostream &operator<<(std::ostream & os, Event & p);

private:
    Machine* _m_ptr;
    unsigned int _time;//длительность события
};



#endif //MODEL_EVENT_H
