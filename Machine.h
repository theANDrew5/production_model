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

//Класс интерфейс

class Machine
{
public:
    Machine();//конструктор без параметров
    Machine(int ID,std::deque<Recipe> recipes, std::list<Batch*> batches={}, bool state=true, unsigned int time=0);
    Machine(const Machine & p);//конструктор копирования
    virtual ~Machine();//деструктор

    virtual unsigned int push_ev()=0;//метод возвращает время события
    virtual void execute() =0;//метод выполняет событие
    virtual unsigned int get_ID()=0;

protected:
    std::string _type;//тип обработки
    unsigned int _ID;//имя
    bool _state;//состояние
    std::deque <Recipe> _recipes;//рецепты на машине
    std::list <Batch*> _bathces;// входная очередь в виде ссылок на партии
    Recipe _last_resipe;//последний рецепт
    unsigned int _time;//время смены рецепта

    friend void read_machines(std::istream & is, Machine &ptr_m, Environment &ptr_e);//вместо оператора >>
    friend std::ostream &operator<<(std::ostream & os, Machine & p);//перегрузка оператора <<
};

//наследник для потоковой обработки
class M_flow: public Machine
{
public:
    M_flow();
    M_flow(int ID,std::deque<Recipe> recipes, std::list<Batch*> batches={}, bool state=true);
    M_flow(const M_flow & p);

    unsigned int push_ev();//метод возвращает время события
    void execute();//метод выполняет событие
    unsigned int get_ID();
    ~M_flow();
};



//наследник обработки группой партий
class M_group:public Machine
{
public:
	M_group();

	M_group(std::string name,std::vector <Recipe> recipes, bool state);

    M_group(std::string name,std::vector <Batch> batches,std::vector <Recipe> recipes, bool state);

    M_group(const M_group & p);

	
	unsigned int push_ev();

	void execute();

	std::string get_name();

	~M_group();
};


/*
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
