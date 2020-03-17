//
// Created by User on 10-Feb-20.
//

#ifndef MODEL_ENVIRONMENT_H
#define MODEL_ENVIRONMENT_H

#include <string>
#include <list>
#include <deque>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "Event.h"
#include "Batch.h"
#include "Machine.h"
class Environment {
public:
    Environment();
    Environment(std::istream &is, std::ostream &os=std::cout,unsigned int time=0);

    friend std::istream & operator>> (std::istream & is, Environment & p);//перегрузка оператора сдвига для потока ввода
    friend std::ostream & operator<< (std::ostream & os, Environment & p);//перегрузка оператора <<

    void push_event(Machine & mch);//вставка события из машины
    void do_step(unsigned int n);//сделать n шагов моделирования
    void add_batch(unsigned int btc_ID, unsigned int mch_ID, unsigned int pos);//вставить в очередь машины партию
private:

    void make_events();//рассчёт массива событий при запуске модели
    Batch* search_batch(unsigned int btc_ID);//возвращает указатель на партию по её ID
    Machine* search_machine(unsigned int mch_ID);//возвращает указатель на машину по её ID


    std::string _name;//имя среды
    std::list <Batch> _batches;//партии
    std::list <Machine*> _machines;//вектор машин
    std::deque <Event> _events;//вектор событий, по которому происходят шаги
    unsigned int _global_model_time;
    std::istream * _is_state_file;//входной файл состояния, чтобы создать среду
    //std::ostream _os_state_file;//выходной файл состояния, чтобы среду сохранить
    std::ostream * _log_file;//последовательность ивентов


    friend void read_machines(std::istream & is, Machine &ptr_m, Environment &ptr_e);//чтение машин
    void read_ev(std::istream & is);//чтение событий
    Batch&  find_bt (std::string name);

};


#endif //MODEL_ENVIRONMENT_H
