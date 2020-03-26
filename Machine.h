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
    Machine(int ID,std::deque<Recipe> recipes, bool state=true, unsigned int time=0, std::list<Batch*> batches={});
    Machine(const Machine & p);//конструктор копирования
    virtual ~Machine();//деструктор

    virtual unsigned int push_ev()=0;//метод возвращает время события
    virtual void execute(std::ostream *log) =0;//метод выполняет событие
    virtual unsigned int get_ID()=0;//возвращает ID машины
    virtual void insert_batch(Batch* btc, unsigned int pos)=0;//вставляет партию в очередь
    virtual void insert_batch(std::deque <Batch*> &container, unsigned int pos=0)=0;

    bool check_queue();

protected:
    std::string _type;//тип обработки
    unsigned int _ID;//имя
    bool _state;//состояние
    std::deque <Recipe> _recipes;//рецепты на машине
    std::list <Batch*> _batches;// входная очередь в виде ссылок на партии
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
    M_flow(int ID,std::deque<Recipe> recipes, bool state=true, unsigned int time=0, std::list<Batch*> batches={});
    M_flow(const M_flow & p);

    unsigned int push_ev();//метод возвращает время события
    void execute(std::ostream *log);//метод выполняет событие
    unsigned int get_ID();
    void insert_batch(Batch* btc, unsigned int pos);
    virtual void insert_batch(std::deque <Batch*> &container, unsigned int pos=0);
    ~M_flow();
};



//наследник обработки группой партий
class M_group:public Machine
{
public:
	
	//		Defualt constructor
	M_group();

	//		Main constructor
	M_group(int ID, std::deque<Recipe> recipes, bool state = true, unsigned int time = 0, std::list<Batch*> batches = {});

	//		Copy constructor
	M_group(const M_group &p);

	//		Returns time of even execution on this machine
	unsigned int push_ev();

	//		execute an event on this machine
	void execute(std::ostream *log);
	
	//		return an ID of machine
	unsigned int get_ID();

	void insert_batch(Batch* btc, unsigned int pos);//вставляет партию в очередь

	void insert_batch(std::deque <Batch*> &container, unsigned int pos = 0);

	~M_group();
};



//наследник обработки пачкой пластин
class M_stack: public Machine
{
public:
	M_stack();
	M_stack(int ID, std::deque<Recipe> recipes, bool state = true, unsigned int time = 0, std::list<Batch*> batches = {});
	M_stack(const M_stack & p);

	unsigned int push_ev();//метод возвращает время события
	void execute(std::ostream *log);//метод выполняет событие
	unsigned int get_ID();
	void insert_batch(Batch* btc, unsigned int pos);
	void insert_batch(std::deque <Batch*> &container, unsigned int pos = 0);
	~M_stack();
};


#endif //MODEL_MACHINE_H
