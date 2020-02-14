//
// Created by User on 10-Feb-20.
//

#ifndef MODEL_EVENT_H
#define MODEL_EVENT_H

#include <iostream>
#include <string>
class Event
{
public:
    Event();
    Event(std::string name, unsigned int time);
    Event(Event const  &p);

    friend std::istream & operator>> (std::istream & is, Event & p)//перегрузка оператора сдвига для потока ввода
    {
       is>>p._machine_name>>p._time;
        return is;
    }
    friend std::ostream &operator<<(std::ostream & os, Event & p)//перегрузка оператора сдвига для вывода
    {
        return os<<p._machine_name<<' '<<p._time;
    }

protected:
    std::string _machine_name; //Имя машины
    unsigned int _time;//длительность события
};


#endif //MODEL_EVENT_H
