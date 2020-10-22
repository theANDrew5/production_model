#pragma once

//#include "pch.h"

#include<vector>

#ifndef MODEL_EXPORTS
#define MODEL_API __declspec(dllexport)
#else
#define MODEL_API __declspec(dllimport)
#endif // !


class Model
{
public:
	
	virtual ~Model();

    virtual void time_shift(unsigned int time)=0;//сдвинуть время модели
    virtual void do_step_till_machine(unsigned int mch_ID)=0;//моделировать до машины ID
    virtual void do_step()=0;//моделировать до коца
    virtual void do_step(unsigned int n)=0;//сделать n шагов моделирования
    virtual void add_batch(unsigned int btc_ID, unsigned int mch_ID, unsigned int pos = 0)=0;//вставить в очередь машины партию
    virtual void add_batch(std::vector<unsigned int>btc_IDs, unsigned int mch_ID, unsigned int pos = 0)=0;//вставить в очередь машины несколько партий
    virtual void replace_queue(std::vector<unsigned int>btc_IDs, unsigned int mch_ID)=0;//замена очереди, не заменяет нулевой элемент

};


MODEL_API Model* environment_create(const char configfile [], const char state_file [], const char logfile [], const char messages [], unsigned int itial_time=0);
