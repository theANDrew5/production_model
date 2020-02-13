//
// Created by User on 10-Feb-20.
//

#ifndef MODEL_EVENT_H
#define MODEL_EVENT_H

#include <string>
class Event
{
public:
    Event(std::string name, unsigned int time);
    Event(Event const  &p);

protected:
    std::string _machine_name; //Имя машины
    unsigned int _time;//длительность события

};


#endif //MODEL_EVENT_H
