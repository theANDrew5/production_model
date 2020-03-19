//
// Created by User on 10-Feb-20.
//
//
#include "Machine.h"
#include <algorithm>

//конструкторы и деструктор интерфейса
Machine::Machine() {_last_resipe= Recipe ();}

Machine::Machine(int ID,std::deque<Recipe> recipes, bool state, unsigned int time, std::list<Batch*> batches):
_ID(ID),_recipes(recipes),_batches(batches), _state(state),_time(time)
{
    _last_resipe=Recipe ();
}

Machine::Machine(const Machine &p):
_ID(p._ID), _batches(p._batches),_recipes(p._recipes), _state(p._state),_time(p._time)
{_last_resipe= Recipe ();}

Machine::~Machine() = default;


//конструкторы и деструктор класса потоковой обработки
M_flow::M_flow()
{
    _type="flow";
}

M_flow::M_flow(int ID,std::deque<Recipe> recipes, bool state, unsigned int time,std::list<Batch*> batches):
        Machine(ID,recipes, state,time, batches)
{
    _type="flow";
}

M_flow::M_flow(const M_flow &p):Machine(p)
{
    _type="flow";
}

M_flow::~M_flow() = default;


//Метод выполняет рассчёт события в очереди
unsigned int M_flow::push_ev()
{
    if (!_batches.empty())
    {
        Batch *it=_batches.front();
        Recipe &rcp = it->get_first();
        if(std::any_of(_recipes.begin(),_recipes.end(),[rcp](Recipe const r){return rcp==r;}))
        //проверка рецептов
        {
            return  ((this->_last_resipe==it->get_first())?
            rcp.get_time()*it->get_count():rcp.get_time()*it->get_count()+this->_time ); //OK
        }
        else throw (it);//ошибка в очереди партия с неверным рецептом
    }
    else
    {
        Batch *ptr= nullptr;
        throw (ptr) ; //очередь пуста
    }
 }

void M_flow::execute(std::ostream *log)//выполнение события
{

    Batch* bt_ptr=this->_batches.front();
    if (this->_last_resipe!=bt_ptr->get_first())
    {
        *log<<"Change_recipe\tMachine_ID: "<< this->_ID<<"\ttime: "<< this->_time<<'\n';
        _last_resipe=bt_ptr->get_first();
        //вставить вывод в лог
    }
    *log<<"Execute_batch\tMachine_ID: "<< this->_ID<<"\tBatch_ID: "<<bt_ptr->get_first().get_ID();
    bt_ptr->execute();
    this->_batches.pop_front();
}

unsigned int M_flow::get_ID()
{
    return this->_ID;
}

void M_flow::insert_batch(Batch* btc, unsigned int pos)
{
    unsigned int n=0;
    auto btc_pos=this->_batches.begin();
    while (n!=pos & !this->_batches.empty())
    {
        btc_pos++;
        n++;
    }
    this->_batches.insert(btc_pos,btc);
}

void M_flow::insert_batch(std::deque<Batch*> &container, unsigned int pos)
{
    for (auto n:container)
    {
        this->insert_batch(n,pos++);
    }
}



//========================		M_group class methods	================================


M_group::M_group() :
	Machine()
{
	_type = "Group";
}


M_group::M_group(int ID, std::deque<Recipe> recipes, bool state, unsigned int time, std::list<Batch*> batches) :
	Machine(ID, recipes, state, time, batches)
{
	_type = "Group";
}


M_group::M_group(const M_group &p) :
	Machine(p)
{
	_type = p._type;
}


unsigned int M_group::push_ev()
{	

	//		Check if queue is empty
	if (!this->_batches.empty())
	{
		Batch *firstBatchPtr = this->_batches.front();
		
		Recipe &firstBatchRecipeRef = firstBatchPtr->get_first();

		if (std::any_of(_recipes.begin(), _recipes.end(), [firstBatchRecipeRef](Recipe const r) {return firstBatchRecipeRef == r; }))
			//проверка рецептов
		{
			return  ((this->_last_resipe == firstBatchPtr->get_first()) ?

				firstBatchRecipeRef.get_time() :

				firstBatchRecipeRef.get_time() + this->_time); //OK
		}
		else throw (firstBatchPtr);//ошибка в очереди партия с неверным рецептом

	}
	else
	{

		//		null pointer exception
		Batch *ptr = nullptr;

		throw (ptr);
	}
}

unsigned int M_group::get_ID()
{
	return this->_ID;
}


void M_group::execute()
{
	//		Check if the recipe need to be changed, and change it if requireed
	Batch* btcPtr = this->_batches.front();
	if (this->_last_resipe != btcPtr->get_first())
	{
		this->_last_resipe = btcPtr->get_first();

	}

	//		Contains the amount of Batch with the same recipes in queue
	int tmpCntr = 0;

	//		Count the group of Batchs with the same recipe from queue, and call Batch.execute() for each of them 
	for (std::list<Batch*>::iterator iter = this->_batches.begin(); (*iter)->get_first() == this->_last_resipe; iter++)
	{
		(*iter)->execute();
		
		tmpCntr++;

	}	

	//		Drop n = tmpCntr Batches from queue
	for (int i = 0; i < tmpCntr; i++)
	{
		this->_batches.pop_front();
	}
}


M_group::~M_group()
{

}




std::ostream &operator<<(std::ostream & os, Machine &p)//перегрузка оператора сдвига для вывода
{
    os<<"TYPE: "<<p._type;
    os<<"\tID: "<<p._ID;
    os<<"\tSTATE: "<<p._state;
    os<<"\tTIME "<<p._time;
    os<<"\tRECIPES:";
    for(Recipe n:p._recipes) os<<'\t'<<n;
    os<<'\n';
    /*
    for(Batch* n:p._batches) os<<n->get_ID()<<' ';
    os<<'\t';*/
    return os;
}





