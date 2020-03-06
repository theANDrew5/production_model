//
// Created by User on 10-Feb-20.
//

#include "Environment.h"

void read_machines(std::istream & is, Machine &ptr_m, Environment &ptr_e)
{

    is>>ptr_m._name;
    is>>ptr_m._state;
    is.get();//потому что >> не читает /n и его захватывает getline
    while (is.peek()!='\t')//читаем рецепты
    {
        Recipe buf;
        is >> buf;
        ptr_m._recipes.push_back(buf);
    }
    is.get();//потому что >> не читает /n
    while (is.peek()!='\t')//читаем имена партий
    {
        std::string bt_name;
        is>>bt_name;
        std::_List_iterator<Batch> it_b=
                std::find_if(ptr_e._batches.begin(), ptr_e._batches.end(),
                        [bt_name](Batch b){ return bt_name==b.get_name() ;});//
        ptr_m._bathces.push_back(*it_b);
    }
    is.get();//потому что >> не читает /n
    //return is;
}


void Environment::read_ev(std::istream &is)
{
    std::string buf_string;
    is>>buf_string;
    std::_List_iterator<std::reference_wrapper<Machine>> it_mch =
            std::find_if(this->_machines.begin(), this->_machines.end(),
                    [buf_string](Machine &mch){ return buf_string==mch.get_name();});//
    /*buf_string.clear();
    is>>buf_string;
    std::_List_iterator<Batch> it_b = std::find_if(this->_batches.begin(), this->_batches.end(), [buf_string](Batch b){ return buf_string == b.get_name();});*/
    unsigned int time;
    is>>time;
    this->_envents.emplace_back(*it_mch,time);
}

std::istream & operator>> (std::istream & is, Environment & p)
{
    is>>p._name;
    is.get();//потому что >> не читает /n
    while (is.peek()!='\n')//читаем партии
    {
        std::stringstream buf_str;
        std::string buf_string;
        std::getline(is,buf_string,'\t');
        buf_str.str(buf_string);
        Batch buf;
        buf_str>>buf;
        p._batches.push_back(buf);
    }
    is.get();//
    while (is.peek()!='\n')//читаем машины
    {
        std::string buf_string;
        is>>buf_string;
        Machine *ptr;
        if (buf_string=="flow") ptr = new M_flow();//здесь вставить остальные условия
        p._machines.push_back(*ptr);
        read_machines(is,*ptr,p);
        //
    }
    is.get();//потому что >> не читает /n
    while (is.peek()!='\n')//читаем события
    {
        p.read_ev(is);
    }
    return is;
}

std::ostream &operator<<(std::ostream &os, Environment &p)
{
    os<<p._name<<'\n';
   for (Batch n:p._batches) os<<n<<'\t';
   os<<'\n';
   for (std::reference_wrapper<Machine> n:p._machines) os<<n<<'\t';
   os<<'\n';
   for (Event n:p._envents) os<<n<<' ';
   os<<'\n';


    return os;
}



Environment::Environment(std::istream &is):_is_state_file(&is)
{
    *_is_state_file>>*this;
    _global_model_time=0;
}

Environment::Environment()
{
    _global_model_time=0;
}

void Environment::make_events()
{
   // for(Machine& n:this->_machines)
}









