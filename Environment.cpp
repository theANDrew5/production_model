//
// Created by User on 10-Feb-20.
//

#include "Environment.h"

static const bool DEBUG=true;

void read_machines(std::istream & is, Machine &ptr_m, Environment &ptr_e)
{

    is>>ptr_m._ID;
    is>>ptr_m._state;
    is>>ptr_m._time;
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
        unsigned int bt_ID;
        is>>bt_ID;
        std::_List_iterator<Batch> it_b=
                std::find_if(ptr_e._batches.begin(), ptr_e._batches.end(),
                        [bt_ID](Batch b){ return bt_ID==b.get_ID() ;});//
        ptr_m._bathces.push_back(&*it_b);
    }
    is.get();//потому что >> не читает /n
    //return is;
}


void Environment::read_ev(std::istream &is)
{
    unsigned int mch_ID;
    is>> mch_ID;
    std::_List_iterator<std::reference_wrapper<Machine>> it_mch =
            std::find_if(this->_machines.begin(), this->_machines.end(),
                    [ mch_ID](Machine &mch){ return mch_ID==mch.get_ID();});
    unsigned int time;
    is>>time;
    this->_events.emplace_back(*it_mch,time);
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
    p.make_events();
    return is;
}

std::ostream &operator<<(std::ostream &os, Environment &p)
{
    os<<p._name<<'\n';
   for (Batch n:p._batches) os<<n<<'\t';
   os<<'\n';
   for (std::reference_wrapper<Machine> n:p._machines) os<<n<<'\t';
   os<<'\n';
   for (Event n:p._events) os<<n<<' ';
   os<<'\n';


    return os;
}



Environment::Environment()
{
    _global_model_time=0;
}

Environment::Environment(std::istream &is, std::ostream &os,unsigned int time):
                        _is_state_file(&is),_global_model_time(time),_log_file(&os)
{
    *_is_state_file>>*this;
}


void Environment::push_event(Machine &mch)
{
    try
    {
        this->_events.emplace_back(mch, mch.push_ev());
    }
    catch (Batch* bt_ptr)
    {
        if (bt_ptr!= nullptr)
        {
            *this->_log_file << "Batch with wrong recipe!\n\tMachine ID: " << mch.get_ID()

                       << "\n\tBatch ID: " << bt_ptr->get_ID() << '\n';
            throw (-1);//рассчёт событий прерван
        }
        else
            *this->_log_file<<"Queue is empty!\n\tMachine ID: "<<mch.get_ID()<<'\n';
    }
    //сортируем
    Event& last=this->_events.back();
    for (auto ev=this->_events.begin();ev!=--(this->_events.end());ev++)
    {
        if (*ev>this->_events.back())
        {
            this->_events.insert(ev, this->_events.back());
            this->_events.pop_back();
            break;
        }
    }
}


//метод рассчёта событий
void Environment::make_events()
{
    for(Machine& mch:this->_machines)
    {
        try
        {
            this->push_event(mch);
        }
        catch (int)
        {
            *this->_log_file<<"Modelling stopped!\n";
        }
    }

    if(DEBUG)
    {
        for (auto n:this->_events) std::cout<<n<<'\t';
        std::cout<<'\n';
    }

}



void Environment::do_step(unsigned int n) {
    if (n < 1) return;
    try
    {
        if (this->_events.empty()) throw (-1);
        auto ev_it = this->_events.begin();
        for (int i = 0; i < n; ++i)
        {

            *this->_log_file << "MODEL TIME:\t" << this->_global_model_time << '\n';
            if (this->_events.empty()) throw (i);
            this->_global_model_time += ev_it->get_time();
            auto ev_it_f = ev_it;
            ++ev_it_f;
            for (ev_it_f; ev_it_f != this->_events.end()--; ev_it_f++) {
                ev_it_f->time_shift(ev_it->get_time());
            }
            ev_it->execute(this->_log_file);
            ev_it++;
            this->_events.pop_front();
        }

    }
    catch (int err)
    {
        switch (err)
        {
            case -1:
                *this->_log_file << "Event vector is empty!\n";
                break;
            default:
                *this->_log_file << "End of event vector reached by step:\t"<<err<<'\n';
        }

    }
}












