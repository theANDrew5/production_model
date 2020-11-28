//
// Created by User on 10-Feb-20.
//
//

#include "pch.h"// pch.h: This is a precompiled header file.
#include "Machine.h"

//========================		Machine class methods	================================ класс интерфейс
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

unsigned int Machine::get_ID()
{
	return this->_ID;
}

void Machine::addRecipe(Recipe newRecipe)
{
	this->_recipes.push_back(newRecipe);
}

bool Machine::check_queue()
{
    return (this->_batches.empty());
}

void Machine::insert_batch(Batch* btc, unsigned int pos)
{
	//замена нулевого элемента неадо исправить
	/*
	if (pos == 0) //нельзя заменять нулевой элемент он уже в потоке событий!
	{
		throw(-1);
	}*/
    unsigned int n = 0;
    auto btc_pos = this->_batches.begin();
    while (n!= pos && !this->_batches.empty())
    {
        btc_pos++;
        n++;
    }
    this->_batches.insert(btc_pos, btc);

}

void Machine::insert_batch(std::deque<Batch*> &container, unsigned int pos)
{//замена нулевого элемента неадо исправить
	/*
	if (pos == 0) //нельзя заменять нулевой элемент он уже в потоке событий!
	{
		throw(-1);
	}
	*/
    for (auto n:container)
    {
        this->insert_batch(n,pos++);
    }
}

void Machine::replace_queue(std::deque<Batch *> &container)
{
	//замена нулевого элемента неадо исправить
	//нельзя заменять нулевой элемент, он уже в потоке событий
	this->_batches.erase(_batches.begin(), this->_batches.end());
    unsigned int pos=0;
    for (auto n:container)
    {
        this->insert_batch(n,pos++);
    }
}

//========================		M_flow class methods	================================ класс потоковой обработки
M_flow::M_flow()
{
	this->_type="flow";
}

M_flow::M_flow(int ID,std::deque<Recipe> recipes, bool state, unsigned int time,std::list<Batch*> batches):
        Machine(ID,recipes, state,time, batches)
{
    this->_type="flow";
}

M_flow::M_flow(const M_flow &p):Machine(p)
{
	this->_type="flow";
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




//========================		M_group class methods	================================


M_group::M_group() :
	Machine()
{
	_type = "Group";
}


M_group::M_group(int ID, std::deque<Recipe> recipes, bool state, unsigned int time, unsigned int count, std::list<Batch*> batches) :
	Machine(ID, recipes, state, time, batches),_count(count)
{
	_type = "Group";
}


M_group::M_group(const M_group &p) :
	Machine(p)
{
	_type = p._type;
	_count = p._count;
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



void M_group::execute(std::ostream *log)
{
	//		Check if the recipe need to be changed, and change it if requireed
	Batch* btcPtr = this->_batches.front();
	if (this->_last_resipe != btcPtr->get_first())
	{
		this->_last_resipe = btcPtr->get_first();
		*log << "Change_recipe\tMachine_ID: " << this->_ID << "\ttime: " << this->_time << '\n';

	}

	//		Contains the amount of Batch with the same recipes in queue
	int tmpCntr = 0;

	//		Count the group of Batchs with the same recipe from queue, and call Batch.execute() for each of them 
	for (auto iter = this->_batches.begin(); iter!= this->_batches.end(); iter++)
	{
	    if ((*iter)->get_first() != this->_last_resipe || tmpCntr==this->_count) break;
		(*iter)->execute();

		*log << "Execute_batch\tMachine_ID: " << this->_ID << "\tBatch_ID: " << (*iter)->get_ID() << "\n";

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


//========================		M_stack class methods	================================

M_stack::M_stack():
	Machine()
{
	this->_type = "stack";
}


M_stack::M_stack(int ID, std::deque<Recipe> recipes, bool state, unsigned int time, unsigned int count, std::list<Batch*> batches) :
	Machine(ID, recipes, state, time, batches), _count(count)
{
	this->_type = "stack";
}


M_stack::M_stack(const M_stack &p):
	Machine(p), _count(p._count)
{
	this->_type = "stack";
}


unsigned int M_stack::push_ev()
{
	if (!_batches.empty())
	{
		Batch *it = _batches.front();
		Recipe &rcp = it->get_first();
		if (std::any_of(_recipes.begin(), _recipes.end(), [rcp](Recipe const r) {return rcp == r; }))
			//проверка рецептов
		{
			return  ((this->_last_resipe == it->get_first()) ?
				rcp.get_time()*(int(it->get_count() / this->_count) + 1) :
				rcp.get_time()*(int(it->get_count() / this->_count)+ 1 ) + this->_time); //OK
		}
		else throw (it);//ошибка в очереди партия с неверным рецептом
	}
	else
	{
		Batch *ptr = nullptr;
		throw (ptr); //очередь пуста
	}
}


void M_stack::execute(std::ostream *log)
{
	Batch* bt_ptr = this->_batches.front();
	if (this->_last_resipe != bt_ptr->get_first())
	{
		*log << "Change_recipe\tMachine_ID: " << this->_ID << "\ttime: " << this->_time << '\n';
		_last_resipe = bt_ptr->get_first();
		//вставить вывод в лог
	}
	*log << "Execute_batch\tMachine_ID: " << this->_ID << "\tBatch_ID: " << bt_ptr->get_ID();
	bt_ptr->execute();
	this->_batches.pop_front();
}



M_stack::~M_stack()
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







