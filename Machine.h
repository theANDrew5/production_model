//
// Created by User on 10-Feb-20.
//

#ifndef MODEL_MACHINE_H
#define MODEL_MACHINE_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <functional>
#include "Batch.h"
#include "Recipe.h"


class Environment;//для функции read_machines
//временный класс события передаваяемый в Event
class Mch_ev
{
public:
    Mch_ev();
    Mch_ev(Batch& p, unsigned int t);
    Mch_ev(Mch_ev &p);
    Batch& _b_ptr;
    unsigned int _time;
};


//Класс интерфейс

class Machine
{
public:
    Machine();//конструктор без параметров
    Machine(std::string name,//конструктор со всеми параметрами
            std::list <std::reference_wrapper<Batch>> batches,std::deque <Recipe> recipes, bool state);
    Machine(std::string name,//конструктор без вектора партий
            std::deque <Recipe> recipes, bool state);
    Machine(const Machine & p);//конструктор копирования
    ~Machine();//деструктор

    virtual Mch_ev push_ev()=0;//метод возвращает время события
    virtual void execute() =0;//метод выполняет событие
    virtual  std::string get_name()=0;

protected:
    std::string _type;//тип обработки
    std::string _name;//имя
    bool _state;//состояние
    std::deque <Recipe> _recipes;//рецепты на машине
    std::list <std::reference_wrapper<Batch>> _bathces;// входная очередь в виде ссылок на партии

    friend void read_machines(std::istream & is, Machine &ptr_m, Environment &ptr_e);//вместо оператора >>
    friend std::ostream &operator<<(std::ostream & os, Machine & p);//перегрузка оператора <<
};


//наследник для потоковой обработки
class M_flow: public Machine
{
public:
    M_flow();
    M_flow(std::string name,//конструктор без вектора событий
    std::list <std::reference_wrapper<Batch>> batches,std::deque <Recipe> recipes, bool state);
    M_flow(std::string name,//конструктор без вектора партий
           std::deque <Recipe> recipes, bool state);
    M_flow(const M_flow & p);

    Mch_ev push_ev();//метод возвращает время события
    void execute();//метод выполняет событие
    virtual  std::string get_name();
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
