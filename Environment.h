//
// Created by User on 10-Feb-20.
//

#ifndef MODEL_ENVIRONMENT_H
#define MODEL_ENVIRONMENT_H

#include "pch.h"// pch.h: This is a precompiled header file.

#include "Event.h"
#include "Batch.h"
#include "Machine.h"



//static const bool DEBUG = true;

class Environment
{
public:
    Environment();
    Environment(std::string& configfile, std::string& state_file, std::string& logfile, std::string& messages, unsigned int itial_time);
    Environment(std::istream &is_conf, std::ostream &os_log=std::cout,
                std::ostream &os_mes=std::cout, unsigned int time = 0);
    Environment(std::istream &is_conf, std::istream &is_state, std::ostream &os_log=std::cout,
            std::ostream &os_mes=std::cout, unsigned int time=0);

    ~Environment();


    friend std::ostream & operator<< (std::ostream & os, Environment & p);//перегрузка оператора <<

    void time_shift(unsigned int time);//сдвинуть время модели
    void do_step_till_machine(unsigned int mch_ID);//моделировать до машины ID
    void do_step();//моделировать до коца
    void do_step(unsigned int n);//сделать n шагов моделирования
    void add_batch(unsigned int btc_ID, unsigned int mch_ID, unsigned int pos=0);//вставить в очередь машины партию
    void add_batch(std::vector<unsigned int>btc_IDs, unsigned int mch_ID, unsigned int pos=0);
    //вставить в очередь машины несколько партий
    void replace_queue(std::vector<unsigned int>btc_IDs, unsigned int mch_ID);//замена очереди, не заменяет нулевой элемент

    #if DEBUG
        void print_env();
    #endif // DEBUG

private:

    void push_event(Machine & mch); //вставка события из машины
    void make_events();//рассчёт массива событий при запуске модели
    void change_event(Machine *mch);//замена события
    Batch* search_batch(unsigned int btc_ID);//возвращает указатель на партию по её ID
    Machine* search_machine(unsigned int mch_ID);//возвращает указатель на машину по её ID
    std::deque<Event>::iterator search_event (Machine *ptr);//возвращает итератор на событие по указателю на машину

    std::string _name;//имя среды
    std::list <Batch> _batches;//партии
    std::list <Machine*> _machines;//вектор машин
    std::deque <Event> _events;//вектор событий, по которому происходят шаги
    unsigned int _global_model_time;
    std::istream * _config_file;//файл конфигурации в нём описаны имя среды и машины
    std::istream * _is_state_file;//входной файл состояния внём описаны партии и очереди в машины
    //std::ostream _os_state_file;//выходной файл состояния
    std::ostream * _log_file;//последовательность ивентов
    std::ostream * _messages;//поток для вывода сообщений

    friend std::istream & operator>> (std::istream & is, Environment & p);
    //перегрузка оператора сдвига для чтения файла конфигурации
    void read_recipes(std::istream &is, std::deque <Recipe> &container);//читаем последовательность рецептов
    void read_state(std::istream &is);//читаем файл состояния
    void read_queues(std::istream &is);
    void read_ev(std::istream & is);//чтение событий

#if DEBUG
    void read_env(std::istream &is);
#endif //  DEBUG



};


#endif //MODEL_ENVIRONMENT_H
