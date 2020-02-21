//
// Created by User on 10-Feb-20.
//

#ifndef MODEL_MACHINE_H
#define MODEL_MACHINE_H

#include <iostream>
#include <string>
#include <vector>
#include "Batch.h"
#include "Recipe.h"
#include "Event.h"


//Класс интерфейс
class Machine {
public:
    Machine();//конструктор без параметров
    Machine(std::string name,//конструктор со всеми параметрами
            std::vector <Batch> batches,std::vector <Recipe> recipes, std::vector<Event> events, bool state);
    Machine(std::string name,//конструктор без вектора событий
            std::vector <Batch> batches,std::vector <Recipe> recipes, bool state);
    Machine(std::string name,//конструктор без вектора партий
            std::vector <Recipe> recipes, bool state);
    Machine(const Machine & p);//конструктор копирования
    ~Machine();//деструктор

    virtual void make_event_vector()=0;//метод создаёт вектор событий
    virtual void execute() =0;//метод выполняет событие
    Event push_event ();//возвращает текущее событие в глобальный вектор среды

    friend std::istream &operator>>(std::istream & is, Machine &p);//перегрузка оператора <<
    friend std::ostream &operator<<(std::ostream & os, Machine & p);//перегрузка оператора <<

protected:
    std::string _type;//тип обработки
    std::string _name;//имя
    std::vector <Batch> _bathces;//вектор партий, входная очередь
    std::vector <Recipe> _recipes;//рецепты на машине
    std::vector <Event> _events = {};//вектор событий по порядку
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
class M_flow: public Machine
{
public:
    M_flow();
    M_flow(std::string name,//конструктор со всеми параметрами
            std::vector <Batch> batches,std::vector <Recipe> recipes, std::vector<Event> events, bool state);
    M_flow(std::string name,//конструктор без вектора событий
            std::vector <Batch> batches,std::vector <Recipe> recipes, bool state);
    M_flow(std::string name,//конструктор без вектора партий
            std::vector <Recipe> recipes, bool state);
    M_flow(const M_flow & p);

    void make_event_vector();
    void execute();
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
