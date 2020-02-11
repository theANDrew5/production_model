//
// Created by User on 10-Feb-20.
//

#ifndef MODEL_EVENT_H
#define MODEL_EVENT_H

#include "Machine.h"
class Event {
public:
    Event(Machine *p, unsigned int time);
    Event(const Event &p);
private:
    Machine * _pointer; //указатель на объект машины
    unsigned int _time;//длительность события

};


#endif //MODEL_EVENT_H
