//
// Created by User on 10-Feb-20.
//

#include "Event.h"
Event::Event(Machine *p, unsigned int time):_pointer(p), _time(time) {}
Event::Event(const Event &p):_pointer(p._pointer), _time(p._time) {}