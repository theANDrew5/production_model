//
// Created by User on 10-Feb-20.
//

#include "Environment.h"

static const bool DEBUG=true;


void Environment::read_ev(std::istream &is)
{
    unsigned int mch_ID;
    is>> mch_ID;
    auto it_mch =
            std::find_if(this->_machines.begin(), this->_machines.end(),
                    [ mch_ID](Machine *mch){ return mch_ID==mch->get_ID();});
    unsigned int time;
    is>>time;
    this->_events.emplace_back(**it_mch,time);
}


void Environment::read_recipes(std::istream &is, std::deque <Recipe> &container)
{
    std::string buf_string="";
    while (is.peek()!='\n')//читаем рецепты машины
    {
        int rcp_ID=0;
        int rcp_time=0;
        is>>buf_string;
        is>>rcp_ID;
        is>>buf_string;
        is>>rcp_time;
        container.emplace_back(rcp_ID,rcp_time);
    }
}

void Environment::read_state(std::istream &is)
{
    std::string buf_string="";
    if (is>>buf_string && buf_string!="BATCHES:")
    {
        *this->_messages<<"STATE FILE IS CORRUPTED!\n";
        throw -1;
    }
    while (is>>buf_string && buf_string=="ID:")//читаем партии
    {
        int ID=0;
        int count=0;
        std::deque <Recipe> recipes{};
        is>>ID;
        is>>buf_string;
        is>>count;
        is>>buf_string;
        if (buf_string!="RECIPES:")
        {
            *this->_messages<<"STATE FILE IS CORRUPTED!\n";
            throw -1;
        }
        this->read_recipes(is,recipes);
        this->_batches.emplace_back(ID,count,recipes);
    }
    //is>>buf_string;
    if (buf_string=="QUEUES:")
    {
        while (is>>buf_string && buf_string=="ID:")
        {
            unsigned int mch_ID=0;
            is>>mch_ID;
            Machine *mch_ptr=this->search_machine(mch_ID);
            std::deque <Batch*> queue{};
            is>>buf_string;
            while (is.peek()!='\n')
            {
                is>>buf_string;
                unsigned int btc_ID=0;
                is>>btc_ID;
                Batch *btc_ptr=this->search_batch(btc_ID);
                queue.push_back(btc_ptr);
            }
            mch_ptr->insert_batch(queue);
        }
    }
}

std::istream & operator>> (std::istream & is, Environment & p)//чтение из файла конфигурации
{
    std::string buf_string="";
    is>>buf_string;
    if (buf_string!="ENVIRONMENT:")
    {
        *p._messages<<"CONFIG FILE IS CORRUPTED!\n";
        throw -1;
    }
    is>>p._name;
    is>>buf_string;
    if (buf_string!="MACHINES:")
    {
        *p._messages<<"CONFIG FILE IS CORRUPTED!\n";
        throw(-1);
    }
    is.get();// \n
    while (is>>buf_string && buf_string=="TYPE:")//читаем машины
    {
        is>>buf_string;
        Machine *ptr;
        if (buf_string=="flow")
        {
            int ID=0;
            bool state=1;
            int time=0;
            std::deque <Recipe> recipes{};
            is>>buf_string;
            is>>ID;
            is>>buf_string;
            is>>state;
            is>>buf_string;
            is>>time;
            is>>buf_string;
            if (buf_string!="RECIPES:")
            {
                *p._messages<<"CONFIG FILE IS CORRUPTED!\n";
                return is;
            }
            p.read_recipes(is,recipes);
            ptr = new M_flow(ID,recipes,state,time);
        }
        else if (buf_string=="stack")
        {
            int ID=0;
            bool state=1;
            int time=0;
            int count=0;
            std::deque <Recipe> recipes{};
            is>>buf_string;
            is>>ID;
            is>>buf_string;
            is>>state;
            is>>buf_string;
            is>>time;
            is>>buf_string;
            is>>count;
            is>>buf_string;
            if (buf_string!="RECIPES:")
            {
                *p._messages<<"CONFIG FILE IS CORRUPTED!\n";
                return is;
            }
            p.read_recipes(is,recipes);
            ptr = new M_stack(ID,recipes,state,time,count);
        }
        else if (buf_string=="group")
        {
            int ID=0;
            bool state=1;
            int time=0;
            int count=0;
            std::deque <Recipe> recipes{};
            is>>buf_string;
            is>>ID;
            is>>buf_string;
            is>>state;
            is>>buf_string;
            is>>time;
            is>>buf_string;
            is>>count;
            is>>buf_string;
            if (buf_string!="RECIPES:")
            {
                *p._messages<<"CONFIG FILE IS CORRUPTED!\n";
                return is;
            }
            p.read_recipes(is,recipes);
            ptr = new M_group(ID,recipes,state,time,count);
        }
        p._machines.push_back(ptr);
    }
    return is;
}

std::ostream &operator<<(std::ostream &os, Environment &p)
{
    os<<"ENVIRONMENT:\t"<<p._name<<'\n';
   os<<"BATCHES:\n";
    for (Batch n:p._batches) os<<n<<'\n';
   os<<"MACHINES:\n";
   for (auto n:p._machines) os<<*n<<'\n';
   os<<'\n';


    return os;
}



Environment::Environment()
{
    _global_model_time=0;
}

Environment::Environment(std::istream &is_conf, unsigned int time, std::ostream &os_log,
                         std::ostream &os_mes):
                        _config_file(&is_conf),_log_file(&os_log),_messages(&os_mes),_global_model_time(time)
{
    *_config_file>>*this;
}

Environment::Environment(std::istream &is_conf, std::istream &is_state, std::ostream &os_log,
                         std::ostream &os_mes, unsigned int time):_config_file(&is_conf),_is_state_file(&is_state)
                         ,_log_file(&os_log),_messages(&os_mes),_global_model_time(time)
{
    *_config_file>>*this;
    this->read_state(*_is_state_file);
    this->make_events();
}

Batch *Environment::search_batch(unsigned int btc_ID)
{
    auto n=this->_batches.begin();
    while (n->get_ID()!=btc_ID)
    {
        n++;
    }
    return &*n;
}

Machine *Environment::search_machine(unsigned int mch_ID)
{
    auto n=this->_machines.begin();
    Machine *ptr=*n;
    while (ptr->get_ID()!=mch_ID)
    {
        n++;
        ptr=*n;
    }
    return ptr;
}

void Environment::change_event(Machine *mch)
{
    auto ev_it=this->search_event(mch);
    this->_events.erase(ev_it);
    this->push_event(*mch);
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
            *this->_messages << "Batch with wrong recipe!\n\tMachine ID: " << mch.get_ID()

                       << "\n\tBatch ID: " << bt_ptr->get_ID() << '\n';
            throw (-1);//рассчёт событий прерван
        }
        else
            *this->_messages<<"Queue is empty!\n\tMachine ID: "<<mch.get_ID()<<'\n';
        return;
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
    for(auto mch:this->_machines)
    {
        try
        {
            this->push_event(*mch);
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



void Environment::do_step(unsigned int n)
{
    if (n < 1) return;
    try
    {
        if (this->_events.empty()) throw (-1);
        for (int i = 0; i < n; ++i)
        {
            auto ev_it = this->_events.begin();
            *this->_log_file << "MODEL_TIME: " << this->_global_model_time << '\n';
            if (this->_events.empty()) throw (i);
            this->_global_model_time += ev_it->get_time();
            auto ev_it_f = ev_it;
            ++ev_it_f;
            for (ev_it_f; ev_it_f != this->_events.end()--; ev_it_f++)
            {
                ev_it_f->time_shift(ev_it->get_time());
            }
            ev_it->execute(this->_log_file);
            Machine * m_ptr=ev_it->get_ptr();
            ev_it++;
            this->_events.pop_front();
            this->push_event(*m_ptr);
        }

    }
    catch (int err)
    {
        switch (err)
        {
            case -1:
                *this->_messages << "Event vector is empty!\n";
                break;
            default:
                *this->_messages << "End of event vector reached by step:\t"<<err<<'\n';
        }
        return;
    }

    if (DEBUG)
    {
        for (auto n:this->_events) std::cout<<n<<'\t';
        std::cout<<'\n';
    }
}

void Environment::do_step()
{
    while (!this->_events.empty())
    {
        this->do_step(1);
    }
}

void Environment::add_batch(unsigned int btc_ID, unsigned int mch_ID, unsigned int pos)
{
    Batch* btc=search_batch(btc_ID);
    Machine* mch=search_machine(mch_ID);
    bool push_event = mch->check_queue();//проверка на пустую очередь
    mch->insert_batch(btc, pos);
    if (push_event) this->push_event(*mch);
    if(push_event==0 && pos==0)//необходимо поменять event
    {
        this->change_event(mch);
    }
    //выводим сообщение
    *this->_messages<<"Batch added:\nBatch:\t"<<btc_ID<<"\tMachine:\t"<<mch_ID<<'\n';
}

void Environment::add_batch(std::vector<unsigned int> btc_IDs, unsigned int mch_ID, unsigned int pos)
{
    Machine* mch = this->search_machine(mch_ID);
    bool push_event = mch->check_queue();//проверка на пустую очередь
    std::deque <Batch*> batches ={};
    for (auto n:btc_IDs)
    {
        Batch* btc =this->search_batch(n);
        batches.push_back(btc);
    }
    mch->insert_batch(batches,pos);
    if (push_event) this->push_event(*mch);
    if(push_event==0 && pos==0)//необходимо поменять event
    {
        this->change_event(mch);
    }
    //выводим сообщение
    *this->_messages<<"Batches added:\nBatches:\t";
    for (auto n:btc_IDs)
        *this->_messages<<n<<' ';
    *this->_messages<<"\tMachine:\t"<<mch_ID<<'\n';
}


void Environment::do_step_till_machine(unsigned int mch_ID)
{
    Machine *m_ptr=this->search_machine(mch_ID);
    while (this->_events.front().get_ptr()!=m_ptr)
    {
        this->do_step(1);
    }
}

void Environment::time_shift(unsigned int time)
{
    while (this->_events.front().get_time()<time)
    {
        time-=this->_events.front().get_time();
        this->do_step(1);
    }
    for (auto n:this->_events)
    {
        n.time_shift(time);
    }
    this->_global_model_time+=time;

    if (DEBUG) std::cout<<this->_global_model_time<<'\n';
}

std::deque<Event>::iterator Environment::search_event(Machine *ptr)
{
    auto it=this->_events.begin();
    while (it->get_ptr()!=ptr) it++;
    return it;
}




































