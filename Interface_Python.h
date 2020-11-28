#pragma once
#pragma once

//#include "pch.h"

#include<vector>
#include <pybind11/pybind11.h>

/*
class Model
{
public:

    virtual ~Model();

    virtual void time_shift(unsigned int time) = 0;//сдвинуть время модели
    virtual void do_step_till_machine(unsigned int mch_ID) = 0;//моделировать до машины ID
    virtual void do_step() = 0;//моделировать до коца
    virtual void do_step(unsigned int n) = 0;//сделать n шагов моделирования
    virtual void add_batch(unsigned int btc_ID, unsigned int mch_ID, unsigned int pos = 0) = 0;//вставить в очередь машины партию
    virtual void add_batch(std::vector<unsigned int>btc_IDs, unsigned int mch_ID, unsigned int pos = 0) = 0;//вставить в очередь машины несколько партий
    virtual void replace_queue(std::vector<unsigned int>btc_IDs, unsigned int mch_ID) = 0;//замена очереди, не заменяет нулевой элемент

};



class PyModel : public Model
{
public:

    using Model::Model;

    void time_shift(unsigned int time) override;//сдвинуть время модели
    void do_step_till_machine(unsigned int mch_ID) override;//моделировать до машины ID
    void do_step() override;//моделировать до коца
    void do_step(unsigned int n) override;//сделать n шагов моделирования
    void add_batch(unsigned int btc_ID, unsigned int mch_ID, unsigned int pos = 0) override;//вставить в очередь машины партию
    void add_batch(std::vector<unsigned int>btc_IDs, unsigned int mch_ID, unsigned int pos = 0) override;//вставить в очередь машины несколько партий
    void replace_queue(std::vector<unsigned int>btc_IDs, unsigned int mch_ID) override;//замена очереди, не заменяет нулевой элемент

};
*/
