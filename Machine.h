//
// Created by User on 10-Feb-20.
//

#ifndef MODEL_MACHINE_H
#define MODEL_MACHINE_H

#include <string>
#include <vector>
#include "Batch.h"
#include "Recipe.h"
#include "Event.h"


//Класс интерфейс
class Machine {
public:
    Machine(std::string name,std::vector <Recipe> recipes, bool state);
    Machine(std::string name,std::vector <Batch> batches,std::vector <Recipe> recipes, bool state);
    Machine(const Machine & p);
    ~Machine();

    virtual void make_event_vector()=0;//метод создаёт вектор событий
    Event push_event ();//возвращает текущее событие в глобальный вектор среды
    virtual void execute() =0;//метод выполняет событие

protected:
    std::string _name;//имя
    std::vector <Batch> _bathces;//входная очередь в форме ссылок на партии
    std::vector <Recipe> _recipes;//рецепты на машине
    std::vector <Event> _events;//вектор событий по порядку
    bool _state;//состояние

};
class Global_event:Event //наследник с дополнительным полем, указателем на машину
{
public:
    Global_event(std::string name, unsigned int time, Machine * p);
    Global_event(Event &ev, Machine *p);
private:
    Machine * _pointer;
};
//наследник для потоковой обработки
class M_flow:Machine
{
public:
    M_flow(std::string name,std::vector <Recipe> recipes, bool state);
    M_flow(std::string name,std::vector <Batch> batches,std::vector <Recipe> recipes, bool state);
    M_flow(const M_flow & p);

    void make_event_vector();
    Global_event push_event();
    ~M_flow();
};


/*
//наследник обработки группой партий
class M_group:Machine
{
public:
    M_group(std::string name,std::vector <Recipe> recipes, bool state);
    M_group(std::string name,std::vector <Batch> batches,std::vector <Recipe> recipes, bool state);
    //M_group(const M_group & p);

    void execution();
};

//наследник обработки пачкой пластин
class M_stack:Machine
{
public:
    M_stack(std::string name,std::vector <Recipe> recipes, bool state);
    M_stack(std::string name,std::vector <Batch> batches,std::vector <Recipe> recipes, bool state);
    //M_stack(const M_stack & p);

    void execution();
};
*/

#endif //MODEL_MACHINE_H
