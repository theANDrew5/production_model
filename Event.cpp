//
// Created by User on 10-Feb-20.
//

#include "Event.h"
Event::Event(std::string name, unsigned int time): _machine_name(name), _time(time) {}
Event::Event(const Event &p):_machine_name(p._machine_name), _time(p._time) {}